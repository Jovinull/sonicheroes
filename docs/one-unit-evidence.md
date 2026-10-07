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
GameCube target. All 25 bodies are reconstructed and now match directly from
C++, together with every function offset and size and all 422 normalized
relocations. No instruction postprocessor is required.

## Chunk-address expression

The shared OpenData helper and the ARAM resource loader compute the address of
the chunk header after reading it. The previous expression grouped the integer
offset subtraction first: `memBlock + (position - 12)`. Reassociating it as
`memBlock + position - 12` reproduces the original load order and temporary
register allocation. It removes four instruction differences in each of the
seventeen affected bodies, including the inlined extended loaders.

The base is a byte pointer, so both offsets are measured in bytes. On a valid
stream after a successful header read, the current position is at least twelve
and within the allocation (possibly one past its end). Forming the current
pointer before subtracting the header size stays within that allocation. The
source does not form a pointer before the beginning of the allocation and adds
no load, barrier, artificial use or padding. Invalid stream behavior is not
used to infer a new input-validation contract.

An isolated whole-object comparison with the configured compiler options
verifies all 9,856 text bytes, 192 exception-table bytes, 288 exception-index
bytes, all 422 relocations and the 45 string-data bytes plus three natural
alignment bytes. The baseline comparison was eight exact bodies; after this
single shared expression fix, all 25 are exact.

## Verification

A fresh native build with ONEFILE marked Matching compiles G9SE8P main DOL
and all seventeen RELs; all eighteen retail image hashes pass. All-source
compilation, progress/report generation, 55 automated tests, both policies
and formatting pass. A second independent review confirms the built object
and byte-pointer arithmetic. No runtime or physical-hardware validation was
performed.
