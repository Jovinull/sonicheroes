# Memory.cpp native matching evidence

`game/Memory.cpp` now emits its complete target object without a post-compile
fixer: six methods, 616 bytes of code, and 80 bytes of owned exception data.
All 14 relocations match by destination, type, addend, and section offset.

## Source and ownership

The optional local PS2 beta `.debug` metadata identifies `src/Memory.cpp` as
C++ and records `THeapCtrl`, `sHeap`, their fields, and all six methods:
`Free`, `Malloc`, the destructor, the constructor, `operator delete`, and
`operator new`. The GameCube allocation operator takes `unsigned long`, as
required by its compiler, whereas the PS2 metadata spells that size parameter
as `unsigned int`. No PS2 instructions are used.

The GameCube run starts after `Task.cpp` and ends at the start of `action.cpp`.
Its six methods correspond to that metadata. The owned ranges are:

| Section | Start | End | Bytes |
| --- | --- | --- | ---: |
| `.text` | `0x800189A4` | `0x80018C0C` | 616 |
| `extab` | `0x80005908` | `0x80005928` | 32 |
| `extabindex` | `0x8000BF5C` | `0x8000BF8C` | 48 |

The unit defines no globals, vtables, static locals, initialization records,
or other data sections. Heap contents are allocated dynamically. The allocator
pointer is external; the class and heap-node fields are instance storage.
The compiler's complete allocated-section inventory agrees with these ranges.

## Native emission

The original reconstruction made `operator delete` visible before the
constructor and destructor, but emitted it too early. With per-unit
`-inline auto,deferred`, reversing the ordinary definitions preserves inline
visibility and emits both functions and exception records in the target order.
This is a matching source arrangement, not evidence of the historical source
order or original compiler command line.

The obsolete Memory object fixer is removed. Four address-based split labels
are replaced with native C++ symbols. The task caller's explicit deleting-
destructor entry and existing symbol normalization are updated accordingly;
its complete object bytes and all 480 relocations remain exact.

## Verification

- All six raw function bodies and all three allocated sections match exactly,
  including section sizes, flags, alignment, and all 14 normalized relocations.
- Fresh linked ELF comparison against the original DOL verifies all 696 owned
  bytes, all six function addresses and sizes, and all 14 relocation sites.
- `ninja -j2 all_source` and the release build pass. `main.dol` and all 17 REL
  hashes match the checked-in manifest, independently rechecked with SHA-1.
- All 204 tool tests, the language policy, and 64 postprocessor checks pass.

These checks establish binary equivalence; they are not hardware testing.
