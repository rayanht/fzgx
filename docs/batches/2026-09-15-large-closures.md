# Selection panel closure — 2026-09-15

Compared with `f40101f2`, this pass adds **one exact function / 4,156 bytes
linked from C**: `fn_10_1C2D8`, previously blocked at 71 differing words and
21 shape edits. Commit `1e98cbbc` contains the accepted source and its required
oracle and arithmetic repairs. No agents were launched, issues opened or commits pushed.

## What closed it

- The saved candidate computed `input * (53 + 74)` instead of
  `input * 53 + 74`. The shared `through_local` generator now checks operator
  precedence before proposing compound assignment.
- Its data view pointed into rodata. Native initialized objects reproduce the
  data-base setup and access lifetimes. The complete **23,128-byte** data prefix
  contains **867 pointer bindings**, including **93 in anonymous DTK objects**.
  All initialized bytes and pointer destinations are proved. Private layout
  copies are externalized; shared data ownership is unchanged.
- Four-byte color objects restore pooled integer loads. Completing nested calls
  before selecting localized strings fixes repeated address lifetimes. An inline
  indexed lookup closes the last four register differences.
- The oracle and data generator now inspect anonymous `pad_` and `gap_` objects
  through the same payload path as named objects. They cannot substitute zeros
  for unnamed pointer tables.

The reusable native-data generator independently turns a corrected extern-view
candidate from **7 words / 3 shape edits to an exact match**. It preserves field
types, measures layouts with MWCC, and emits symbolic relocation initializers.
String views spanning pointer tables retain their byte view through a union.
Thirteen other saved large candidates produced no eligible variants; this is
not evidence that all large functions can be repaired by the same transformation.

## Adjacent work remains open

| Function | Bytes | Before words / shape | After words / shape |
| --- | ---: | ---: | ---: |
| `fn_10_1D314` | 4,228 | 363 / 93 | 121 / 15 |
| `fn_10_1BFC4` | 788 | 92 / 15 | 22 / 16 |

The second panel needed a fixed float parameter before variadic arguments,
complete native data, and automatic color initializers. Splitting grouped local
declarations exposed ten locals to compiler-graph analysis without changing the
instructions. Row-value and attribute-index lifetimes account for further
improvements. Two loops still hoist X-coordinate calculations that retail keeps
inside the loop; coordinate and conversion-register lifetimes also differ.

The 788-byte function had fabricated variadic state, a buffer with the wrong
extent, and descriptor fields displaced by 68 bytes. It now uses the EABI
argument cursor, a 512-byte buffer and measured field offsets. Its 832-byte
stack frame matches retail; entry scheduling and conversion operands remain
different. Compiler, declaration-order and cursor-representation probes did
not close it. The potential 5,700-byte contiguous region is **not closed**.

The refreshed 9,832-byte `fn_1_BC310` still differs by 1,182 words / 341 shape
edits; its percentage concealed extensive structural errors. The 7,680-byte
`fn_3_15A0` has 855 / 288, and the 6,192-byte `fn_1_BA144` has 245 / 66.
The title state machine remains at 155 / 10 and movie cleanup at 95 / 3;
native-pool and helper-lifetime experiments did not improve their saved bests.
These functions are not counted as new matched bytes.

## Reproduction and checks

The portable archive contains the accepted source, original and corrected
adjacent candidates, generator recipes, and three negative oracle probes:
missing anonymous pointers, an altered anonymous destination, and an altered
initialized byte. All three have exact instruction streams and must be rejected.
The arithmetic generator recipe must retain the exact accepted instruction stream.

```sh
uv run tools/fzgx.py fixup --archive state/repairs/large_closures_20260915.json.gz
uv run python configure.py
ninja
build/tools/dtk shasum -q -c config/GFZE01/build.sha1
uv run tools/fzgx.py lint
uv run tools/fzgx.py snapshot
```

Numeric results and source hashes are in the adjacent JSON. Partial candidates
are archived for continued work; they have not been integrated into the game.

Validation completed: all ten archived bodies reproduce their scores and expected
oracle results; the full hash check prints `16 files OK`; lint reports zero
findings. The snapshot records 5,014 matched functions, 2,166 unmatched,
14 blocked and 114 assembly units. Four previously accepted pool matches remain.
