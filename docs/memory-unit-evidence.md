# Memory.cpp native matching evidence

`game/Memory.cpp` now emits its complete reconstructed target object without a
post-compile fixer: six methods, 616 code bytes, 80 exception bytes, and the
four-byte `TaskHeap` pointer. All 14 relocations match by destination, type,
addend, and section offset.

## Source and ownership

Optional local PS2 beta `.debug` metadata identifies `src/Memory.cpp` as C++
and records `THeapCtrl`, `sHeap`, their fields, and all six methods: `Free`,
`Malloc`, the destructor, the constructor, `operator delete`, and `operator
new`. The GameCube allocation operator takes `unsigned long`, as required by
its compiler, whereas the PS2 metadata spells that size parameter as
`unsigned int`. No PS2 instructions are used.

The GameCube code run starts after `Task.cpp` and ends at `action.cpp`.
Its six methods correspond to that metadata. The reconstructed owned ranges
are:

| Section | Start | End | Bytes |
| --- | --- | --- | ---: |
| `.text` | `0x800189A4` | `0x80018C0C` | 616 |
| `extab` | `0x80005908` | `0x80005928` | 32 |
| `extabindex` | `0x8000BF5C` | `0x8000BF8C` | 48 |
| `.sbss` | `0x8042C148` | `0x8042C14C` | 4 |

`TaskHeap` was previously included at the end of the task unit's `.sbss` and
incorrectly sized as eight bytes. It is a four-byte pointer. Its metadata
record appears in `Memory.cpp`, `Task.cpp`, and `o_flower.cpp`; repetition alone
cannot distinguish a definition from a reference. The ownership inference
also uses these independent observations:

- `TaskHeap` appears first in the Memory data metadata; in the Task metadata
  it appears after the task's own globals, among external references.
- In the PS2 data layout it lies between the matrix pointer and message state,
  consistent with the Memory/message/mobject link sequence, while the task
  globals occupy a separate later range.
- In the GameCube layout it follows the task globals, consistent with that
  platform's Task/Memory/action code order.

This supports assigning the pointer to Memory. The historical GameCube data
boundary remains an evidence-backed hypothesis, not recovered object-file
metadata. The allocator's shared `ourGlobals` pointer is external. There are
no other static locals, vtables, or initialization records in the unit.
Heap contents and heap-node fields are dynamic instance storage.

The four bytes at `0x8042C14C`–`0x8042C150` remain an unowned alignment gap;
they are not a second pointer or an invented source field. The task unit's
`.sbss` now ends at `0x8042C148`, and it imports `TaskHeap` from Memory.

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
its code and retained data remain exact, including all 480 relocations.

## Verification

- All six raw function bodies and all four allocated sections match exactly,
  including section sizes, flags, alignment, and all 14 normalized relocations.
- Fresh linked ELF comparison against the original DOL verifies all 696
  file-backed bytes, all six function addresses and sizes, and all 14 relocation
  sites. The four-byte pointer and adjacent gap lie in the DOL's zero-initialized
  BSS range, with the pointer exported at the correct address and size.
- `ninja -j2 all_source` and the release build pass. `main.dol` and all 17 REL
  hashes match the checked-in manifest, independently rechecked with SHA-1.
- All 204 tool tests, the language policy, and 64 postprocessor checks pass.

These checks establish binary equivalence; they are not hardware testing.
