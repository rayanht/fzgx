"""PowerPC/CodeWarrior decompilation with owned type context and the existing oracle."""
from __future__ import annotations

import io
import json
import re
import subprocess
from contextlib import contextmanager, redirect_stdout, redirect_stderr

from .project import ROOT, STATE_DIR
from .sdkimport import declarations, masked
from .signatures import recovered, propagate, split_params


def _expand(text, name, emit):
    """Expand balanced generated expressions, including nested field accesses."""
    while match := re.search(r'\b' + name + r'\(', text):
        start = match.end()
        depth, end = 1, start
        while end < len(text) and depth:
            depth += (text[end] == '(') - (text[end] == ')')
            end += 1
        if depth:
            raise ValueError(f'unclosed {name}')
        replacement = emit(split_params(text[start:end - 1]))
        text = text[:match.start()] + replacement + text[end:]
    return text


def structure_loops(text):
    """A single back edge to a guarded block is a while loop, not a C goto header."""
    while True:
        code = masked(text)
        changed = False
        for match in re.finditer(r'(?m)^(\w+):\s*\n([ \t]*)if\s*\(', code):
            label, indent = match[1], match[2]
            if len(re.findall(r'\bgoto\s+' + label + r'\s*;', code)) != 1:
                continue
            start, depth = match.end(), 1
            end = start
            while end < len(code) and depth:
                depth += (code[end] == '(') - (code[end] == ')')
                end += 1
            opening = re.match(r'\s*\{', code[end:])
            if not opening:
                continue
            body_start = end + opening.end()
            closing, depth = body_start, 1
            while closing < len(code) and depth:
                depth += (code[closing] == '{') - (code[closing] == '}')
                closing += 1
            tail = re.search(r'\bgoto\s+' + label + r'\s*;\s*$', code[body_start:closing - 1])
            if not tail or re.match(r'\s*else\b', code[closing:]):
                continue
            text = (text[:match.start()] + indent + 'while (' + text[start:end]
                    + text[end:body_start] + text[body_start:body_start + tail.start()]
                    + indent + '}' + text[closing:])
            changed = True
            break
        if not changed:
            return text


@contextmanager
def _mwcc_formatting(signatures, stack):
    """Retain machine-width accesses when inference cannot name a compatible C field."""
    from m2c import translate as ir
    from m2c import evaluate
    saved = {cls: cls.format for cls in (ir.StructAccess, ir.Cast, ir.FuncCall, ir.BinaryOp, ir.ArrayAccess)}
    assignment = ir.format_assignment
    original_deref = evaluate.deref

    def deref(arg, regs, info, *, size, store=False):
        if isinstance(arg, ir.AddressMode) and info.is_stack_reg(arg.base):
            for base, (typ, length, name) in stack.items():
                if base <= arg.offset and arg.offset + size <= base + length:
                    root = info.get_stack_var(base, store=False)
                    if isinstance(root, ir.LocalVar):
                        info.add_local_var(root)
                        return ir.StructAccess(ir.AddressOf(root, root.type.reference()), arg.offset - base,
                                               size, None, info, ir.Type.any_field())
        return original_deref(arg, regs, info, size=size, store=store)

    def stack_offset(expr):
        expr = ir.late_unwrap(expr)
        if isinstance(expr, ir.Cast):
            return stack_offset(expr.expr)
        if isinstance(expr, ir.AddressOf) and isinstance(expr.expr, ir.LocalVar):
            return expr.expr.value
        if isinstance(expr, ir.BinaryOp) and expr.op in ('+', '-'):
            base = stack_offset(expr.left)
            right = ir.late_unwrap(expr.right)
            if base is not None and isinstance(right, ir.Literal):
                return base + right.value * (1 if expr.op == '+' else -1)
        return None

    def access(self, fmt):
        path = self.late_field_path()
        if path is None or path == [0]:
            return f'(*({ir.Type.ptr(self.type).format(fmt)})((u8 *)({self.struct_var.format(fmt)}) + {self.offset}))'
        return saved[ir.StructAccess](self, fmt)

    def cast(self, fmt):
        source = self.expr.type
        if self.reinterpret and source.is_float() != self.type.is_float():
            expr = ir.late_unwrap(self.expr)
            if isinstance(expr, (ir.GlobalSymbol, ir.StructAccess, ir.ArrayAccess, ir.LocalVar)):
                return f'(*({self.type.format(fmt)} *)&({expr.format(fmt)}))'
        if source.is_pointer_or_array() != self.type.is_pointer_or_array() and not source.is_float() and not self.type.is_float():
            return f'(({self.type.format(fmt)})({self.expr.format(fmt)}))'
        return saved[ir.Cast](self, fmt)

    def call(self, fmt):
        target = ir.late_unwrap(self.function)
        sig = target.type.get_function_pointer_signature()
        original = target
        while isinstance(original, ir.Cast):
            original = ir.late_unwrap(original.expr)
        known = signatures.get(original.c_symbol_name) if isinstance(original, ir.GlobalSymbol) else None
        known = known or signatures.get(target.format(fmt))
        if target.format(fmt) == 'M2C_STRUCT_COPY' and len(self.args) == 3:
            offset, size = stack_offset(self.args[0]), ir.late_unwrap(self.args[2])
            if offset in stack and isinstance(size, ir.Literal) and size.value == stack[offset][1]:
                typ, _, name = stack[offset]
                return f'{name} = *(const {typ} *)({self.args[1].format(fmt)})'
        if sig and sig.params is not None:
            args = []
            for i, arg in enumerate(self.args):
                text = ir.format_expr(arg, fmt)
                typ = known.args[i] if known and known.args is not None and i < len(known.args) else None
                if typ and '*' in typ:
                    text = f'({typ})({text})'
                elif i < len(sig.params) and sig.params[i].type.is_pointer():
                    text = f'({sig.params[i].type.format(fmt)})({text})'
                args.append(text)
            return f'{target.format(fmt)}({", ".join(args)})'
        return saved[ir.FuncCall](self, fmt)

    def binary(self, fmt):
        left, right = ir.late_unwrap(self.left), ir.late_unwrap(self.right)
        lp, rp = left.type.is_pointer_or_array(), right.type.is_pointer_or_array()
        # Scaled C indexing is represented by ArrayAccess. Remaining address
        # arithmetic in this IR retains the instruction's byte displacement.
        if self.op in ('+', '-') and (lp or rp):
            l, r = self.left.format(fmt), self.right.format(fmt)
            if lp and not rp:
                return f'((u8 *)({l}) {self.op} {r})'
            if rp and not lp and self.op == '+':
                return f'({l} + (u8 *)({r}))'
            return f'((s32)({l}) {self.op} (s32)({r}))'
        return saved[ir.BinaryOp](self, fmt)

    def array(self, fmt):
        target = self.ptr.type.get_pointer_target()
        if target and target.format(fmt) != self.type.format(fmt):
            size = target.get_size_bytes()
            if size:
                return f'(*({ir.Type.ptr(self.type).format(fmt)})((u8 *)({self.ptr.format(fmt)}) + ({self.index.format(fmt)}) * {size}))'
        return saved[ir.ArrayAccess](self, fmt)

    def assign(lhs, rhs, fmt):
        if lhs.type.is_pointer() or (rhs.type.is_pointer_or_array() and not lhs.type.is_pointer_or_array()):
            return f'{lhs.format(fmt)} = ({lhs.type.format(fmt)})({ir.format_expr(rhs, fmt)});'
        return assignment(lhs, rhs, fmt)

    ir.StructAccess.format, ir.Cast.format, ir.FuncCall.format = access, cast, call
    ir.BinaryOp.format, ir.ArrayAccess.format = binary, array
    ir.format_assignment = assign
    evaluate.deref = deref
    try:
        yield
    finally:
        for cls, method in saved.items():
            cls.format = method
        ir.format_assignment = assignment
        evaluate.deref = original_deref


def stack_context(p, fn, draft):
    """Transport aggregate stack objects already constrained by recovered call signatures."""
    index = recovered(p)
    frame = re.search(r'\bstwu r1, -(0x[0-9a-f]+|\d+)\(r1\)', '\n'.join(fn.asm))
    if not frame:
        return '', {}
    size = int(frame[1], 0)
    stack = {}
    for match in re.finditer(r'^\s+([\w ]+) loc_([0-9A-F]+);$', draft or '', re.M):
        typ, offset = match[1].strip(), int(match[2], 16)
        layout = index.layout(typ + ' *')
        if layout and layout[1] > 8 and offset + layout[1] <= size:
            stack[offset] = (typ, layout[1], f'loc_{offset:X}')
    if not stack:
        return '', {}
    cursor, fields = 0, []
    for offset, (typ, length, name) in sorted(stack.items()):
        if offset < cursor:
            return '', {}
        if offset > cursor:
            fields.append(f'char unk_{cursor:X}[{offset - cursor}];')
        fields.append(f'{typ} {name};')
        cursor = offset + length
    if cursor < size:
        fields.append(f'char unk_{cursor:X}[{size - cursor}];')
    return f'struct _m2c_stack_{fn.symbol.name} {{ ' + ' '.join(fields) + ' };\n', stack


def context(p, module, name, draft):
    index = recovered(p)
    source = None
    tus = p.module_config_dir(module) / 'tus.json'
    if tus.exists():
        tu = next((t for t in json.loads(tus.read_text())['tus'] if name in t['functions']), None)
        if tu:
            source = p.module_src_prefix(module) + '/' + tu['file']
            index = propagate(index, module, tu['functions'])
    fn = p.function_asm(module)[name]
    called = [m[1] for line in fn.asm if (m := re.search(r'\bbl (\w+)', line))
              and not re.match(r'_(save|rest)', m[1])]
    signatures = {n: sig for n in dict.fromkeys([name] + called)
                  if (sig := index.get(module, n, source))
                  and (n != name or not sig.origin.startswith('register-flow'))}
    parts = ['#include "types.h"'] + index.preamble(signatures.values())
    present = {re.sub(r'\s+', '', text) for text in parts}
    # The existing layout recovery supplies globals, not its guessed call arities.
    for piece in declarations(draft or ''):
        if piece.kind == 'type' or (piece.kind == 'object' and piece.text.lstrip().startswith('extern ')):
            normalized = re.sub(r'\s+', '', piece.text)
            if normalized not in present:
                parts.append(piece.text)
                present.add(normalized)
    parts += [sig.declaration(n) for n, sig in signatures.items()]
    return '\n'.join(parts) + '\n', signatures


def generate(p, module, name, draft=None, descending=False):
    from m2c.main import parse_flags, run
    from . import lift

    fn = p.function_asm(module).get(name)
    if fn is None:
        return None, 'no disassembly'
    if draft is None:
        draft = lift.lift_total(p, module, name, max_ins=max(1200, fn.symbol.size // 4))
    root = STATE_DIR / 'machine' / module / name
    root.mkdir(parents=True, exist_ok=True)
    asm = '.section .text\n.global ' + name + '\n' + name + ':\n'
    asm += '\n'.join(re.sub(r'^[0-9A-Fa-f]+: ', '', line) for line in fn.asm) + '\n'
    (root / 'input.s').write_text(asm)
    preamble, signatures = context(p, module, name, draft)
    stack_declaration, stack = stack_context(p, fn, draft)
    (root / 'context.c').write_text(preamble + stack_declaration)
    cpp = subprocess.run(['cc', '-E', '-P', '-I', str(ROOT / 'include'), str(root / 'context.c')],
                         capture_output=True, text=True, timeout=30)
    if cpp.returncode:
        return None, cpp.stderr[-2000:]
    (root / 'context.i').write_text(cpp.stdout)
    flags = ['-t', 'ppc-mwcc-c', '--valid-syntax', '--context', str(root / 'context.i'), str(root / 'input.s')]
    if descending:
        flags.append('--descending-regs')
    output, errors = io.StringIO(), io.StringIO()
    with redirect_stdout(output), redirect_stderr(errors), _mwcc_formatting(signatures, stack):
        code = run(parse_flags(flags))
    text = output.getvalue()
    (root / ('descending.raw.c' if descending else 'raw.c')).write_text(text)
    if code or 'Error while' in text:
        return None, text[-2000:] + errors.getvalue()[-1000:]
    text = _expand(text, 'M2C_FIELD', lambda a: f'(*({a[1]})((u8 *)({a[0]}) + ({a[2]})))')
    text = re.sub(r'\bM2C_UNK(8|16|32|64)?\b', lambda m: 's' + (m[1] or '32'), text)
    text = re.sub(r'\bCLZ\(', '__cntlzw(', text)
    text = _expand(text, 'MULTU_HI', lambda a: f'((u32)(((u64)(u32)({a[0]}) * (u64)(u32)({a[1]})) >> 32))')
    text = _expand(text, 'MULT_HI', lambda a: f'((s32)(((s64)(s32)({a[0]}) * (s64)(s32)({a[1]})) >> 32))')
    # The upstream compatibility header makes unhandled instructions no-ops and
    # bitwise casts numeric conversions. Such output is a draft, never a candidate.
    unresolved = sorted(set(re.findall(r'\b(?:M2C_\w+|GLUE_F64|MULTU?_HI|DMULTU?_HI)\b', text)))
    if unresolved:
        return None, 'unresolved: ' + ', '.join(unresolved)
    text = structure_loops(text)
    text = re.sub(r'\bgoto\s+(\w+);', r'goto \1; /* Preserves the retail branch. */', text)
    if fn.symbol.section == '.init':
        text = re.sub(r'(?m)^(\w[\w *]*\b' + re.escape(name) + r'\([^;]+\)\s*\{)',
                      r'__declspec(section ".init") \1', text)
    result = preamble + '\n' + text
    candidate = root / ('descending.c' if descending else 'candidate.c')
    candidate.write_text(result)
    from .lint import lint_file
    findings = lint_file(candidate)
    if findings:
        return None, '; '.join(f'{rule}:{line} {reason}' for rule, line, reason in findings)
    return result, ''
