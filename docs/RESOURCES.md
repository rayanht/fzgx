# Resources and credits

## Tools this project is built on

- [decomp-toolkit](https://github.com/encounter/decomp-toolkit) — analysis, splitting, REL and disc tooling (encounter).
- [objdiff](https://github.com/encounter/objdiff) — object diffing and progress reports; powers [decomp.dev](https://decomp.dev).
- [wibo](https://github.com/decompals/wibo) — runs the CodeWarrior compilers on Linux and macOS.
- [dtk-template](https://github.com/encounter/dtk-template) — the project structure, `configure.py` and build system (CC0).
- [sjiswrap](https://github.com/encounter/sjiswrap) — Shift-JIS source wrapper (JPN builds).

## `line__.bin`

- [Line__Crypt](https://github.com/CosmoCortney/Line__Crypt) by CosmoCortney — documented the cipher over `enemy_line/line__.bin` and its per-region keys. `tools/linecrypt.py` is a reimplementation of the 32-bit LCG XOR stream, cross-checked against the retail loader stub's disassembly.
- [SMB_LZ_Tool](https://github.com/bobjrsenior/SMB_LZ_Tool) by bobjrsenior (Unlicense) — the Amusement Vision FF7-style LZSS shared with Super Monkey Ball. `tools/avlz.py` reimplements the decoder to mirror the retail routine.

## Reference decompilations

- [doldecomp/dolsdk2001](https://github.com/doldecomp/dolsdk2001) — Dolphin SDK; preferred reference for SDK units in main.dol.
- [doldecomp/melee](https://github.com/doldecomp/melee), [doldecomp/sms](https://github.com/doldecomp/sms), [doldecomp/mkdd](https://github.com/doldecomp/mkdd) — MSL, MetroTRK and middleware references.
- [camthesaxman/smb-decomp](https://github.com/camthesaxman/smb-decomp) — the closest engine relative (Amusement Vision). Read for vocabulary only: no licence, nothing copied.

### CARD source adaptation

The CARD implementations and Dolphin declarations are adapted from the CC0
[MKDD](https://github.com/SwareJonge/mkdd) and
[TWW](https://github.com/zeldaret/tww) SDK sources. Exact upstream files,
revisions, function identities and relocation bindings are recorded in
[`state/sdkimports/card.json`](../state/sdkimports/card.json). The complete
`CARDCheck.c`, `CARDCreate.c`, `CARDNet.c` and `CARDRdwr.c` files use MKDD;
`CARDOpen.c` uses TWW. All build includes belong to this repository under
`include/dolphin/`; upstream checkouts are only inputs to the import tool.

## Community knowledge (vocabulary only)

- [Manifold Project](https://github.com/RaphaelTetreault/ManifoldProject) by Raphael Tetreault — stage, collision and asset format work for F-Zero GX/AX.
- gc-forever and gamemasterplc code threads — memory addresses and their meanings for GFZE01.
- [The Cutting Room Floor: F-Zero GX](https://tcrf.net/F-Zero_GX) — leftover debug material.

## Community

- [GC/Wii Decompilation Discord](https://discord.gg/hKx3FJJgrV), `#dtk`.
- [decomp.dev](https://decomp.dev) — progress hub.
- [decomp.me](https://decomp.me) — per-function scratches.
