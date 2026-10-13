# Scanpath translation unit evidence

Symbolic PS2 metadata positively identifies scanpath.cpp as C++. Its complete
inventory contains twenty public functions and two private helpers. A public-only
inventory misses SCPathSubCheckTheNearestPoint and CalcPNNPntParam.

The GameCube candidate unit is `0x800AEE80–0x800B13EC`, immediately following
the established pathctrl.cpp boundary. Sixteen surviving bodies occupy 9,580
bytes. The first function merges two null-terminated PATHTAG pointer tables.
The final destructor clears the shared manager pointer, releases CLASS_PATH
nodes, destroys TObject and conditionally frees the allocation. The following
function at 0x800B13EC handles a different object's component pointer at 0x20,
allocates a 60-byte component and uses different virtual tables; it is excluded.

| GameCube address | Initial correlation |
| --- | --- |
| 0x800AEE80 | MargePathTag |
| 0x800AEF48 | SCPathPntNearToOnpos |
| 0x800AF0A8 | private SCPathSubCheckTheNearestPoint |
| 0x800AF2E4 | SCPathOnposToPntnmb |
| 0x800AF3AC | GetStatusOnPath |
| 0x800AF8D4 | private CalcPNNPntParam |
| 0x800AFB50 | GetPointDataOnPath |
| 0x800AFBF4 | TObjPathManage::scanpathGetTheConnectedPath |
| 0x800AFD48 | scanpathGetTheNearestPath |
| 0x800AFF28 | TObjPathManage::ReleasePath |
| 0x800B001C | TObjPathManage::EntryPath |
| 0x800B0F40 | TObjPathManage::Disp |
| 0x800B0F44 | TObjPathManage::Exec |
| 0x800B113C | EndPath |
| 0x800B1168 | InitPath |
| 0x800B128C | TObjPathManage destructor |

The four reEntry methods (Len, Vec, Ang, Pos), SetPath and the constructor
have no separate bodies in this range. InitPath visibly allocates 0x230 bytes,
inlines TObject-derived initialization, publishes the shared manager pointer,
stores the input table at 0x28 and builds the CLASS_PATH list at 0x2c. Its
allocation/list-building operations correlate the inlined constructor and
SetPath. EntryPath is 3,876 bytes and requires auditing the reEntry operations
as part of its reconstruction. All sixteen surviving bodies are now reconstructed in C++, together with
the six metadata-named inline methods. All sixteen bodies match directly from
compiler output with the scoped settings described below.

The manager virtual table referenced by construction and destruction is at
0x80253668. The shared path manager pointer is at 0x8042C380. Linked relocation
and exception-index analysis establishes these complete owned ranges:

| Section | Start | End | Bytes |
| --- | --- | --- | ---: |
| extab | 0x80007EB4 | 0x80007F68 | 180 |
| extabindex | 0x8000E4D0 | 0x8000E560 | 144 |
| .text | 0x800AEE80 | 0x800B13EC | 9580 |
| .data | 0x80253658 | 0x80253698 | 64 |
| .sdata | 0x8042B378 | 0x8042B380 | 8 |
| .sbss | 0x8042C380 | 0x8042C388 | 8 |
| .sdata2 | 0x8042DC60 | 0x8042DCA0 | 64 |

Only PS2 symbolic metadata was inspected; no PS2 instructions were used.
Metadata confirms the generic PATHTAG table pointer is void*, with distinct
12-byte position, 20-byte point and 28-byte rail records. The shared header
now describes all three formats and the complete 560-byte manager. Existing
pathctrl callers use the recovered C++ API and the metadata-confirmed
SCPathOnposToPntnmb argument order. Other existing callers retain their
provisional declarations with only their external symbol names updated.
The existing Task virtual-method name mapping is updated consistently in its
callers and existing metadata post-processors.

Native comparison verifies instruction bytes and normalized relocations exactly
for all sixteen bodies, including the 636-byte `CalcPNNPntParam`. All game/SDK
direct call targets and counts agree with retail. The compiler additionally
emits a 40-byte weak definition of the existing TObject::operator delete for
constructor exception cleanup. A diagnostic native link confirms that the
linker selects Task's existing definition at 0x8001895C and discards the weak
duplicate and its extra eight-byte exception record and twelve-byte index.
The manager vtable, name pointer and shared pointer retain their retail
addresses. The complete linked .sdata2 section is byte-identical to retail,
including scanpath's constants and normal linker alignment.

## Native compiler match

All sixteen owned functions (9,580 text bytes) now match directly from compiler
output. `CalcPNNPntParam` uses scoped `#pragma optimization_level 4` and
`#pragma opt_dead_assignments off`, followed immediately by resets for both.
The remaining functions retain unit-wide `-O3,p`. Applying the higher optimization
level across the whole unit regresses `ConnectedPath`; O3 with dead assignments
disabled alone leaves the angle load/copy mismatch. The scoped combination fixes
that mismatch while preserving the other fifteen bodies.

These settings are reconstruction choices supported by compiler comparisons;
the historical presence of these pragmas is not established. They replace the
former four-register-field instruction normalizer, which has been removed along
with its build rule and tests. No instruction bytes are patched after compilation.

The compiler emits the same existing 40-byte weak `TObject::operator delete`
body and its 20 bytes of exception records. The native compiler object has the
same allocated bytes and all 350 relocation records as the formerly normalized
object. The linker discards the duplicate weak support code as documented above;
the owned unit retains 346 relocations and normal four-byte alignment tails.

## Verification

All sixteen owned functions match directly from the compiled object. All allocated
bytes and 350 compiler-object relocations agree with the previously verified
object, including the unchanged weak support body. A fresh main ELF/DOL link
confirms linker discard and the owned data layout. All eighteen G9SE8P hashes
(main DOL plus seventeen RELs) pass. All-source compilation, 198 automated tests,
language policy, all 64 remaining post-processor checks and source formatting pass.

PAL/Japan are not supported build targets; PS2 was used only for symbolic
metadata. Compilation does not establish runtime or physical-hardware validation.
