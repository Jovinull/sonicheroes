# Decompilation work tracking

This file records active ownership so parallel decompilation work does not overlap.

| Owner | Scope | Status |
| --- | --- | --- |
| Claude Code | GX graphics library | Active; reserved |
| Codex | `game/skyfs_adx.c` (`0x80013038`–`0x80014154`) | Complete; `pr-skyfs-adx` |
| Codex | `game/Peripheral.cpp` (`0x80014154`–`0x80015AC0`) | Complete; `pr-peripheral` (stacked on `pr-skyfs-adx`) |

The unified `advertiseD` reconstruction is complete on `pr-advertised`; do not
open the superseded per-function or per-file advertise branches.

`pr-skyfs-adx` supersedes `pr-module-loader` and the artificial
`state_set.cpp`, `dvd_status.cpp`, `module_loader.cpp`, `state_accessor.cpp`,
and `dlfs.c` splits.  The PS2 beta DWARF proves those ranges are one original
`skyfs_adx.c` translation unit.

`pr-peripheral` uses the PS2 beta DWARF to restore the original
`Peripheral.cpp` boundary and evidence-backed controller/demo names. It is
temporarily based on `pr-skyfs-adx` because the preceding TU owns the
`lbl_8042C0DC` small-data symbol required by the retail link.
