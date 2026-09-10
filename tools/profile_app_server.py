#!/usr/bin/env python3
"""Measure live app-server multiplexing without claiming decompilation functions.

Each model receives a nonce and returns it through a dynamic tool. The host
interrupts before returning that result, exercising the matcher's terminal path.
Requests are billable; this is an explicit capacity diagnostic, never a CI check.
"""
import argparse
import asyncio
import contextlib
import json
import os
import time
from pathlib import Path

from codex_server import AppServer, Matcher, tool
from orchestrate import codex_server_cmd, price_usage
from fzgx.project import STATE_DIR


async def profile(a):
    directory = STATE_DIR / 'diagnostics' / a.name
    server = AppServer(codex_server_cmd(a.model, a.provider, a.effort), directory)
    sessions, processes = [], []
    started = time.monotonic()
    progress = {'loaded': 0, 'called': 0, 'completed': 0, 'wrong_nonce': 0, 'hooks': 0}
    ready = asyncio.Event()

    class Probe(Matcher):
        def event(self, message):
            super().event(message)
            if message.get('method') == 'hook/started':
                progress['hooks'] += 1

        async def call(self, message):
            p = message['params']
            self.turn = p['turnId']
            self.tool_calls += 1
            if p['tool'] != 'record' or p.get('namespace') or p['arguments'] != {'nonce': self.symbol}:
                progress['wrong_nonce'] += 1
            progress['called'] += 1
            await self.interrupt()

    async def one(i):
        s = Probe(server, None, str(i), '', a.model, directory)
        sessions.append(s)
        try:
            r = await server.request('thread/start', dict(model=a.model, modelProvider=a.provider,
                approvalPolicy='never', sandbox='read-only', ephemeral=True,
                baseInstructions='Call the record tool with the supplied nonce.', developerInstructions='',
                config=server.thread_config, dynamicTools=[tool('record', 'Record the supplied nonce.', nonce='Supplied nonce')],
                allowProviderModelFallback=False))
            s.thread = r['thread']['id']
            server.sessions[s.thread] = s
            if r['model'] != a.model or r['modelProvider'] != a.provider:
                raise RuntimeError('unexpected provider/model')
            progress['loaded'] += 1
            if progress['loaded'] == a.parallel:
                ready.set()
            await ready.wait()
            r = await server.request('turn/start', dict(threadId=s.thread,
                input=[dict(type='text', text=f'Call record with nonce "{i}".')], effort=a.effort, summary='none'))
            s.turn = r['turn']['id']
            await asyncio.wait_for(s.done.wait(), a.timeout)
            progress['completed'] += 1
        finally:
            with contextlib.suppress(Exception):
                await s.interrupt()
                await server.request('thread/unsubscribe', dict(threadId=s.thread))
            server.sessions.pop(s.thread, None)
            s.log.close()

    async def sample():
        while True:
            cp = await asyncio.create_subprocess_exec('ps', '-axo', 'pid=,ppid=,rss=,comm=', stdout=asyncio.subprocess.PIPE)
            stdout, _ = await cp.communicate()
            rows = [line.split(None, 3) for line in stdout.decode().splitlines()]
            descendants = {server.process.pid}
            while True:
                more = {int(pid) for pid, parent, rss, comm in rows if int(parent) in descendants}
                if more <= descendants:
                    break
                descendants |= more
            owned = [(int(pid), int(rss), comm) for pid, parent, rss, comm in rows if int(pid) in descendants]
            processes.append(dict(seconds=round(time.monotonic() - started, 3),
                                  rss_kib=sum(rss for _, rss, _ in owned), processes=owned, **progress))
            await asyncio.sleep(0.5)

    sampler, failure = None, None
    try:
        await server.start()
        sampler = asyncio.create_task(sample())
        async with asyncio.TaskGroup() as group:
            for i in range(a.parallel):
                group.create_task(one(i))
    except Exception as error:
        failure = repr(error)
    finally:
        if sampler:
            sampler.cancel()
            with contextlib.suppress(asyncio.CancelledError):
                await sampler
        if server.process:
            await server.close()
    prices = price_usage(a.model, [u for s in sessions for u in s.samples], a.provider)
    summary = dict(parallel=a.parallel, elapsed_s=round(time.monotonic() - started, 3), **progress, **prices,
                   error=failure, overload_retries=server.overload_retries,
                   peak_rss_mib=round(max((p['rss_kib'] for p in processes), default=0) / 1024, 1),
                   peak_processes=max((len(p['processes']) for p in processes), default=0), samples=processes)
    (directory / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    print(json.dumps({k: v for k, v in summary.items() if k != 'samples'}, indent=2))
    return 0 if not failure and progress['called'] == a.parallel and not progress['wrong_nonce'] else 1


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--parallel', type=int, required=True)
    p.add_argument('--provider', choices=['openai', 'deepseek'], default='deepseek')
    p.add_argument('--model', default='deepseek-flash')
    p.add_argument('--effort', default='low')
    p.add_argument('--api-key-file', type=Path)
    p.add_argument('--timeout', type=int, default=180)
    p.add_argument('--name', default=time.strftime('app-server-profile-%Y%m%d-%H%M%S'))
    a = p.parse_args()
    if a.parallel < 1:
        p.error('--parallel must be positive')
    if a.api_key_file:
        os.environ['DEEPSEEK_API_KEY'] = a.api_key_file.expanduser().read_text().strip()
    if a.provider == 'deepseek' and not os.environ.get('DEEPSEEK_API_KEY'):
        p.error('set DEEPSEEK_API_KEY or pass --api-key-file')
    return asyncio.run(profile(a))


if __name__ == '__main__':
    raise SystemExit(main())
