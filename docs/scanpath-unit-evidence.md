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
as part of its reconstruction. The other correlations above are an initial
inventory and still require per-body native audits.

The manager virtual table referenced by construction and destruction is at
0x80253668. The shared path manager pointer is at 0x8042C380. Exception and
owned-data boundaries remain to be established before introducing the split.
Only PS2 symbolic metadata was inspected; no PS2 instructions were used.

This is a whole-unit reservation, not a completion or matching claim. No code
or build configuration has changed. Reconstruction, complete owned-section
verification, all supported target builds and relevant tests remain required.
