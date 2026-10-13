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
this GameCube range; their operations are reconstructed inside the surviving callers. The shared
`pathCalcRoughArea` helper is restored under its metadata name and inlines into
Spin, Gliding and Seeing; its path-table walk computes the common bounds.

The next function, `0x800AEE80`, merges two null-terminated pointer lists into a
new allocation, independently correlating with the following `scanpath.cpp`
`MargePathTag` operation. It is outside the path-control unit.

Six non-leaf bodies own 48 bytes of exception records at
`0x80007E84–0x80007EB4`, and 72 bytes of exception-index records at
`0x8000E488–0x8000E4D0`. The observed constants span
`0x8042DC28–0x8042DC60`. `pathSeeingPath` references the role table at
`0x80253648`. The owned data range is `0x80253648–0x80253658`: three role integers
and four bytes of alignment. Retained `pathSeeingPath` metadata names this
static local `role_table` and gives its array bounds as 0 through 2, confirming
the 12-byte symbol extent rather than the former inferred 16-byte extent. The shared path-task pointer at `0x8042C380` is also used by the
following scanning unit and must not be assumed private storage.

Only symbolic PS2 metadata is used; executable behavior is recovered from
GameCube. All eight surviving bodies are reconstructed together in C++ and emit
byte-exact instructions without instruction post-processing. The unit is now
`Matching`. See [the pool-order contract](pathctrl-constant-order.md) for the
remaining compiler constant-order correction.

## Whole-unit verification

The native object contains 4,676 exact instruction bytes across all eight
functions, plus exact 48-byte exception and 72-byte exception-index sections.
Its three role integers occupy 12 bytes; the linker supplies the four zero
alignment bytes present in the 16-byte reference range. Both data sections use
eight-byte alignment. Fourteen float constants occupy 56 bytes. After the
bounded constant-pool permutation, every owned section and all 110 resolved
relocation destinations match the reference.

The GameCube layout uses eight player pointers and four team pointers. The
seeing-path loop visits all four teams. Unknown external fields retain
offset-based names. Retained symbolic metadata supplies the local types and
private helpers `pathCalcRoughArea`, `pathCheckRangeWithinArea2` and
`pathCheckRangeWithinArea3`; their GameCube instruction sequences independently
confirm the correlations. No PS2 instruction implementation was imported.

Spin explicitly promotes its byte loop index through `u32` before calling the
signed-int player-path API, preserving the full public signature and native
register lifetimes. GlidingReg uses ordinary array indexing and repeated player
mask expressions. Seeing retains its optional point output check through the
unsigned output-pointer view also used by the called path routine. Its outer
team loop and metadata-named locals reproduce the surviving loop registers.

The position copy in Spin and facing-vector copy in GlidingReg use CodeWarrior's
`__memcpy` builtin. Each emits the reference integer-word loads and stores
without an external call, preserving the vector bits.

The unit retains default automatic inlining and original definition order.
Deferred inlining changes the constructor size and does not recover constant
order. All scalar storage is reconstructed; the pool step moves existing
compiler-emitted bytes and symbol values only.

## Final build verification

The supported G9SE8P release/all-source matrix passes with the reconstructed
unit linked: freshly relinked main DOL and all seventeen RELs match all eighteen
original hashes. The report marks all eight functions, all 4,676 code bytes and
all 192 owned data bytes at 100%. All 195 automated tests, language policy and
64 postprocessor checks pass. Formatting and diff checks pass. These results
establish compilation and binary identity, not runtime or console validation.

## Player-path API parameter evidence

The symbolic metadata identifies `SpinAlongPathP__FiP7PATHTAG` and
`RunWithSeeingPathP__FiP7PATHTAG`, both returning signed int and accepting a
signed-int player number followed by PATHTAG*. Their GameCube counterparts at
`0x800DFD08` and `0x800DFB88` index the task/player tables directly using the
full incoming register, check path-control flags, compare previous/current
path distances and update the active tag. Their ordering and behavior correlate
with the metadata APIs. The provisional declarations now use s32, replacing
the earlier u8 inference from the caller's local variable.

The byte-index promotion at the call site now produces the original instructions
without narrowing either public API. The player loop remains `u8`, as recorded
in the symbolic metadata.

`pathCheckRangeWithinArea2(CLASS_PATH*, int, int*, float)` is restored under
its metadata name and inlines into Seeing. It rejects a missing player, tests
the six bounds in retail order, compares distance with the supplied catch
distance and optionally writes the path point. Its explicit comparisons retain
the original unordered-floating-point behavior. Restoring the helper removes
decompiler temporaries and the artificial-looking check of a local variable's
address, while retaining the real optional output-pointer test in the helper.
