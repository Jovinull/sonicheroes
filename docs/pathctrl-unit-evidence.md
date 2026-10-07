# Path control translation unit evidence

The original symbolic metadata identifies `pathctrl.cpp` as C++ and describes
`CLASS_PATH`, seven public functions and four private helper functions. Public
functions alone do not describe the complete unit. GameCube has eight surviving
bodies at `0x800ADC3C–0x800AEE80`; the range begins immediately after the
established `eff_tornado.cpp` split.

| GameCube address | Correlated operation |
| --- | --- |
| 0x800ADC3C | pathSpin1D |
| 0x800ADF4C | pathGliding |
| 0x800AE0D0 | private pathGlidingReg |
| 0x800AE8A8 | pathSeeingPath |
| 0x800AED84 | CLASS_PATH::Exec |
| 0x800AEDB4 | CLASS_PATH::Reset |
| 0x800AEDE8 | CLASS_PATH destructor |
| 0x800AEE38 | CLASS_PATH constructor |

`Exec` calls the callback at offset 0x54. The constructor stores that callback,
clears `useCopyData` at 0x48, resets mode/flag/timer and eight signed-short player
slots at 0x04–0x13, and clears the tag and list pointers at 0x44/0x4c/0x50.
Those accesses independently match the metadata's 0x58-byte CLASS_PATH layout.
The destructor clears the list links and conditionally calls operator delete.
The private range-check and rough-area helpers have no standalone bodies in
this GameCube range; their inlining must be reconstructed within the whole unit.

The next function, `0x800AEE80`, merges two null-terminated pointer lists into a
new allocation, independently correlating with the following `scanpath.cpp`
`MargePathTag` operation. It is outside the path-control unit.

Six non-leaf bodies own 48 bytes of exception records at
`0x80007E84–0x80007EB4`, and 72 bytes of exception-index records at
`0x8000E488–0x8000E4D0`. The observed constants span
`0x8042DC28–0x8042DC60`. `pathSeeingPath` references the role table at
`0x80253648`. Final owned-data boundaries and alignment require the native
object audit. The shared path-task pointer at `0x8042C380` is also used by the
following scanning unit and must not be assumed private storage.

This reservation does not claim completion. Reconstruction, native comparison,
all supported target builds and relevant checks remain required. Only symbolic
PS2 metadata is used; executable behavior is recovered from GameCube.
