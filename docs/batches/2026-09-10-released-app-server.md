# Released-attempt retry — 2026-09-10

Started `deepseek-released-appserver-457-low-20260910` at 2026-09-10T16:11:48Z on the shared local Codex app server.

- Pool: 457 still-unmatched final releases, 153,864 retail bytes.
- Source batch: `deepseek-recovered-above90-128-low-20260910`. Its interrupted `fn_1_149E2C` was released with its best C preserved and included. `fn_80021930` was excluded because it had since been integrated.
- Every seed is the released attempt's saved reconstruction. Compiler settings come from release metadata (357), identical archived compiles (98), or the identical original seed (2).
- No size or score cutoff. Model concurrency: 457; local tool concurrency: 16.
- DeepSeek-V4.1-Flash, low reasoning effort, 16 checks, 4 stale checks, 7,200-second timeout.
- Live verification: every 60 seconds, with a final drain; all 16 hashes before source commits.
- Runner PID at launch: 7991. Tooling commit: `60cd067`.

The adjacent JSON records the command, source hashes, compiler options and attempt provenance. Runtime logs and eventual results are under `.fzgx/runs/deepseek-released-appserver-457-low-20260910/`; the runner log is `.fzgx/runs/deepseek-released-appserver-457-low-20260910.log`. These are launch settings, not final outcomes.
