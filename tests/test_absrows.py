import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))

from fzgx import oracle  # noqa: E402
from fzgx.api import lint_repair  # noqa: E402


def _row(text, reloc_sym=None, kind="DIFF_ARG_MISMATCH"):
    ins = {"formatted": text}
    if reloc_sym is not None:
        ins["relocation"] = {"target_symbol": reloc_sym, "addend": 0}
    return {"diff_kind": kind, "instruction": ins}


def test_abs_rows_accept_resolved_literals(monkeypatch):
    monkeypatch.setattr(oracle, "_ABS_SYMS", {"__DIRegs": 0xCC006000, "__viReg": 0xCC002000})
    right = {"symbols": [{"name": "__DIRegs"}]}
    lrows = [_row("lis r3, 0xcc00"), _row("addi r3, r3, 0x6000"), _row("lwz r0, 0x24(r3)", kind="DIFF_NONE"), _row("lis r4, 0xcc01")]
    rrows = [_row("lis r3, __DIRegs@ha", 0), _row("addi r3, r3, __DIRegs@l", 0), _row("lwz r0, 0x24(r3)", kind="DIFF_NONE"), _row("lis r4, __DIRegs@ha", 0)]
    assert oracle._abs_rows(right, lrows, rrows) == {0, 1}


def test_abs_rows_signed_low_half(monkeypatch):
    monkeypatch.setattr(oracle, "_ABS_SYMS", {"__x": 0xCC00A000})  # low half >= 0x8000: ha carries
    right = {"symbols": [{"name": "__x"}]}
    lrows = [_row("lis r3, 0xcc01"), _row("addi r3, r3, -0x6000")]
    rrows = [_row("lis r3, __x@ha", 0), _row("addi r3, r3, __x@l", 0)]
    assert oracle._abs_rows(right, lrows, rrows) == {0, 1}


def test_lint_repair_adds_allow_comment_per_line():
    text = "int x;\n    y = *(u32 *)0x800000F8;\n    volatile u32 z;\n"
    out = lint_repair(text, [("f", "A1", 2, "m"), ("f", "A2", 2, "m"), ("f", "S2", 3, "m"), ("f", "A3", 1, "m")])
    lines = out.split("\n")
    assert lines[0] == "int x;"
    assert lines[1].endswith("/* fzgx-allow: A1,A2 unnamed OS/hardware memory */")
    assert lines[2].endswith("/* fzgx-allow: S2 memory-mapped register */")
