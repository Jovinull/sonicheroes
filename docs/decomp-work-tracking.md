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
| Codex | `game/action.cpp` (begins `0x80018C0C`) | Complete; `pr-game-action-cpp` |
| Ares | `main/game/ares_800421b4.cpp` | Active; `ares/tu-main-game-ares_800421b4` |
| Ares | `actionstage`, `debug`, `e_pawn`, `e_spboss`, `eff_firedunk`, `newcamera`, `particlecore` onboarding workspaces | Active; reserved |
| Claude | Stage TU (exact file pending handoff) | Active; all stage TUs temporarily reserved to avoid overlap |
| Codex rapid lane 2 | `game/dAnim.cpp` (`0x800A7AE0`–`0x800A80E0`) | Active; `pr-game-danim-cpp` |
| Codex rapid lane 3 | `game/Endian.cpp` (`0x8004BECC`–`0x8004C160`) | Complete; `pr-game-endian-cpp` |
| Codex rapid lane 1 | RenderWare skeleton (`0x80011C20`–`0x8001234C`) | Complete; `pr-game-skeleton-cpp` |
| Codex rapid lane 3 | `game/GetSpParam.cpp` (`0x80130BC0`–`0x80130DF0`) | Complete; `pr-game-get-sp-param-cpp` |
| Codex rapid lane 1 | `game/hAnim.cpp` (`0x800BCE78`–`0x800BD1E8`) | Complete; `pr-game-hanim-cpp` |
| Codex rapid lane 3 | `game/moviePlay.cpp` (`0x801390A4`–`0x801391D0`) | Complete; `pr-game-movie-play-cpp` |
| Codex rapid lane 1 | `game/perf_ps.cpp` (provisional `0x8001EDE0`–`0x8001EECC`) | Active; branch pending |

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

The complete `action.cpp` reconstruction matches all 61 functions across its
five retail split objects. `ACTION::Loop` keeps the original 4,964-byte size and
uses a function-scope iterator aggregate with `opt_lifetimes off`; indexed task
loops preserve CodeWarrior's target `r29` cursor and `r30` counter/score
coloring without assembly or post-link code patches. The post-compile helper
restores the retail split symbols, redirects compiler-generated switch-table
references to the existing retail data slice, and removes CodeWarrior's
duplicate weak `BitFlag` destructor atom. It does not alter the instruction
bytes of any of the 61 retail functions. Four one-line continuation wrappers
compile the same source into the five original retail object fragments; this
preserves the original linker inputs while keeping one authoritative
`action.cpp` implementation.
