# Enemy gadget base translation unit evidence

Symbolic compilation unit `0xa858fa` explicitly names enemy/e_gadget.cpp as
C++ and identifies its class, fields and five out-of-line methods. Header
metadata identifies its destructor and small virtual methods. GameCube
construction/destruction references a single 80-byte vtable, tying every
emitted tail method to this unit. No PS2 instructions were inspected.

| Function | GameCube address | Bytes |
| --- | --- | ---: |
| CheckCameraFrustum | 0x800FD468 | 104 |
| TDisp | 0x800FD4D0 | 96 |
| Disp | 0x800FD530 | 96 |
| Exec | 0x800FD590 | 104 |
| constructor | 0x800FD5F8 | 100 |
| inline destructor | 0x800FD65C | 108 |
| SetClump | 0x800FD6C8 | 8 |
| Update | 0x800FD6D0 | 4 |
| DispOpaq | 0x800FD6D4 | 4 |
| DispTrans | 0x800FD6D8 | 4 |
| DelClump | 0x800FD6DC | 4 |
| provisional UnknownSlot44 | 0x800FD6E0 | 4 |
| provisional UnknownSlot48 | 0x800FD6E4 | 4 |
| CanDisp | 0x800FD6E8 | 8 |

All fourteen bodies occupy `0x800FD468–0x800FD6F0` (648 bytes). The preceding
constructor belongs to another class, and the following routines manipulate
the enemy manager's linked lists. Owned exception records occupy
`0x80009738–0x80009768` (48 bytes), their index occupies
`0x8000FD18–0x8000FD60` (72 bytes), and the vtable occupies
`0x8025A800–0x8025A850` (80 bytes). No constants, strings or zero-initialized
storage belong here. Task parent, heap and current-camera globals remain external.

The 0x38-byte class publicly derives from the verified 0x28-byte TObject
contract. It stores owner at 0x28, clump at 0x2C, nested eGadgetMode at 0x30,
and signed IsKilled at 0x34. Its constructor attaches to the external task
parent, stores the owner, clears clump/killed state and selects standby mode.
The empty destructor invokes TObject destruction and inherited heap deletion;
it does not release the clump. Frustum checking returns true with no clump,
otherwise builds a sphere and tests the current camera. Disp/TDisp require
not-killed and virtual CanDisp before virtual opaque/transparent display.
Exec sets the task kill signal when killed, otherwise gates virtual Update
through the external execution predicate.

The vtable retains all nine TObject virtual slots followed by the gadget
methods. The pure slot at 0x3C is `s32 ReqGadgetMode(eGadgetMode)`: MGun, Shot
and SearchLight constructor/vtable/method correlations plus positive derived
metadata establish the signature and nested enum. The slot at 0x40 is void
DelClump, corroborated by positive base/SearchLight metadata, Shot resource
release and destructor dispatch, and Searcher callers.

Slots 0x44 and 0x48 are additional GameCube virtuals whose authentic names are
unresolved. They retain explicitly provisional names and void/no-argument
interfaces, supported by callers supplying only this and ignoring a result.
Laser overrides toggle a release-specific field; the base bodies are empty.
Their bodies, slots and ownership are verified, but the original names and
unused return contracts are not claimed. The GameCube vtable has more slots
than the older PS2 metadata. Compiler-emitted inline methods retain weak ELF
binding, replacing the initial auto-split's provisional global classifications.

All fourteen bodies and the vtable contents match directly from C++. Ordinary
automatic inlining intersperses referenced inline methods and emits the
destructor exception record last. Moving inline definitions out of class and
below the five methods shifts the text toward its desired tail but still
leaves exception records in the wrong order. Whole-unit auto,deferred with the
five source definitions reversed produces every correct body and the exact
exception payload/order, while emitting a 148-byte destructor/inline block
before the 500-byte out-of-line block. Retail places those two blocks in the
opposite order; its exception index follows text order while its destructor
exception record remains first.

The remaining correction is restricted to moving complete compiler-owned
atoms and their metadata. No function instruction bytes need modification.
Original source line order and historical compiler flags are not asserted;
this is a reviewed reconstruction setting motivated by inline virtual emission
and the distinct exception-record/index ordering. The guarded normalizer
rotates the 148-byte inline block behind the 500-byte method block and moves
the destructor exception-index row after the other five rows. Symbol values,
relocation sites and section-relative addends follow those same permutations.
It embeds no instruction words and never reads a reference object.

Exact input/output payload hashes, full symbol and relocation inventories,
section properties and intra-function branch checks reject unexpected input.
Every function body is checked for byte preservation, the output is validated
before atomic replacement, and a second invocation is a no-op. Independent
raw-to-normalized review confirms no changed fields outside the two payload
permutations and their symbol/relocation metadata. All fourteen normalized
functions, all owned sections and all 41 effective relocations match.

The complete G9SE8P release matrix passes with this source marked Matching:
main DOL and all seventeen RELs match the eighteen expected artifact hashes.
All 69 automated tests pass, including seven synthetic normalizer tests;
language and post-processor policies pass. Independent object and permutation
reviews pass. Compilation and binary comparison do not establish runtime or
physical-hardware validation.
