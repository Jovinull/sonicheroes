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
the six metadata-named inline methods. Fifteen bodies match directly; the
sixteenth uses the bounded register normalization described below.

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

Native comparison currently verifies instruction bytes and normalized
relocations exactly for fifteen bodies: MargePathTag, SCPathPntNearToOnpos,
SCPathSubCheckTheNearestPoint, SCPathOnposToPntnmb, GetStatusOnPath,
GetPointDataOnPath, scanpathGetTheConnectedPath, scanpathGetTheNearestPath, ReleasePath, EntryPath, Disp,
Exec, EndPath, InitPath and the destructor. All sixteen bodies have the same game/SDK direct call targets
and counts as retail. The remaining native comparisons are:

| Function | Retail bytes | Candidate bytes | objdiff similarity |
| --- | ---: | ---: | ---: |
| CalcPNNPntParam | 636 | 636 | 99.91% |

Similarity is diagnostic, not an exact-match claim. The candidate additionally
emits a 40-byte weak definition of the existing TObject::operator delete for
constructor exception cleanup. A diagnostic native link confirms that the
linker selects Task's existing definition at 0x8001895C and discards the weak
duplicate and its extra eight-byte exception record and twelve-byte index.
The manager vtable, name pointer and shared pointer retain their retail
addresses. The complete linked .sdata2 section is byte-identical to retail,
including scanpath's constants and normal linker alignment.

The diagnostic native link preserves every section size and address. The whole
DOL differs in only five instruction bytes across two instructions, all within CalcPNNPntParam; every data
and exception section is byte-identical. The remaining helper loads an angle into r4 and then copies it to r27;
retail loads r27 and copies it to r4. All other instructions agree. Unit-wide
`-O3,p` preserves the other fifteen exact bodies and removes the broader register
allocation differences produced by `-O4,p`.

## Remaining compiler allocation and normalization

`tools/fix_scanpath_registers.py` changes four encoded register fields across
those two instructions out of the helper's 159 instructions. It substitutes
register numbers into compiler-generated instructions; it contains no retail
instruction words. The raw source is fifteen of sixteen exact, and this is
not a source-only match claim.

The first instruction loads the current signed-short angle into r4 instead
of r27. Two intervening loads use neither register. The fourth instruction
copies that angle into the other register. Both versions therefore have
identical full register state before the next DiffAngle call, including the
angle in both r4 and r27. No branch enters the window interior; the earlier
index in r4 is dead, and the caller's r27 has already been saved. Loads and
non-recording register copies leave memory and condition flags unchanged.
Later angle calls and the existing save/restore sequence are identical. The
independent transfer audit checks all 65,536 signed-halfword inputs.

The normalizer requires exact raw/output text and helper hashes, the expected
local function boundary and relocation records, and each instruction's opcode
and original register fields. It is atomic and idempotent and rejects an
unknown compiler state. No other instruction, section, symbol or relocation
is changed. Five file bytes change in total.

Source trials included metadata-local scopes, pointer/angle assignment and
declaration orders, copies, reloads, casts, argument forms and compiler
versions/options. O4 with dead-store optimization disabled fixes this helper
but regresses ConnectedPath; further bound-local forms did not restore the
whole unit. No fabricated barrier or padding was introduced. A future source
change that fixes the transfer can remove this tool and its build step.

## Verification

The normalized compiler object verifies all sixteen bodies and their
relocations exactly. All seven owned sections and 346 relocations agree after
explicitly accounting for the existing weak-delete coalescing and normal
four-byte section tails; those linker operations are not performed by the tool.
A fresh native link with scanpath marked Matching confirms those expectations:
G9SE8P main DOL and all seventeen RELs compile and all eighteen retail image
hashes pass. All-source compilation and progress/report generation pass.
The 68 automated tests, language policy, post-processor policy and formatting
checks pass. Six new tests cover mutation bounds, idempotence and rejection of
unexpected input, function/relocation metadata, register fields and failed CLI
writes/stamps.

PAL/Japan are not supported build targets; PS2 was used only for symbolic
metadata. No runtime or physical-hardware validation was performed.
