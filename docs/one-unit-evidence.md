# ONEFILE translation unit evidence

The original symbolic metadata identifies `one.cpp` as C++ and names the
`ONEFILE` class, archive operations, seven extended resource loaders and nine
resource loaders. GameCube calls and member accesses independently correlate
these operations with the contiguous range `0x800BA7F8–0x800BCE78`.
The following unit is the established `hAnim.cpp` split.

The preceding function, `fn_800BA754`, copies a different 0x50-byte structure,
including byte fields at offsets 0x2c and 0x40. The preceding graphics routine
`fn_800B9408` calls that copy operation repeatedly. It is excluded from ONEFILE.

There are 25 surviving GameCube bodies. `Exist` and `OpenData` are inlined;
there is no invented standalone export for either. GameCube additionally has
an archive memory-stream setter at `0x800BA7F8` and an ARAM resource loader at
`0x800BC370`; their original names remain unknown. These belong to the complete
unit even though the available PS2 metadata does not name them.

GameCube allocates 0x58 bytes for ONEFILE in the resource loader. Its fields are
`fname[64]`, `exBuffer`, `oneFileInfo`, `showError`, `flagBW`, and `memInfo`, at
0x00, 0x40, 0x44, 0x48, 0x4c, and 0x50 respectively. The additional PS2
`mCurStream` field at 0x58 is absent on GameCube.

The retail exception index associates 24 non-leaf methods with contiguous
`extab` entries at `0x80008240–0x80008300` and index entries at
`0x8000E8F0–0x8000EA10`. `CheckFileName` is the sole leaf method.
Two archive ownership marker strings start at `0x80253C00` and `0x80253C18`;
the complete native string data is 45 bytes, followed by three retail alignment
bytes. No synthetic padding is emitted.

This branch depends on the canonical Expand2 interface correction in PR #567.
Only symbolic PS2 metadata is used; implementation behavior comes from the
GameCube target. All 25 bodies are reconstructed. Native comparison finds eight exact functions
and 17 with instruction differences; all function sizes, exception records and
422 normalized relocations are exact. The unit remains NonMatching. No runtime
or hardware validation is claimed.


Verification for this reconstruction: the G9SE8P all-source release build and
normal link pass, together with 55 automated tests and both language and
post-processor policy checks. All 18 normal-link hashes pass. Since `one.cpp`
is NonMatching, the normal link retains its original object; those hashes do
not establish an exact native replacement or runtime behavior.
