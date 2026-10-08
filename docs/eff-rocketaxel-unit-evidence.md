# Complete rocket effect translation unit evidence

Positive symbolic metadata identifies effect/eff_rocketaxel.cpp as C++ with
21 file-origin definitions across four classes, three factories and resource
startup/shutdown. Seventeen bodies survive at 0x800F3134–0x800F46B0, totaling
5,500 bytes. Four ordinary constructors inline into factories or Hit::Exec;
all four remain part of the reconstruction. No PS2 instructions were inspected.

Four class strings, their class-name pointers and vtables independently anchor
ownership. Eight owned ranges contain 5,500 code bytes, 344 exception bytes,
192 index bytes, 64 read-only bytes, 304 data bytes, sixteen small-data bytes,
24 small-BSS bytes and eighty constant bytes, with 375 relocations. Shutdown
has no exception record. All owned storage code references stay inside the
complete function range.

The read-only range contains five twelve-byte local vector initializer
templates, with four final alignment bytes. Initialized data contains four
class strings, four 44-byte vtables and three resource filenames; the final
vtable has four alignment bytes. Four class-name pointers are global. Six
resource pointers are file-private, ordered clumpAxel/Hit/HitB then
materialAxel/Hit/HitB. The pool contains one eight-byte conversion double;
its last entry is a real four-byte 0.6 float, with no omitted tail.

GameCube allocation and access evidence agrees with metadata class sizes:
Jump and Axel are 0x30, HitB is 0x48, and Hit is 0x38. All inherit the verified
0x28 TObject base. Jump and Axel share the Axel material. Hit::Exec contains
three separately inlined HitB constructions. Shutdown clears six pointers;
it does not destroy the template resources.

Independent boundary review excludes the preceding recursive RwFrame hierarchy
helper and the following material-plugin/callback graph. The latter begins
with its own no_tx_light.mte string immediately after the final rocket vtable
alignment. Exact neighboring source filenames are not inferred from adjacency.

The Hit execution path uses the existing nonvirtual TObject::GetChildCount
implementation at 0x80017830. Its canonical name is retained by the Task object
post-processor; the existing method source and call target are unchanged.

All 21 definitions are reconstructed. Source trials recover the four rendering
methods through metadata-backed RGBA temporaries: capture the color fields,
replace alpha, then assign the aggregate. Compound alpha temporaries preserve
the original subtraction and clamping. Reversed ordinary definition order with
whole-unit auto,deferred recovers the remaining emission order. No object
normalizer has been introduced.

The frozen production object passes strict comparison for all seventeen
instruction bodies, global bindings and surviving order, all 375 effective
relocations, and all eight owned sections. Only the verified four-byte tails
in read-only/data storage differ before linking; the complete eighty-byte
pool is exact. Four ordinary constructor copies and weak TObject delete remain
native compiler output for the linker to discard.

Independent source review confirms the bounded signed-integer alpha subtraction
and clamp, player-history query ordering, the complete 64-byte fallback matrix
copy, material/clump API contracts and owned clone destruction. Floating-point
branches preserve their ordered/unordered behavior: unordered motion length
uses the fallback matrix. No extra null checks or template cleanup are added.
All-source compilation and the complete G9SE8P release DOL plus seventeen
supported RELs pass; all eighteen reference hashes match. Independent final
map/ELF comparison confirms all seventeen original addresses and all eight
complete byte ranges. All four ordinary constructor copies and weak delete
(800 text bytes plus 120 exception and sixty index bytes) are naturally
discarded; the original strong TObject delete is retained. Objdiff reports
100% for all seventeen functions, with compiler-only helper/EH records accounted
for by strict surviving-object and final-link audits. All 62 automated tests
and both policy checks pass. The complete unit is enabled as Matching without
an object normalizer. Compilation and byte comparison do not establish runtime
or physical-hardware validation.
