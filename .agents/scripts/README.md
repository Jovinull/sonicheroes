# Agent scripts

Small, read-only or local helpers shared by every agent (Codex, Claude Code) and people.
Standard library only. They must not download, build, push or change Git settings unless their
own help says so, and they never write original-game data into the repository.

| script | what it does |
| --- | --- |
| `agent_doctor.py [--verify]` | Environment check with fixes: work branch, no extra worktrees, pre-commit hook enabled, correct disc in `orig/G9SE8P` (a PlayStation 2 image there is a FAIL), build tree, optional tools. `--verify` also checks the 18 artifact hashes of the current build. |

| `ps2sym.py` (+ `elfmini.py`) | Local lookups in your own PS2 `orig/ps2/SLUS_207.18` symbol table: `find`, `class`, `around` (source order), `section`, `files`, `missing` (PS2 C++ names the GameCube `symbols.txt` lacks) and `export` (local JSONL index in `build/ps2/`). Evidence for names/classes/boundaries only; output stays local (LEGAL.md). |

Run from the repository root, e.g. `python3 .agents/scripts/agent_doctor.py` or
`python3 .agents/scripts/ps2sym.py class TObjCamera --demangle`.
