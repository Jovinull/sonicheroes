# locateTable.cpp unit evidence

Symbolic debug metadata identifies `D:\Tsonic\Tsonic\src\locateTable.cpp`
with `language=C_PLUS_PLUS`, five public functions, four public locator tables,
public DemoLocator storage, and two private timer tables. Only symbolic PS2
metadata was consulted; instructions and initializer values come from GameCube.

| Function | GameCube address | Size |
| --- | --- | --- |
| InitStageTime | 0x800A2090 | 140 |
| game1pSetLimitTime | 0x800A211C | 184 |
| SearchIntroStageLocator | 0x800A21D4 | 96 |
| SearchGoalStageLocator | 0x800A2234 | 96 |
| SearchStartStageLocator | 0x800A2294 | 312 |

The complete text range ends at `0x800A23CC`; all five functions are leaf
functions and own no exception tables or small-data constants.

| Owned object | Address | Size | Retail count |
| --- | --- | --- | --- |
| gStartStageLocator | 0x8024FEB0 | 4524 | 39 |
| gGoalStageLocator | 0x8025105C | 5040 | 60 |
| gStartStageLocator2p | 0x8025240C | 1380 | 23 |
| gIntroStageLocator | 0x80252970 | 1428 | 21 |
| timelimit_table | 0x80252F04 | 152 | 19 |
| stageTimerInfomation | 0x80252F9C | 12 | 1 |
| DemoLocator (.bss) | 0x80303E48 | 112 | 4 |

The contiguous data range ends at `0x80252FA8`, where an unrelated enemy class
string begins. The obsolete auto-split label at `0x80252411` lay five bytes
inside the two-player table; its removal follows the typed record stride,
complete data contents, and the 23-entry retail loop. DemoLocator is also
corroborated by Peripheral's 112-byte demo-file copy. That existing consumer
only changes the external symbol spelling.

Metadata establishes START_LOCATE (28 bytes), GOAL_LOCATE (20), INTRO_LOCATE
(16), their position/angle/formation/state/data fields, sTime's three signed
bytes, timer callback `void (*)()`, and the table record shapes. Row counts
come from GameCube bounds and data, since the PS2 version differs. Float
initializers preserve every retail bit, including negative zero. Public
function return types and signed-byte output pointers follow metadata.
The externally owned Action, MODESWITCH and TObjTeam structures are partial
views exposing only fields accessed by this unit. Retail establishes Action's
currentStageNo at 0x2C and timeoverFunction at 0x270, teamKind at 0x34, and
mode bytes at 0x18/0x1E. The callback remains the existing external function at
0x80018F38.

SearchStartStageLocator retains the retail demo-data priority, shared search
index across team iterations, and unchecked team/locator indices. InitStageTime
retains its unconditional output writes; game1pSetLimitTime instead checks its
optional outputs and defaults to one minute. The source uses ordinary array
size expressions for loop limits, preserving the unsigned bound comparison in
the two-player search while keeping the signed metadata local index.

Native single-object verification passes all five function bytes and bindings,
complete allocated sections (828-byte text, 12536-byte data, 112-byte BSS), and
all 43 effective relocations. Forty-two relocations are in text; the remaining
one initializes the timer callback. No normalizer, deferred inlining, or
instruction substitution is used. Independent object, type/control-flow and
consumer-symbol reviews pass. All-source compilation of the supported
G9SE8P main DOL and seventeen RELs passes; all eighteen reference hashes pass.
Progress/report generation, 62 automated tests and both policies pass.
Compilation and binary comparison do not establish runtime or physical-hardware
validation.
