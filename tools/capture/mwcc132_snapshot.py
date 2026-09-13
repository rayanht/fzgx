"""GDB-side capture for GC/1.3.2 mwcceppc.exe: a coloring-only port of the recovery project's
allocator_snapshot reader. Layouts and addresses were derived from the 1.3.2 binary (capstone)
and from live memory in the fzgx-capture VM (CLAUDE.md, 2026-09-13). Writes the same file
names/schemas as the 1.2.5 capture so simplify_replay.py, autotarget.py and the solver work.

Usage (inside gdb-multiarch attached to the qemu-i386 stub):
  python import sys; sys.path.append('/Users/rayan/mwcc/tools'); sys.path.append('/Users/rayan/fzgx/tools/capture')
  source /Users/rayan/fzgx/tools/capture/mwcc132_snapshot.py
  mwcc132-capture OUTPUT_DIR
  continue
"""
import json, struct, sys
from pathlib import Path
import gdb
import allocator_snapshot as base

TARGET_132 = "GC/1.3.2"
CLASS_GPR, CLASS_FPR, CLASS_VR = 4, 3, 2
COUNTS = 0x5E8A7C
COALESCE_FIRST, COALESCE_LAST = 0x5E7FC8, 0x5E86A8
base.SUPPORTED_TARGETS["132"] = TARGET_132
base.PCODE_BLOCKS_ADDRESS = 0x5E87B0
base.INTERFERENCE_GRAPH_ADDRESS = 0x5E87D0
base.COALESCED_REGISTERS_ADDRESS = 0x5E21C8
base.PCODE_OPCODE_DESCRIPTORS_ADDRESS = 0x5BEE78
base.PCODE_MAX_OPCODE = 0x260
base.VIRTUAL_REGISTER_COUNT_ADDRESSES = {"gpr": COUNTS + 4 * CLASS_GPR, "fpr": COUNTS + 4 * CLASS_FPR, "vr": COUNTS + 4 * CLASS_VR}
base.INITIAL_OBJECT_REGISTER_LAST_ADDRESSES = {"gpr": COUNTS + 4 * CLASS_GPR, "fpr": COUNTS + 4 * CLASS_FPR, "vr": COUNTS + 4 * CLASS_VR}  # unknown in 1.3.2: reported as the count
base.COALESCE_RANGE_ADDRESSES = {0: (COALESCE_FIRST + 4 * CLASS_GPR, COALESCE_LAST + 4 * CLASS_GPR), 1: (COALESCE_FIRST + 4 * CLASS_FPR, COALESCE_LAST + 4 * CLASS_FPR), 9: (COALESCE_FIRST + 4 * CLASS_VR, COALESCE_LAST + 4 * CLASS_VR)}


class Reader132(base.SnapshotReader):
    def __init__(self, read_memory):
        super().__init__(read_memory, compiler=TARGET_132, target_sha256="132")

    def opcode_descriptor(self, opcode):
        cached = self._opcode_descriptors.get(opcode)
        if cached is not None:
            return cached
        if opcode < 0 or opcode > base.PCODE_MAX_OPCODE:
            raise base.SnapshotError(f"invalid PCode opcode 0x{opcode:x}")
        raw = self._read(base.PCODE_OPCODE_DESCRIPTORS_ADDRESS + opcode * 0x12, 0x12)
        mnemonic_address, format_address = struct.unpack_from("<II", raw)
        fmt = self.c_string(format_address) if format_address else ""
        d = {"mnemonic": self.c_string(mnemonic_address) if mnemonic_address else f"op{opcode}",
             "operand_format": fmt, "fixed_operand_count": raw[8], "unknown_09": raw[9],
             "flags": struct.unpack_from("<H", raw, 0x0A)[0], "encoding": f"0x{struct.unpack_from('<I', raw, 0x0E)[0]:08x}"}
        try:
            d["operand_schema"] = base.decode_operand_format(fmt)
        except Exception:
            d["operand_schema"] = {"dynamic_operand_count": False, "operands": []}
        self._opcode_descriptors[opcode] = d
        return d

    def operand(self, address):
        raw = self._read(address, 0x0C)
        return {"kind": raw[0], "class": raw[1], "flags": struct.unpack_from("<H", raw, 2)[0],
                "reg": struct.unpack_from("<h", raw, 4)[0], "value_signed": struct.unpack_from("<i", raw, 4)[0],
                "value_unsigned": struct.unpack_from("<I", raw, 4)[0], "object": f"0x{struct.unpack_from('<I', raw, 8)[0]:08x}", "raw": raw.hex()}

    def instruction(self, address):
        header = self._read(address, 0x24)
        opcode = struct.unpack_from("<h", header, 0x20)[0]
        operand_count = struct.unpack_from("<h", header, 0x22)[0]
        if operand_count < 0 or operand_count > 4096:
            raise base.SnapshotError(f"invalid operand count {operand_count} at 0x{address:08x}")
        return {"address": f"0x{address:08x}", "next": struct.unpack_from("<I", header, 0)[0],
                "previous": struct.unpack_from("<I", header, 4)[0], "block": struct.unpack_from("<I", header, 8)[0],
                "definition_index": struct.unpack_from("<I", header, 0x10)[0], "opcode": opcode,
                "opcode_descriptor": self.opcode_descriptor(opcode), "flags": struct.unpack_from("<I", header, 0x14)[0],
                "operands": [self.operand(address + 0x24 + i * 0x0C) for i in range(operand_count)]}

    def interference_node(self, address):
        header = self._read(address, 0x1A)
        count = struct.unpack_from("<h", header, 0x18)[0]
        if count < 0 or count > 32767:
            raise base.SnapshotError(f"invalid neighbor count {count} at 0x{address:08x}")
        nd = self._read(address + 0x1A, count * 2)
        return {"address": f"0x{address:08x}", "next": struct.unpack_from("<I", header, 0)[0],
                "object": f"0x{struct.unpack_from('<I', header, 4)[0]:08x}", "spill_cost": struct.unpack_from("<i", header, 8)[0],
                "virtual_register": struct.unpack_from("<h", header, 0x10)[0], "degree": struct.unpack_from("<h", header, 0x12)[0],
                "physical_register": struct.unpack_from("<h", header, 0x14)[0], "flags": struct.unpack_from("<H", header, 0x16)[0],
                "neighbors": [struct.unpack_from("<h", nd, i * 2)[0] for i in range(count)]}

    def reaching_definitions(self, blocks):
        return None

    def object_name(self, address):
        """The C name of a compiler object (named local or parameter), or '' for a temp."""
        if not address:
            return ""
        try:
            data = self.u32(address + 0x0A)
            raw = self._read(data, 64) if data else b""
        except Exception:
            return ""
        import re as _re
        m = _re.search(rb"[ -~]{2,}", raw[10:])
        return m.group(0).decode() if m else ""

    def coloring_snapshot(self, reg_class, simplify_stack, program_counter=0):
        snap = super().coloring_snapshot(reg_class, simplify_stack, program_counter)
        for node in snap["nodes"]:
            node["name"] = self.object_name(int(node["object"], 16))
        return snap

    def pcode_stage(self, phase, pc):
        return {"format": "mwcc-pcode-stage-v1", "compiler": TARGET_132, "phase": phase, "program_counter": f"0x{pc:08x}",
                "blocks": self.blocks()}


def _write(path, data):
    path.write_text(json.dumps(data, indent=1))


class Session:
    def __init__(self, output):
        self.output = Path(output); self.output.mkdir(parents=True, exist_ok=True)
        self.index = 0; self.attempt = 0; self.stack = 0
        inf = gdb.selected_inferior()
        self.reader = Reader132(lambda a, n: bytes(inf.read_memory(a, n)))

    def allocate(self):
        self.index += 1; self.attempt = 0
        pc = int(gdb.parse_and_eval("$pc"))
        snap = self.reader.snapshot(0, pc)
        _write(self.output / f"allocator-{self.index:04d}.json", snap)
        _write(self.output / f"pcode-{self.index:04d}-scheduled.json", self.reader.pcode_stage("scheduled", pc))
        print(f"captured allocator {self.index}: {sum(len(b['instructions']) for b in snap['blocks'])} instructions, {snap['virtual_register_counts']} vregs")

    def select(self):
        cls = self.reader.u8(0x5E931F)
        if cls != CLASS_GPR:
            return
        self.attempt += 1
        esp = int(gdb.parse_and_eval("$esp"))
        self.stack = self.reader.u32(esp + 4)
        snap = self.reader.coloring_snapshot(0, self.stack, int(gdb.parse_and_eval("$pc")))
        _write(self.output / f"coloring-{self.index:04d}-gpr-{self.attempt:02d}-before.json", snap)
        ret = self.reader.u32(esp)
        ReturnBreakpoint(ret, self)
        print(f"captured coloring {self.index} attempt {self.attempt} before: {len(snap['nodes'])} nodes, {len(snap['simplify_order'])} in simplify order")

    def select_done(self):
        snap = self.reader.coloring_snapshot(0, self.stack, int(gdb.parse_and_eval("$pc")))
        _write(self.output / f"coloring-{self.index:04d}-gpr-{self.attempt:02d}-after.json", snap)

    def final(self):
        _write(self.output / f"pcode-{self.index:04d}-final.json", self.reader.pcode_stage("final", int(gdb.parse_and_eval("$pc"))))
        print(f"captured final PCode {self.index}")


class ReturnBreakpoint(gdb.Breakpoint):
    def __init__(self, address, session):
        super().__init__(f"*{address:#x}", temporary=True, internal=True); self.session = session
    def stop(self):
        self.session.select_done(); return False


class HookBreakpoint(gdb.Breakpoint):
    def __init__(self, address, session, method):
        super().__init__(f"*{address:#x}", internal=True); self.session = session; self.method = method
    def stop(self):
        try:
            getattr(self.session, self.method)()
        except Exception as e:
            print(f"capture error in {self.method}: {e}")
        return False


class Mwcc132Capture(gdb.Command):
    """mwcc132-capture OUTPUT_DIR"""
    def __init__(self):
        super().__init__("mwcc132-capture", gdb.COMMAND_USER)
    def invoke(self, argument, from_tty):
        s = Session(argument.strip())
        HookBreakpoint(0x5077B0, s, "allocate")
        HookBreakpoint(0x507A30, s, "select")
        HookBreakpoint(0x433FC8, s, "final")  # reconvergence after the FINAL CODE dump block
        print("mwcc132 capture armed")


Mwcc132Capture()
