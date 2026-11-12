# Agent scripts

Small, read-only or local helpers shared by every agent (Codex, Claude Code) and people.
Standard library only. They must not download, build, push or change Git settings unless their
own help says so, and they never write original-game data into the repository.

| script | what it does |
| --- | --- |
| `agent_doctor.py [--verify]` | Environment check with fixes: work branch, no extra worktrees, pre-commit hook enabled, correct disc in `orig/G9SE8P` (a PlayStation 2 image there is a FAIL), build tree, optional tools. `--verify` also checks the 18 artifact hashes of the current build. |

| `ps2sym.py` (+ `elfmini.py`) | Local lookups in your own PS2 `orig/ps2/SLUS_207.18` symbol table: `find`, `class`, `around` (source order), `section`, `files`, `missing` (PS2 C++ names the GameCube `symbols.txt` lacks) and `export` (local JSONL index in `build/ps2/`). Evidence for names/classes/boundaries only; output stays local (LEGAL.md). |

| `try1.py SRC FUNC [--flags ...]` | Compile a scratch source with the real MWCC command and compare ONE function with the retail one WORD BY WORD (relocation fields masked, branch targets compared). Needs a built tree. `--flags` presets: `default`, `exc`, `ns` (units whose retail has extab), `fpoff`. Exit 0 only when identical. |
| `perm.py SRC FUNC [--flags ...]` | Try every order of the function's leading bare local declarations and rank them by word diffs: MWCC assigns saved registers and stack slots in declaration order, so many register-only diffs are a permutation. |
| `extabnew.py UNIT...` | After building a placed unit, compare retail extab/extabindex/.ctors sizes (from the split block in `splits.txt`) with ours. A unit can be EXACT per function and still fail the DOL hash when these differ. Read its output after the build. |

Run from the repository root, e.g. `python3 .agents/scripts/agent_doctor.py` or
`python3 .agents/scripts/ps2sym.py class TObjCamera --demangle`.
