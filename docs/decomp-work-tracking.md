# Decompilation work tracking

This file records active ownership so parallel decompilation work does not overlap.

| Owner | Scope | Status |
| --- | --- | --- |
| Codex 2026-10-06 | `game/matrix.cpp`, recovered matrix API declarations and symbol names | Complete locally on `decomp/whole-tu-20261006`: 16 functions, all seven owned sections and 104 relocations exact; full G9SE8P release and 18 hashes pass; publication pending |
| Codex 2026-10-06 | `game/calc_movcolli.cpp`, all three moving-collision functions | Active on `decomp/calc-movcolli-20261006`; complete draft: all three bodies compile; point routine/constants match, triangle/segment remain nonmatching; G9SE8P build, 55 tests and 18 original-linked hashes pass |
| Codex 2026-10-07 | `game/miscs.cpp`, complete eleven-function utility unit | Complete on PR #557; eleven source bodies exact, six compiler scalar atoms reordered; native DOL and all 17 RELs byte-identical |
| Codex 2026-10-07 | `game/calc.cpp`, complete interpolation and matrix-rotation unit | Complete on `decomp/calc-20261006`; eight bodies, seven source-exact; ten GetRotYXZ register fields normalized; all 18 native image hashes and 63 tests pass |
| Codex 2026-10-06 | `game/octreeColli.cpp`, complete collision-query unit | Active on `decomp/octree-colli-20261006`; PR #562 ready: all nine native functions, owned sections and 103 relocations exact; native G9SE8P build, 18 hashes, 55 tests and policies pass |
| Codex 2026-10-06 | `game/octree.cpp`, complete octree and collision-list unit | Ready on `decomp/octree-20261006`; all ten functions and owned sections native-match, 37 relocations exact; full G9SE8P build, 18 hashes, 55 tests and policies pass |
| Codex 2026-10-06 | `game/light.cpp`, complete CLIGHT/RP_Light unit | Complete on `decomp/light-20261006`; all 26 surviving bodies reconstructed at 0x80052184–0x80053FB8; 25 source-exact, ten register fields across seven Init instructions normalized; all 18 native image hashes and 63 tests pass |
| Codex 2026-10-06 | `game/gParam.cpp`, game parameter unit at `0x800663D0`–`0x80067050` | Active on `decomp/gparam-20261006`; complete: 27 functions and 191 relocations exact; native G9SE8P build, 18 hashes and 55 tests pass |
| Codex 2026-10-06 | `game/locateTable.cpp`, five functions and owned locator/timer tables | Active on `decomp/locate-table-20261006`; complete: five functions, owned data and 43 relocations exact; native G9SE8P build, 18 hashes and 55 tests pass |
| Codex 2026-10-07 | `game/enemy/e_database.cpp`, complete twelve-function enemy resource database | Complete on `decomp/e-database-20261007`; twelve source-exact methods, 2,380 text bytes, 67 exact relocations and all owned sections; all 18 native image hashes and 55 tests pass |
| Codex 2026-10-06 | `game/one.cpp`, complete ONEFILE archive unit | Complete on `decomp/one-20261006`; 25 GameCube bodies at `0x800BA7F8–0x800BCE78`, including two platform-specific methods; all 25 bodies source-exact, with 422 relocations and exception metadata exact; all 18 native image hashes and 55 tests pass |
| Codex 2026-10-06 | `game/misc.cpp`, `0x800D5844`–`0x800D7B18`, complete 30-function unit | Active on `decomp/misc-20261006`; complete candidate integrated; 26/30 functions exact, four geometry helpers pending; original object linked; G9SE8P build, 55 tests and 18 hashes pass |
| Codex 2026-10-06 | `game/c_colli_react.cpp`, complete collision reactor unit | Complete Matching C++ reconstruction; 42 bodies, all owned sections and linked image exact with documented single-inline-atom normalization; PR preparation |
| Codex 2026-10-06 | `game/scanpath.cpp`, complete path scanning/manager unit | Reserved on `decomp/scanpath-20261006`; sixteen surviving bodies at `0x800AEE80–0x800B13EC`, plus six inlined metadata methods; owned sections and reconstruction pending |
| Codex 2026-10-06 | `game/pathctrl.cpp`, complete CLASS_PATH control unit | Active on `decomp/pathctrl-20261006`; eight surviving GameCube bodies at `0x800ADC3C–0x800AEE80`; all eight bodies reconstructed, four lifecycle bodies exact; draft NonMatching, full supported build, 18 hashes and 55 tests pass |
| Codex 2026-10-06 | `game/message.cpp`, complete GameCube font/message unit | In progress on `decomp/message-20261006`; complete: nine surviving functions, eight owned sections and 141 relocations exact; native G9SE8P build, 18 hashes and 55 tests pass |
| Claude Code | GX graphics library | Active; reserved |
| Codex | `game/cri/axrna.c` | Attempted; no net improvement after source-form and compiler-flag trials |
| Codex | `game/cri/svm.c` | Attempted; BSS layout identified, but no net object improvement |
| Codex | `game/cri/rnares.c` | Attempted; aggregate evidence retained, no text improvement without synthetic layout code |
| Codex | `game/rw_gcn_raster.c` | Complete for now; PR #497 took the unit 17.8% -> 28.4% matched (30/47 functions). What is left is register allocation, not structure |
| Claude Code | `game/rw_gcn_core.c` | Active; reserved |
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
| Codex root lane | `game/SpAdvStgFailed.cpp` (`0x8013B76C`–`0x8013BC78`) | Complete; `pr-game-sp-adv-stg-failed-cpp` |
| Codex rapid lane 1 | `game/perf_ps.cpp` (provisional `0x8001EDE0`–`0x8001EECC`) | Active; branch pending |
| Codex | `rel/o_invoke_colli.cpp` (`TObjSetInvokeColli`, nine stage overlays) | Complete; `pr-stage-common-o-invoke-colli-cpp` |

The unified `advertiseD` reconstruction is complete on `pr-advertised`; do not
open the superseded per-function or per-file advertise branches.

## Completed on `pr-advertised`

| Scope | Verification |
|---|---|
| Complete `advertiseD` overlay | 434/434 source functions; all 21 source objects `Matching`; exact REL and DOL hashes |
| Linked sections and relocations | Exact retail section sizes and byte-identical `.text`, `.rodata`, and `.data` layout |
| `adv_title.cpp` | 30/30 functions; exact source order, code, owned data, and linked ranges |
| `adv_player.cpp` | 21/21 functions; exact code, data, symbol order, and relocation targets |
| `adv_story.cpp`, `adv_story_tail.cpp` | 33/33 functions; exact object split, code, data, and symbol addresses |
| `adv_challenge.cpp` | 78/78 functions and exact owned sections |
| Remaining code and data objects | All functions and owned sections report 100% |

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

## Coordination rules

- Use C++ for game-owned code unless positive evidence establishes C.
- A file is complete only when all code and owned data report 100% in objdiff.
- Do not add assembly implementations.
- Do not run overlapping work without reserving the exact scope in this file.

## Completed: native LSC family correction

The coordinated `game/cri/lsc_err.c`, `lsc.c`, `lsc_ini.c` and
`lsc_svr.c` correction covers all 26 functions at
`0x8021F410–0x80220544`, with inferred original source boundaries and
complete owned storage. All 44 meaningful symbols and 150 relocations match,
without synthetic padding, per-function pragmas or an instruction patcher.
All-source and source-linked G9SE8P release builds, 54 tests, both policies
and all eighteen artifact hashes pass. See
[the detailed audit](cri-lsc-native-audit.md). No subset of this boundary
correction is claimed separately.

## 2026-09-25 completed-branch consolidation

Codex root owns `integrate-cri-complete-20260925`, based on upstream main
`4243c6c`. It consolidates the nine already-completed CRI changes behind
PRs #515–#523 into fourteen complete units. The older error-reporter partial
is superseded by LSC's `lsc_err.c`; the stacked LSC ancestors are included
once. Partial raster, GCCI, MFCI and RenderWare worktrees remain untouched.
The integration also propagates the recovered adapter callback type through
AXRNA and corrects ten private SVM constant bindings after a reference audit.
See [the integration proof](cri-integration-20260925.md) for exact scope,
duplicate handling, all-target verification and limits. This entry supersedes
older completed-unit publication statuses above; it does not claim an upstream
merge until the remote accepts it.
