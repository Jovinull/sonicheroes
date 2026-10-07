# Complete ball effect translation unit evidence

Positive symbolic metadata identifies effect/eff_ball.cpp as C++ with eleven
file-origin definitions. All eleven survive at 0x800C8EA0–0x800C99F8, totaling
2,904 bytes: rendering, two angle overloads, color assignment, instance reset,
destructor, constructor, shutdown, two original-resource setters, and startup.
No PS2 instructions were inspected. EffBall is a nonpolymorphic 0x1C-byte class:
four color bytes and six clump pointers. It does not inherit TObject.

The preceding static initializer points to unrelated storage and owns its own
constructor-list row. The following function polls and clears ADX sound errors.
Neither belongs to this unit. The six-slot resource graph and positive metadata
account for the complete unit independently of neighboring code.

Eight owned ranges contain 2,904 code bytes, 72 exception bytes, 108 index bytes,
16 read-only bytes, 344 data bytes, 408 BSS bytes, 16 small-data bytes and
32 constant bytes. There are 176 relocations. Class-static clump/UV arrays are
global; material pointers, UV state, default color and timestamps are private.
Startup owns the two six-entry filename tables. UV state uses the verified
GameCube 68-byte stride. The read-only 1.1 scale vector is twelve logical bytes
plus four alignment bytes. The default color is one four-byte RGBA object;
the legacy one-byte/three-byte symbol split is corrected without changing bytes.

Both original-resource setters are static class methods, as confirmed by the
absence of a metadata this parameter and by GameCube argument passing. The
floating-angle overload inlines the integer-angle calculation, whose ordinary
definition also survives. Both remain reconstructed. Strict production-object
comparison passes all eleven bodies, all 176 relocation meanings and all eight
owned sections. No extra functions or exception records require removal.

Reversed ordinary definition order and whole-unit auto,deferred inlining
recover the native layout without an object normalizer. Declaring timestamps
after startup retains their original data placement. Shutdown advances its
three resource pointers separately in the loop increment. The two startup-local
filename tables retain native local names dff_name$4 and uvb_name$11. The only
section-size differences are verified zero tail alignment: four bytes in
read-only and small data, and six after the final ten-byte filename string.

Independent source review confirms static-setter argument passing, angle
rounding and ordered threshold checks, differing constructor/reset slot rules,
resource ownership and render-state ordering. The original light-query
self-loop, repeated UV-resource test and timestamp update only after successful
UV advancement are preserved. No additional clump/null guards are invented.

With the complete unit enabled as Matching, all-source compilation and the
G9SE8P release DOL plus all seventeen supported RELs pass; all eighteen
reference hashes match. Objdiff reports 100% for all eleven functions and all
eight owned sections. Independent final-map/ELF comparison confirms all eleven
original addresses and all eight complete byte ranges, with no extra helper
bodies. All 62 automated tests and both policy checks pass.
Compilation and byte comparison do not establish runtime or physical-hardware
validation.
