# Decompilation work tracking

This file records active ownership so parallel decompilation work does not overlap.

| Owner | Scope | Status |
| --- | --- | --- |
| Claude Code | GX graphics library | Active; reserved |
| Codex | `game/skyfs_adx.c` (`0x80013038`–`0x80014154`) | Complete; `pr-skyfs-adx` |
| Codex | `game/Peripheral.cpp` (`0x80014154`–`0x80015AC0`) | Complete; `pr-peripheral` (stacked on `pr-skyfs-adx`) |
| Codex | `game/main.cpp` (`0x80015AC0`–`0x80016514`) | Complete; `pr-game-main-cpp` |
| Codex agents | `game/Task.cpp` (`0x80016514`–`0x800189A4`) | Complete; `pr-game-task-cpp` |
| Codex | `game/Memory.cpp` (`0x800189A4`–`0x80018C0C`) | Complete; `pr-game-memory-cpp` |
| Codex | `game/action.cpp` (begins `0x80018C0C`) | Active; taking over stale empty `ares/wip-action` placeholder |
| Ares | `main/game/ares_800421b4.cpp` | Active; `ares/tu-main-game-ares_800421b4` |
| Ares | `actionstage`, `debug`, `e_pawn`, `e_spboss`, `eff_firedunk`, `newcamera`, `particlecore` onboarding workspaces | Active; reserved |

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

`pr-game-main-cpp` reconstructs all three functions and every owned section.
The PS2 beta DWARF positively identifies the original source as C++, and the
following `Task.cpp` method order fixes the end of `main.cpp` at
`TMainTask::Reset` (`0x80016514`). The complete object and all 18 linked
artifacts are exact.

The complete `Task.cpp` end is fixed at `0x800189A4`: PS2 beta DWARF places
`THeapCtrl::Free` and every following heap method in `Memory.cpp`. All 34
`Task.cpp` functions and every owned section are byte-perfect.
The source retains the C++ classes, virtual tables, global constructor, and
exception metadata identified by the PS2 beta DWARF and independently
correlated against the GameCube object.
