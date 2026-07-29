# Decompilation work tracking

This file records active ownership so parallel decompilation work does not
overlap.

| Owner | Scope | Status |
| --- | --- | --- |
| Claude Code | GX graphics library | Active; reserved |
| Claude Code | Stage translation unit | Active; stage work reserved |
| Codex | `game/action.cpp` | Active; `pr-game-action-cpp` |
| Codex agent | RenderWare skeleton (`0x80011C20`–`0x8001234C`) | Active; reserved |
| Codex agent | `game/Endian.cpp` (`0x8004BECC`–`0x8004C160`) | Complete; `pr-game-endian-cpp` |
| Codex agent | `game/dAnim.cpp` (`0x8003B7C8`–`0x8003C640`) | Active; reserved |

The unified `advertiseD` reconstruction is complete on `pr-advertised`; do not
open superseded per-function or per-file advertise branches.
