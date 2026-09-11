"""LLDB callbacks for capture_mwgraph.py; loaded only by the debugger."""
from __future__ import annotations

import hashlib
import json
import sys
from pathlib import Path

import lldb

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from fzgx.mwgraph import PROFILES, read_graph

_state = {}


def memory(address, size):
    if not size:
        return b''
    error = lldb.SBError()
    data = _state['process'].ReadMemory(address, size, error)
    if not error.Success() or len(data) != size:
        raise RuntimeError(f'cannot read compiler memory at {address:#x}: {error}')
    return data


def number(address, width=4):
    return int.from_bytes(memory(address, width), 'little')


def after(frame, location, internal):
    try:
        index, cls = _state['pending'].pop(location.GetBreakpoint().GetID())
        _state['captures'][index]['after'] = read_graph(memory, _state['profile'], cls)
        location.GetBreakpoint().SetEnabled(False)
    except Exception as error:
        _state['error'] = str(error)
        return True
    return False


def select(frame, location, internal):
    try:
        stack = frame.FindRegister('rsp').GetValueAsUnsigned() & 0xffffffff
        profile = _state['profile']
        if profile['class_global']:
            cls = {4: 'gpr', 3: 'fpr'}[number(profile['class_global'], 1)]
            head = number(stack + 4)
        else:
            cls = {0: 'gpr', 1: 'fpr'}[number(stack + 4)]
            head = number(stack + 8)
        index = len(_state['captures'])
        _state['captures'].append({'before': read_graph(memory, profile, cls, head)})
        bp = _state['target'].BreakpointCreateByAddress(number(stack))
        bp.SetScriptCallbackFunction('mwgraph_lldb.after')
        _state['pending'][bp.GetID()] = index, cls
    except Exception as error:
        _state['error'] = str(error)
        return True
    return False


def begin_function(frame, location, internal):
    try:
        stack = frame.FindRegister('rsp').GetValueAsUnsigned() & 0xffffffff
        obj = number(stack + 8)
        record = number(obj + 10) if obj else 0
        name = bytearray()
        if record:
            for i in range(1024):
                byte = memory(record + 10 + i, 1)
                if byte == b'\0':
                    break
                name.extend(byte)
        _state['captures'] = _state['by_name'].setdefault(name.decode('utf-8', errors='replace'), [])
    except Exception as error:
        _state['error'] = str(error)
        return True
    return False


def run(debugger, config_path):
    config = json.loads(Path(config_path).read_text())
    debugger.SetAsync(False)
    groups = []
    for job in config['jobs']:
        key = job['args'][:-4]
        for group in groups:
            if group[0]['args'][:-4] == key and all(j['name'] != job['name'] for j in group):
                group.append(job)
                break
        else:
            groups.append([job])
    reports = []
    for group in groups:
        digest = hashlib.sha256(Path(group[0]['args'][0]).read_bytes()).hexdigest()
        profile = PROFILES[digest]
        target = debugger.CreateTarget(config['wibo'])
        loader = target.BreakpointCreateByRegex('loadPEFromSource')
        _state.clear()
        _state.update(profile=profile, target=target, captures=[], by_name={}, pending={}, error=None)
        directory = str(Path(group[0]['args'][-1]).parent)
        arguments = group[0]['args'][:-4] + ['-c', '-o', directory] + [j['args'][-3] for j in group]
        process = target.LaunchSimple(arguments, None, config['root'])
        _state['process'] = process
        failure = None
        try:
            if process.GetState() != lldb.eStateStopped:
                raise RuntimeError('compiler loader breakpoint was not reached')
            process.GetSelectedThread().StepOut()
            loader.SetEnabled(False)
            # PE code is now mapped; resolving guest breakpoints before loading
            # silently misses them under native Wibo.
            memory(profile['select'], 8)
            for address, callback in ((profile['select'], 'select'), (profile['codegen'], 'begin_function')):
                bp = target.BreakpointCreateByAddress(address)
                bp.SetScriptCallbackFunction('mwgraph_lldb.' + callback)
            while process.GetState() == lldb.eStateStopped:
                if _state['error']:
                    raise RuntimeError(_state['error'])
                process.Continue()
                if process.GetState() == lldb.eStateStopped:
                    reason = process.GetSelectedThread().GetStopReason()
                    if reason not in (lldb.eStopReasonPlanComplete, lldb.eStopReasonBreakpoint):
                        raise RuntimeError(f'unexpected debugger stop: {reason}')
            if process.GetState() != lldb.eStateExited or process.GetExitStatus() != 0:
                raise RuntimeError(f'compiler exit: {process.GetExitStatus()}')
            if _state['pending']:
                raise RuntimeError('incomplete allocator capture')
        except Exception as error:
            process.Kill()
            failure = str(error)
        finally:
            debugger.DeleteTarget(target)
        for job in group:
            captures = _state['by_name'].get(job['name'])
            if failure or not captures:
                report = {'symbol': job['symbol'], 'error': failure or 'no allocator capture for function'}
            else:
                report = {'symbol': job['symbol'], 'compiler_sha256': digest, 'captures': captures}
            Path(job['capture']).write_text(json.dumps(report))
            reports.append({k: v for k, v in report.items() if k != 'captures'})
            print(json.dumps(reports[-1]), flush=True)
    Path(config['report']).write_text(json.dumps(reports))
