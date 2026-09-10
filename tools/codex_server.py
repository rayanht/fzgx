"""Multiplex matcher threads over one Codex app-server stdio connection.

Only active tool calls consume a subprocess slot. Model sessions use asyncio
tasks; identities and file paths never come from model tool arguments.
"""
from __future__ import annotations

import asyncio
import contextlib
import json
import os
import signal
import sys
import time
from datetime import datetime, timezone
from pathlib import Path

from fzgx import api
from fzgx.ledger import Ledger
from fzgx.project import ROOT, STATE_DIR


def tool(name, description, **parameters):
    return dict(type='function', name=name, description=description, deferLoading=False,
                inputSchema=dict(type='object', properties={k: dict(type='string', description=v)
                                 for k, v in parameters.items()}, required=list(parameters), additionalProperties=False))


MATCHER_TOOLS = [
    tool('write_unit', 'Replace your complete C work copy, compile, and return the retail object diff.',
         source='Complete C source'),
    tool('patch_unit', 'Replace one unique occurrence in your work copy, compile, and return the diff.',
         old='Exact text occurring once', new='Replacement text'),
    tool('check', 'Probe compiler versions and retain the best compiler for subsequent edits.',
         versions='all, a comma-separated compiler list, or empty to check the current compiler'),
    tool('release', 'Stop working on this function, saving your best candidate.', reason='Precise remaining technical obstacle'),
]


class RpcError(RuntimeError):
    def __init__(self, error):
        super().__init__(json.dumps(error))
        self.code = error.get('code')


class AppServer:
    def __init__(self, command, directory):
        self.command, self.directory = command, directory
        self.pending, self.sessions, self.jobs = {}, {}, set()
        self.serial = 0
        self.write_lock = asyncio.Lock()
        # The server bounds pending commands, not live model turns. Reserve
        # separate slots for stopping/unloading so a start burst cannot starve
        # completion. Tool responses never wait for these command slots.
        self.start_slots = asyncio.Semaphore(16)
        self.control_slots = asyncio.Semaphore(16)
        self.overload_retries = 0
        self.process = None
        self.closed = False

    async def start(self):
        self.directory.mkdir(parents=True, exist_ok=True)
        self.errors = (self.directory / 'app-server.stderr.log').open('w')
        self.events = (self.directory / 'app-server.jsonl').open('w', buffering=1)
        self.process = await asyncio.create_subprocess_exec(
            *self.command, cwd=ROOT, stdin=asyncio.subprocess.PIPE, stdout=asyncio.subprocess.PIPE,
            stderr=self.errors, start_new_session=True, limit=32 * 1024 * 1024)
        (self.directory / 'app-server.pid').write_text(str(self.process.pid) + '\n')
        self.reader = asyncio.create_task(self._read())
        await self.request('initialize', dict(clientInfo=dict(name='fzgx', version='1.0'),
                                             capabilities=dict(experimentalApi=True)))
        await self.send(dict(method='initialized'))
        # Codex 0.153.4 still starts inherited servers with orchestrator.mcp
        # disabled. Disable every effective server explicitly before any thread.
        # Never write config or auth; the names come from a read-only RPC.
        config = await self.request('config/read', dict(cwd=str(ROOT), includeLayers=False))
        self.thread_config = {f'mcp_servers.{name}.enabled': False
                              for name in config['config'].get('mcp_servers', {})}
        return self

    async def send(self, message):
        async with self.write_lock:
            self.process.stdin.write((json.dumps(message) + '\n').encode())
            await self.process.stdin.drain()

    async def request(self, method, params, timeout=120):
        slots = self.start_slots if method in ('thread/start', 'turn/start') else self.control_slots
        async with asyncio.timeout(timeout):
            async with slots:
                delay = 0.05
                while True:
                    try:
                        return await self._request_once(method, params)
                    except RpcError as error:
                        # This explicit rejection means the command was not
                        # accepted. Never retry a timeout or other ambiguous
                        # failure: thread/start and turn/start are mutations.
                        if error.code != -32001:
                            raise
                        self.overload_retries += 1
                        await asyncio.sleep(delay)
                        delay = min(1.0, delay * 2)

    async def _request_once(self, method, params):
        if self.closed:
            raise RuntimeError('Codex app server disconnected')
        self.serial += 1
        rid = self.serial
        future = asyncio.get_running_loop().create_future()
        self.pending[rid] = future
        try:
            await self.send(dict(id=rid, method=method, params=params))
            return await future
        finally:
            self.pending.pop(rid, None)

    async def _dispatch(self, message, session):
        rid, method = message['id'], message['method']
        if method != 'item/tool/call' or session is None:
            await self.send(dict(id=rid, error=dict(code=-32601, message='Only assigned matcher tools are available')))
            return
        await session.call(message)

    async def _read(self):
        failure = RuntimeError('Codex app server disconnected')
        try:
            while line := await self.process.stdout.readline():
                message = json.loads(line)
                method, params = message.get('method', ''), message.get('params') or {}
                # Completed items carry the full text. Persisting every token
                # delta multiplies log I/O at high model concurrency.
                if method.endswith(('/delta', '/textDelta', '/outputDelta')):
                    continue
                if method == 'mcpServer/startupStatus/updated' and params.get('status') == 'starting':
                    raise RuntimeError('Unexpected inherited MCP startup: ' + params['name'])
                if not method:
                    future = self.pending.get(message.get('id'))
                    if future and not future.done():
                        if 'error' in message:
                            future.set_exception(RpcError(message['error']))
                        else:
                            future.set_result(message.get('result'))
                    continue
                session = self.sessions.get(params.get('threadId'))
                if session:
                    session.event(message)
                elif not method.startswith('codex/event/'):
                    self.events.write(json.dumps(dict(timestamp=utcnow(), **message)) + '\n')
                if 'id' in message:
                    job = asyncio.create_task(self._dispatch(message, session))
                    self.jobs.add(job)
                    job.add_done_callback(self.jobs.discard)
        except Exception as error:
            failure = error
        finally:
            for future in list(self.pending.values()):
                if not future.done():
                    future.set_exception(failure)
            for session in list(self.sessions.values()):
                session.error = str(failure)
                session.done.set()
            self.closed = True

    async def close(self):
        # Let already-dispatched compiler/submission operations finish before
        # tearing down the transport or releasing their claims.
        if self.jobs:
            await asyncio.gather(*list(self.jobs), return_exceptions=True)
        if self.process and self.process.returncode is None:
            self.process.stdin.close()
            try:
                await asyncio.wait_for(self.process.wait(), 10)
            except TimeoutError:
                os.killpg(self.process.pid, signal.SIGTERM)
                await self.process.wait()
        await self.reader
        self.errors.close()
        self.events.close()


def utcnow():
    return datetime.now(timezone.utc).isoformat()


class Matcher:
    def __init__(self, server, slots, symbol, agent, model, directory):
        self.server, self.slots = server, slots
        self.symbol, self.agent, self.model = symbol, agent, model
        self.directory = directory
        self.terminal = directory / f'{symbol}.terminal.json'
        if self.terminal.exists():
            raise ValueError(f'{self.terminal}: already completed; use a new batch name')
        self.env = {**os.environ, 'FZGX_AGENT_ID': agent, 'FZGX_SYMBOL': symbol,
                    'FZGX_HARNESS': 'codex', 'FZGX_MODEL': model, 'FZGX_RESULT_FILE': str(self.terminal)}
        self.log = (directory / f'{symbol}.log').open('w', buffering=1)
        self.done, self.lock = asyncio.Event(), asyncio.Lock()
        self.thread = self.turn = None
        self.error = None
        self.total, self.samples = {}, []
        self.model_started = False
        self.tool_calls, self.tool_secs, self.queue_secs = 0, 0.0, 0.0

    def event(self, message):
        self.log.write(json.dumps(dict(timestamp=utcnow(), **message)) + '\n')
        params, method = message.get('params', {}), message.get('method')
        if method == 'turn/started':
            self.turn = params['turn']['id']
        elif method == 'thread/tokenUsage/updated':
            total = params['tokenUsage']['total']
            fields = dict(input_tokens='inputTokens', cached_input_tokens='cachedInputTokens',
                          cache_write_input_tokens='cacheWriteInputTokens', output_tokens='outputTokens')
            delta = {k: max(0, total.get(v, 0) - self.total.get(v, 0)) for k, v in fields.items()}
            if delta['input_tokens'] or delta['output_tokens']:
                timestamp = (datetime.fromtimestamp(message['emittedAtMs'] / 1000, timezone.utc).isoformat()
                             if message.get('emittedAtMs') else utcnow())
                self.samples.append((timestamp, delta))
            self.total = total
        elif method == 'turn/completed':
            turn = params['turn']
            if turn.get('error'):
                self.error = json.dumps(turn['error'])
            self.done.set()
        elif method == 'error' and not params.get('willRetry', False):
            self.error = json.dumps(params.get('error', params))

    async def cli(self, *args):
        queued = time.monotonic()
        async with self.slots:
            started = time.monotonic()
            self.queue_secs += started - queued
            proc = await asyncio.create_subprocess_exec(
                sys.executable, str(ROOT / 'tools/fzgx.py'), '--json', *args, cwd=ROOT, env=self.env,
                stdout=asyncio.subprocess.PIPE, stderr=asyncio.subprocess.PIPE, start_new_session=True)
            # Shield a tool mutation from session cancellation. Killing submit
            # halfway through carving would leave the build tree inconsistent.
            pending = asyncio.create_task(proc.communicate())
            try:
                stdout, stderr = await asyncio.shield(pending)
            except asyncio.CancelledError:
                await pending
                raise
            self.tool_secs += time.monotonic() - started
            try:
                return json.loads(stdout)
            except ValueError:
                raise RuntimeError((stderr or stdout or b'empty tool result').decode(errors='replace')[-2000:])

    async def interrupt(self):
        if self.turn and not self.done.is_set() and not self.server.closed:
            await self.server.request('turn/interrupt', dict(threadId=self.thread, turnId=self.turn))
            await asyncio.wait_for(self.done.wait(), 30)

    async def call(self, message):
        params, rid = message['params'], message['id']
        async with self.lock:
            if self.terminal.exists() or self.done.is_set():
                return
            try:
                self.turn = params['turnId']
                name, args = params['tool'], params['arguments']
                spec = next((t for t in MATCHER_TOOLS if t['name'] == name), None)
                if not spec or params.get('namespace') or not isinstance(args, dict) or set(args) != set(spec['inputSchema']['required']):
                    raise ValueError('invalid assigned tool or arguments')
                if not all(isinstance(v, str) for v in args.values()):
                    raise ValueError('tool arguments must be strings')
                self.tool_calls += 1
                if name in ('write_unit', 'patch_unit'):
                    paths = []
                    try:
                        command = [name.replace('_', '-'), self.symbol, '--agent', self.agent]
                        for key, value in args.items():
                            path = self.directory / f'{self.symbol}.tool.{key}'
                            path.write_text(value)
                            paths.append(path)
                            command += ['--file' if key == 'source' else f'--{key}-file', str(path)]
                        result = await self.cli(*command)
                    finally:
                        for path in paths:
                            path.unlink(missing_ok=True)
                elif name == 'check':
                    result = await self.cli('check', self.symbol, *(['--versions', args['versions']] if args['versions'] else []))
                else:
                    result = await self.cli('release', self.symbol, '--agent', self.agent, '--reason', args['reason'])
                self.log.write(json.dumps(dict(timestamp=utcnow(), method='fzgx/tool/result',
                                               params=dict(tool=name, result=result))) + '\n')
                if self.terminal.exists():
                    # Interrupt before returning the terminal tool result, so
                    # Codex cannot issue a model request just to summarize it.
                    await self.interrupt()
                    return
                text = api.format_check(result) if name == 'check' else json.dumps(result)
                response = dict(success=result.get('ok', True), contentItems=[dict(type='inputText', text=text)])
            except Exception as error:
                response = dict(success=False, contentItems=[dict(type='inputText', text=str(error))])
            await self.server.send(dict(id=rid, result=response))

    async def run(self, options, revise=False):
        started = time.monotonic()
        setup_secs, outcome = 0.0, 'incomplete'
        try:
            async with asyncio.timeout(options.timeout):
                assignment = await self.cli('claim', self.symbol, '--agent', self.agent)
                if not assignment.get('ok'):
                    raise RuntimeError('assignment failed: ' + json.dumps(assignment))
                seed = assignment.get('seed') or {}
                if seed and not revise and not (seed.get('kind') == 'lift_total' and '???' in seed['source']):
                    assignment['initial_check'] = api.format_check(await self.cli('check', self.symbol))
                    seed['instruction'] = 'Continue this installed work copy from the initial diff using patch_unit.'
                (self.directory / f'{self.symbol}.assignment.json').write_text(json.dumps(assignment, indent=2) + '\n')
                setup_secs = round(time.monotonic() - started, 3)
                if not self.terminal.exists():
                    task = {'context': assignment['context']}
                    if seed:
                        task['seed'] = {k: seed[k] for k in ('source', 'kind', 'instruction') if k in seed}
                    if revise:
                        task['source'] = (await self.cli('read-unit', self.symbol))
                    if assignment.get('initial_check'):
                        task['initial_check'] = assignment['initial_check']
                    prompt = f'Assigned function: {self.symbol}. Continue the supplied reconstruction.\n' + json.dumps(task)
                    (self.directory / f'{self.symbol}.prompt.txt').write_text(prompt + '\n')
                    instructions = ROOT / 'tools' / ('codex_revise.md' if revise else 'codex_matcher.md')
                    response = await self.server.request('thread/start', dict(
                        model=self.model, modelProvider=options.provider, cwd=str(ROOT), approvalPolicy='never',
                        sandbox='read-only', baseInstructions=instructions.read_text(), developerInstructions='',
                        config=self.server.thread_config, dynamicTools=MATCHER_TOOLS, ephemeral=True,
                        allowProviderModelFallback=False))
                    self.thread = response['thread']['id']
                    self.server.sessions[self.thread] = self
                    self.log.write(json.dumps(dict(method='fzgx/thread', params=response)) + '\n')
                    if response['model'] != self.model or response['modelProvider'] != options.provider:
                        raise RuntimeError('server selected a different model or provider')
                    self.model_started = True
                    response = await self.server.request('turn/start', dict(
                        threadId=self.thread, input=[dict(type='text', text=prompt)], effort=options.effort,
                        summary='none', model=self.model))
                    self.turn = response['turn']['id']
                    await self.done.wait()
                    if self.error:
                        raise RuntimeError(self.error)
        except TimeoutError:
            outcome, self.error = 'timeout', 'worker wall time exhausted'
        except Exception as error:
            outcome, self.error = 'crash', str(error)
        finally:
            # Serialize cleanup after in-flight edits, including on timeout.
            with contextlib.suppress(Exception):
                await self.interrupt()
            async with self.lock:
                if not self.terminal.exists():
                    reason = self.error or 'model ended without a match; best candidate saved automatically'
                    try:
                        await self.cli('release', self.symbol, '--agent', self.agent, '--reason', reason)
                    except Exception as error:
                        self.error = f'{reason}; automatic release failed: {error}'
            if self.thread:
                with contextlib.suppress(Exception):
                    await self.server.request('thread/unsubscribe', dict(threadId=self.thread))
                self.server.sessions.pop(self.thread, None)
            self.log.close()
        attempt = json.loads(self.terminal.read_text()) if self.terminal.exists() else {}
        if attempt:
            status = attempt['outcome'].removeprefix('shadow-')
            outcome = 'matched' if status in ('matched', 'matched-pool') else ('released' if not self.error else outcome + '+released')
        return dict(symbol=self.symbol, outcome=outcome, percent=100.0 if outcome == 'matched' else attempt.get('best_in_attempt'),
                    checks=attempt.get('checks'), secs=round(time.monotonic() - started, 1), setup_secs=setup_secs,
                    tool_secs=round(self.tool_secs, 3), tool_queue_secs=round(self.queue_secs, 3), tool_calls=self.tool_calls,
                    model_started=self.model_started, model=self.model if self.model_started else '',
                    thread_id=self.thread, error=self.error, turns=1 if self.model_started else 0,
                    rc=0 if not self.error else 1, attempt_id=attempt.get('id'), usage_samples=self.samples)


async def fan_out(p, options, model, symbols, batch, revise, command, price):
    directory = STATE_DIR / 'runs' / batch
    server = AppServer(command, directory)
    slots = asyncio.Semaphore(options.tool_parallel)
    queue = iter(enumerate(symbols, 1))
    results, spent = [], 0.0

    async def worker():
        nonlocal spent
        while not server.closed and (options.budget_usd is None or spent < options.budget_usd):
            try:
                idx, symbol = next(queue)
            except StopIteration:
                return
            prefix = 'revise-' if revise else ('shadow-' if options.shadow else '')
            matcher = Matcher(server, slots, symbol, f'{prefix}{batch}-codex-{idx}', model, directory)
            row = await matcher.run(options, revise)
            row.update(price(model, row.pop('usage_samples'), options.provider, options.fast))
            spent += row['cost']
            if row['attempt_id']:
                Ledger().db.execute('UPDATE attempts SET tokens_in=?,tokens_out=?,cost_usd=?,harness=?,model=? WHERE id=?',
                                    (row['tokens_in'], row['tokens_out'], row['cost'], 'codex', model, row['attempt_id']))
            results.append(row)
            with (directory / 'results.jsonl').open('a') as output:
                output.write(json.dumps(row) + '\n')
            pct = '' if row['percent'] is None else f"{row['percent']:.1f}%"
            print(f"  {row['outcome']:16s} {symbol:14s} {pct:7s} checks={row['checks']} "
                  f"tools={row['tool_calls']} ${row['cost']:.3f} {row['secs']}s", flush=True)

    parent = asyncio.current_task()
    loop = asyncio.get_running_loop()
    loop.add_signal_handler(signal.SIGTERM, parent.cancel)
    try:
        await server.start()
        async with asyncio.TaskGroup() as group:
            for _ in range(min(options.parallel, len(symbols))):
                group.create_task(worker())
    finally:
        if server.process:
            await server.close()
        loop.remove_signal_handler(signal.SIGTERM)
    return results, spent
