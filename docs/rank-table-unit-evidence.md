# rankTable.cpp unit evidence

The symbolic debug metadata names `D:\Tsonic\Tsonic\src\rankTable.cpp`
and explicitly records `language=C_PLUS_PLUS`. Its three global functions are
`GetADXForRank(int)`, `CheckTimeRank(int, int, int)`, and
`CheckScoreRank(int, int)`. Five private table definitions are also named.
No PS2 instruction bytes were used.

The corresponding complete GameCube text range is `0x8012D440–0x8012D97C`:

| Function | Address | Size |
| --- | --- | --- |
| GetADXForRank | 0x8012D440 | 132 |
| CheckTimeRank | 0x8012D4C4 | 700 |
| CheckScoreRank | 0x8012D780 | 508 |

The five tables occur consecutively in `.data` at `0x8028A2C0`, `0x8028A4DC`,
`0x8028A608`, `0x8028A74C`, and `0x8028A864`, with sizes 540, 300, 324, 280,
and 20 bytes. A 36-byte compiler-generated switch table follows at
`0x8028A878`. Thus owned data ends at `0x8028A89C`; the next four bytes are
alignment before a neighboring unit's table. There are no owned exception,
constant-pool, or zero-initialized sections. The unit has 32 text relocations
and nine switch-table relocations.

The metadata establishes the score records' signed-short `[team][rank]`
qualifications and the time records' signed-byte `[team][rank][minute/second]`
qualifications. Retail GameCube data and loop bounds establish row counts
15, 15, 9, and 14 respectively; these differ from the earlier PS2 tables.
All initializer values come from the GameCube data. Public return types and
voice enum labels follow symbolic metadata.

External views expose the accessed portions of Action, teamTOp and pModeSwitch.
GameCube loads establish currentStageNo at Action+0x2C, teamKind at team+0x34,
and the mission selector byte at pModeSwitch+0x28. These globals remain
externally owned. The retail routines deliberately omit rank/team bounds
checks, use signed comparisons, return -1 for an unsupported mission/team or
missing stage, and use the original strict score and inclusive time thresholds.

The three source functions compile without deferred inlining or any object
normalizer. The single-object audit confirms identical complete text and data,
all three function bindings/offsets/sizes, and all 41 effective relocations.
Independent full-object and source/metadata review passes. The supported
G9SE8P main DOL and all seventeen RELs compile; all eighteen reference hashes
pass. All-source compilation, progress/report generation, 62 automated tests
and both policies pass. Compilation and binary comparison do not establish
runtime or physical-hardware validation.
