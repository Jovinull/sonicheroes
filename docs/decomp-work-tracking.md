# Decompilation work tracking

Update this file when starting or handing off overlapping work. A row reserves
only the listed source files.

## Active

| Owner | Branch | Scope | Status |
|---|---|---|---|
| Claude Code (external checkout) | external | GX graphics library | Reserved; do not modify from this branch |

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

## Coordination rules

- AdvertiseD is delivered as one branch and one PR: `pr-advertised`.
- Use C++ unless there is positive evidence that the original source was C.
- A file is complete only when all code and owned data report 100% in objdiff.
- Do not add assembly implementations.
- Do not run worktree fleets or searches that retain thousands of object files.
