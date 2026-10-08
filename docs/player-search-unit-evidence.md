# Complete player search translation unit evidence

Symbolic metadata identifies player/player_search.cpp as C++ with exactly four
file-origin functions: SearchVanishedPlayers, CountVanishedPlayers,
SearchTheNearestRivalPlayer and SearchTheNearestLeaderPlayer. Their GameCube
implementations occupy 0x80041C5C–0x80041FF4, totaling 920 bytes. No PS2
instructions were inspected.

The first two functions traverse eight task pointers, testing signed task
mode 39. The first returns the requested vanished player's object; nonpositive
orders choose the first match. The counter returns the total. Rival search
excludes self, missing task pointers, same-team players and vanished players;
it compares squared distance, preserving the first match on ties. Leader
search traverses four teams and uses each team's current leader. It compares
vector length against a 10,000,000 initial threshold, also preserving ties.
Existing preconditions on player indices and pointers are retained.

All four symbolic definitions are accounted for. The preceding empty body
has no matching definition in this unit and is excluded. The next function
creates a pathname and opens a stream; it is not player-search code. Four
owned sections comprise 920 code bytes, 16 exception bytes, 24 exception-index
bytes and eight constant bytes. Both constants have exclusive references from
these functions. The inventory contains 32 relocations; no owned writable
storage or inlined ordinary definitions are omitted.

TASKWK mode and position offsets, PLAYERWK teamNo at 0x25C and team leaderNo
at 0x3A/member_player_no at 0x110 are corroborated by symbolic metadata and
GameCube accesses. External player/team definitions are deliberately partial
views. The original GameCube loops establish eight players and four teams.
Shared arrays and math helpers retain their existing address aliases.

All four functions match directly from C++ source with ordinary automatic
inlining. Metadata local declaration order recovers register allocation;
explicit component copies preserve the original floating-point loads/stores.
No object normalizer or assembly is introduced.

Verification: the full documented G9SE8P matrix compiled successfully: main DOL
and all seventeen REL targets. All eighteen output hashes match the reference.
The final ELF/map independently confirms all four function addresses and every
owned section byte. All 62 automated tests, language policy and object-step
policy checks pass. No runtime or physical-hardware validation is claimed.
