# Recovered-candidate DeepSeek batch

Batch `deepseek-recovered-above90-128-low-20260910` launched at 14:45 UTC on
2026-09-10 with runner PID 9298. Active-run metadata is in
`.fzgx/runs/deepseek-recovered-above90-active.json`; the runner log is
`.fzgx/runs/deepseek-recovered-above90-128-low-20260910.log`.
It contains 578 unfinished functions / 189,808 bytes with historical C match
scores strictly above 90%. There is no size cap or SDK exclusion. Sizes range
from 28 to 4,224 bytes; 74 functions / 63,516 bytes are at least 512 bytes.

`tools/seeds/recovered.py` combines attempt bodies, compiler check archives,
saved lifter results, owned SDK imports, deterministic repairs, sweep caches
and spelling results. The ledger alone supplies 513 eligible functions;
saved generated candidates add 65. Donor similarity rankings do not qualify.
Each worker receives the existing reconstruction and its compiler settings.
The selector freezes source hashes and records both historical and current
scores, including provenance for old attempts whose body paths were missing.

All 578 selected seeds compiled against the current headers and retail objects.
The initial check left 32 at or below 90%; checking 45 alternate saved candidates
reduced that to 29. These remain included because their historical scores
qualify; 549 selected seeds currently exceed 90%. Lint reported zero findings
and the existing build passed all 16 target hashes. No unit tests were added.

The batch uses DeepSeek-V4.1-Flash (`deepseek-flash`), 128 concurrent Codex
workers, `low` reasoning, 16 checks, four consecutive stale checks and a
7,200-second worker timeout. The claim attempt cap remains 100. The orchestrator
dry run selected all 578 symbols; its worker command requests `low` explicitly.
Personal Codex configuration and authentication were not changed.

Local artifacts are under `.fzgx/seeds/deepseek-recovered-above90-128-low/`:
`manifest.json`, frozen C, `selection.json`, `alternates.json`, `summary.json`,
`batch.json` and `launch.sh`. Preparation is reproducible from the saved corpus:

```sh
uv run tools/seeds/recovered.py --above 90 --output NEW_OUTPUT_DIRECTORY
```

The launch command is:

```sh
uv run tools/orchestrate.py --harness codex --provider deepseek \
  --model deepseek-flash --api-key-file ~/.config/fzgx/deepseek.key \
  --parallel 128 --effort low --timeout 7200 \
  --max-checks 16 --max-stale 4 --max-attempts 100 \
  --seeds .fzgx/seeds/deepseek-recovered-above90-128-low/manifest.json \
  --no-trivial --batch deepseek-recovered-above90-128-low-20260910
```
