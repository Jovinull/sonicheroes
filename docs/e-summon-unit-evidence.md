# Complete enemy summoning translation unit evidence

The positive C++ compilation unit enemy/e_summon.cpp identifies TEnemySummon,
its six methods, fields, class-name pointer and vtable. GameCube preserves
three emitted bodies; SummonEnemy, CreateSummonPtcl and the constructor are
inlined. No PS2 instructions were inspected.

| Emitted function | GameCube address | Bytes |
| --- | --- | ---: |
| TEnemySummon::Exec | 0x801308C8 | 524 |
| TEnemySummon destructor | 0x80130AD4 | 108 |
| TEnemySummon::Create | 0x80130B40 | 128 |

Together they occupy 760 text bytes at 0x801308C8–0x80130BC0. The preceding
routine belongs to autosave; the next range is the independently identified
GetSpParam unit. Correlated method behavior, class construction and the
vtable establish the complete surviving class inventory.

Owned exception records occupy 0x8000B670–0x8000B698 (40 bytes), with three
index records at 0x80011638–0x8001165C (36 bytes). Initialized data contains
the 13-byte class string at 0x8028AED0, its natural alignment and the 44-byte
vtable at 0x8028AEE0, followed by four bytes of linker alignment. The class-name
pointer at 0x8042BB88 is four bytes, followed by four bytes of linker alignment.
The auto-split symbol sizes had included this trailing alignment; corrected
vtable and pointer sizes follow the actual typed objects. Shared communication
tables, task parents, mode/action state, heap and set-generator state remain
external. No owned BSS or floating constants are asserted.

The 0x34-byte class derives from the verified 0x28-byte TObject layout and
stores signed mMode at 0x28, signed mTimer at 0x2C and unsigned-byte
mCommunicationId at 0x30. Its constructor registers the class name, records
its size in the observed task field, selects mode zero and initializes an
80-frame timer. Its empty destructor delegates to base destruction and heap
release.

Exec resumes the communication group and requests task death during restart.
Otherwise its three signed pause flags gate progress. Mode zero clears the
standby condition for matching enemy IDs in the communication list. Mode one
creates the effect and sleeps the group on its first frame, decrements the
timer, then resumes the group and optionally plays the sound when it expires.
Mode two requests task death. The recovered external CreateEffect, TaskSleep
and TaskResume signatures return void and take unsigned-int IDs.

The two inlined helper return types are signed int in metadata, but GameCube
calls discard their values. Their neutral return values are explicit
reconstruction choices, not claims about unobservable original values.
CreateSummonPtcl's association with the effect call is a semantic boundary
inference; no surviving standalone body proves that source-level boundary.

A local snapshot of the metadata-backed ACTIONMODE_TURN enum reproduces the
restart predicate's exact compiler lowering. Direct field expressions, nested
predicates and broader inline-mode trials did not. Ordinary auto inlining and
the local enum snapshot produce all three exact bodies without normalization
or deferred inlining. The enum itself represents the observed restart values;
its field remains at the GameCube offset 0x18.

The compiler also emits a 40-byte weak TObject::operator delete duplicate and
its exception records because the new-expression needs cleanup. Its body and
both relocations equal the existing Task.cpp definition. The normal linker
selects the existing strong definition at 0x8001895C and explicitly discards
this unit's duplicate and associated exception records in the final link map. No instruction or data removal
step is introduced. The inherited TObject::TDisp symbol receives the same
canonical rename already reviewed with e_mtnpath, propagated through its three
existing callers and three existing symbol-normalization tables.

Independent review verifies all three surviving bodies, every owned section
and all 41 effective relocations. The final ELF confirms constructor cleanup
points to the existing delete helper and all exception-index addresses/sizes
are exact. The complete supported G9SE8P release matrix passes: main DOL and
all seventeen RELs match all eighteen expected hashes. All 62 automated tests,
language policy and post-processor policy pass. Compilation and binary
comparison do not establish runtime or physical-hardware validation.
