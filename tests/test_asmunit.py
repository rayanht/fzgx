import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))

from fzgx.asmunit import fix_branch_hints  # noqa: E402
from fzgx.carve import order_labels_after_functions  # noqa: E402


def test_backward_hinted_branch_is_respelled():
    src = (
        "/* 80005E74 00002E74  40 A2 FF EC */\tbne+ .L_80005E60\n"   # backward, y=1
        "/* 80024F90 00024F90  40 A2 00 08 */\tbne+ .L_80024F98\n"   # forward, y=1: unchanged
        "/* 80005E60 00002E60  40 82 FF EC */\tbne .L_80005E60\n"    # backward, y=0: unchanged
    )
    out, n = fix_branch_hints(src)
    lines = out.splitlines()
    assert n == 1
    assert lines[0].startswith("/* 80005E74 00002E74  40 A2 FF EC */\tbne- .L_80005E60")
    assert lines[1].endswith("bne+ .L_80024F98")
    assert lines[2].endswith("bne .L_80005E60")


def test_function_line_moves_before_same_address_label(tmp_path):
    p = tmp_path / "symbols.txt"
    p.write_text(
        "__OSDBINTEND = .text:0x8000AA2C; // type:label scope:global\n"
        "fn_8000AA2C = .text:0x8000AA2C; // type:function size:0x4\n"
        "other = .text:0x8000AA30; // type:label scope:global\n"
    )
    assert order_labels_after_functions(p) is True
    lines = p.read_text().splitlines()
    assert lines[0].startswith("fn_8000AA2C =") and lines[1].startswith("__OSDBINTEND =") and lines[2].startswith("other =")
    assert order_labels_after_functions(p) is False  # idempotent
