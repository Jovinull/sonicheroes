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
this GameCube range; their operations are reconstructed inside the surviving callers.

The next function, `0x800AEE80`, merges two null-terminated pointer lists into a
new allocation, independently correlating with the following `scanpath.cpp`
`MargePathTag` operation. It is outside the path-control unit.

Six non-leaf bodies own 48 bytes of exception records at
`0x80007E84–0x80007EB4`, and 72 bytes of exception-index records at
`0x8000E488–0x8000E4D0`. The observed constants span
`0x8042DC28–0x8042DC60`. `pathSeeingPath` references the role table at
`0x80253648`. The owned data range is `0x80253648–0x80253658`: three role integers
and four bytes of alignment. The shared path-task pointer at `0x8042C380` is also used by the
following scanning unit and must not be assumed private storage.

Only symbolic PS2 metadata is used; executable behavior is recovered from
GameCube. All eight surviving bodies are now reconstructed together in C++.
The unit remains `NonMatching`; no instruction post-processor is used.

## Native verification

The constructor, destructor, Reset and Exec have byte-exact instruction bodies.
The four larger functions remain nonmatching:

| Function | Retail bytes | Native bytes | objdiff match |
| --- | ---: | ---: | ---: |
| pathSpin1D | 784 | 780 | 88.00% |
| pathGliding | 388 | 392 | 98.40% |
| pathGlidingReg | 2008 | 2024 | 90.92% |
| pathSeeingPath | 1244 | 1284 | 86.55% |

Every direct game/SDK call target and its per-function count agrees with retail.
The three role integers match. All fourteen floating-point constants match
bit-for-bit as a multiset in a 56-byte pool, but their order differs. Exception
records and function-size index records still differ. These checks do not
establish behavioral equivalence for the nonmatching bodies.

The GameCube layout uses eight player pointers and four team pointers; the
team table is 16 bytes and the seeing-path loop visits all four entries.
Unknown fields in external object views retain offset-based names.

Validation: G9SE8P, the only configured target, passes the release all-source
build, including main and all seventeen RELs. All eighteen normal-link hashes,
55 automated tests, language policy and post-processor policy pass. Because
this unit is NonMatching, normal linking still uses its retail object; the
hashes do not validate the candidate implementation. No runtime or hardware
validation was performed.
