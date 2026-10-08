# Complete enemy player-search utility evidence

Positive C++ compilation-unit metadata for enemy/e_utility_search.cpp names
four namespace functions and their signed-int returns, vector parameters,
locals and relevant field types. No PS2 instructions were inspected.

| Function | GameCube address | Bytes |
| --- | --- | ---: |
| provisional fn_80103178 | 0x80103178 | 96 |
| nSearchPlayer::GetTeamNoFromPlayerNum | 0x801031D8 | 60 |
| nSearchPlayer::GetNearestLeaderPosition | 0x80103214 | 112 |
| nSearchPlayer::GetNearestPlayerNum | 0x80103284 | 160 |
| nSearchPlayer::GetNearestLeaderNum | 0x80103324 | 328 |

The complete reconstruction covers 756 text bytes through 0x8010346C,
24 exception bytes at 0x80009A10–0x80009A28 and 36 exception-index bytes
at 0x8000FF88–0x8000FFAC. No constants, initialized data or BSS belong here.
All four player/team pointer arrays remain external. Unemitted symbolic
ENEMY_CRASH_POWER storage is not invented in the GameCube unit.

Including the first helper is a documented ownership inference, not recovered
source-file metadata. The preceding 0x80102FB4–0x80103178 factory is positively
TObjEffCrash3D, anchored by its allocation, constructor and vtable. The next
0x8010346C stub belongs to TObjEffObi, anchored by its vtable and class string.
The intervening helper shares the named leader query's signed backup-leader
and member-index lookup and has player-query callers in enemy voice and flyer
strategy code. Its original name is unknown, so it retains an address-based
C ABI boundary within this C++ unit. Four named functions use their recovered
namespace and genuine C++ linkage.

The partial external structure views represent only verified fields. TASKWK
position is at 0x18; GameCube TObjOldPlayer embeds it at 0x6F0, so player
position is at 0x708. Its PLAYERWK starts at 0x760 and teamNo is at 0x25C,
giving 0x9BC. Signed PLAYERWK characterno at offset 1 has direct metadata
support. Team leaderNo_Backup is at 0x3B, distinct from leaderNo at 0x3A;
member_player_no is at 0x110, formation count at 0x120 and formation pointers
at 0x128. Older-platform full class sizes are not asserted for GameCube.

The first helper returns the selected leader's signed character number or -1
for the observed missing-team/player cases, without adding bounds checks.
Player-number to team-number lookup checks the original 0–7 range. Position
lookup copies the selected leader position only on success. Nearest-player
uses strict less-than distance comparisons; nearest-leader accepts equal
squared distances. The special-player fallback examines formation members
and returns the inner formation index, preserving the observed behavior even
though the ordinary path returns a global player index.

All five bodies match raw compiler output on the first attempt, with exact
owned sections and all 29 effective relocations. No normalizer, deferred
inlining or per-function compiler pragma is needed. The nine existing source
consumers receive only canonical symbol substitutions and formatting; their
preexisting loose declarations and call expressions remain unchanged.
Independent source, object, ownership and consumer reviews pass.

The full supported G9SE8P source-linked release matrix passes: main DOL and
all seventeen RELs match all eighteen expected artifact hashes. All 62
automated tests and the language/post-processor policies pass. Compilation and
binary comparison do not establish runtime or physical-hardware validation.
