# Decompilation work tracking

This file records active ownership so parallel decompilation work does not overlap.

| Owner | Scope | Status |
| --- | --- | --- |
| Claude Code | GX graphics library | Active; reserved |
| Codex | `game/skyfs_adx.c` (`0x80013038`–`0x80014154`) | Complete; `pr-skyfs-adx` |

The unified `advertiseD` reconstruction is complete on `pr-advertised`; do not
open the superseded per-function or per-file advertise branches.

`pr-skyfs-adx` supersedes `pr-module-loader` and the artificial
`state_set.cpp`, `dvd_status.cpp`, `module_loader.cpp`, `state_accessor.cpp`,
and `dlfs.c` splits.  The PS2 beta DWARF proves those ranges are one original
`skyfs_adx.c` translation unit.
