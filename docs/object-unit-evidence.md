# Complete object.cpp reconstruction

## Boundary, language and types

Local symbolic metadata identifies `object.cpp` as C++, including rendering
overloads, `OBJ_MoveOnGround`, `OBJ_ReplacePlayer`, and the function-local static
`lengthByHands` array. GameCube instructions, call targets and relocations
establish the 79 surviving functions at `0x8005BEC4–0x8005F490` and their owned
storage. PS2 instruction bytes were not used. Platform-sensitive layouts and
argument registers are taken from the GameCube accesses.

The resource entry/request names and iterator helper are reconstruction aids;
their exact byte strides, fields and uses come from GameCube. The real
`ONEFILE(char*, int)` constructor produces the target C++ call and exception
cleanup. Its GameCube allocation is `0x58` bytes; the PS2 metadata's `0x5C` size
includes a platform-specific trailing field and was not copied. This removes
the old fragment's fabricated inline constructor wrapper.

The decompressor uses the shared signed byte-count contract from PR #567 and a
stream-memory descriptor with pointer and length fields. This replaces the
older pointer-return declaration. Existing callers retain their runtime
interfaces through mechanical canonical-symbol renames.

## Source-produced layout

`-inline auto,deferred,level=2` expands the nested camera helpers while retaining
the ordinary externally callable camera-check function. Level 1 leaves a nested
call unexpanded; explicitly marking the public function inline removes its
standalone body. Deferred compilation emits definitions in reverse lexical
order. Reverse address order in this reconstruction produces the retail
function offsets, exception tables, and scalar-pool order. This does not
establish the lost original lexical order.

The three near-camera overloads copy one internal constant `RwRGBAReal` into
mutable local colors. The explanatory name `nearCameraColor` is reconstructed.
Its single 16-byte payload and all generated loads and stores match the target.
The metadata-backed `lengthByHands` remains function-local static. Defining the
last three resource-name strings after the player methods places the array
before those strings; forward declarations preserve C linkage.

The source independently reproduces all 79 function offsets, exception payloads,
owned data, and 800 relocations: 655 text, 128 exception-index, one exception
payload, and 16 data relocations. Existing section alignment accounts for the
four-byte tails. No layout normalizer or artificial padding is used.

## Explicit register-allocation remainder

Raw compiler output matches 78 of 79 instruction bodies, with no missing or
extra functions. `objPointerReadFromClumpAnim` differs only in ten register
fields across six instructions: two address initializations, two moves into
`strcmp`'s argument, and two pointer increments. The compiler uses `r31` for
the two scan cursors; retail uses `r27`. No opcode, immediate, branch, memory
access or relocation differs. A raw native DOL comparison finds exactly eight
differing bytes in those six instruction words, and nowhere else.

Both are callee-saved registers already covered by the function's save/restore
sequence. Each cursor is initialized before the loop and survives the same
`strcmp` calls. The cursor value is dead on every loop exit. Before subsequent
uses, the request pointer freshly defines `r31` at function offset `0xC0`, and
the expanded buffer freshly defines `r27` at `0x100`. Early exits reach the common
register-restoring epilogue. The recoloring therefore preserves data flow on
all paths; it does not replace missing behavior.

`tools/fix_object_registers.py` applies only those ten field substitutions to
compiler-produced instructions. It does not contain or copy retail instruction
words. Input/output hashes, the function boundary and the relocation contract
reject unexpected objects; already-normalized input must satisfy the output
contract. The old fragment's 91-field/60-instruction adjustment and exception
cleanup edit are removed. The new remainder is ten fields in six instructions
out of this complete 13,772-byte TU.

Helper/caller declaration orders, loop forms, stream descriptor types, scoped
locals and historical source forms were tested without recovering these last
register choices. The underlying source/compiler allocation cause remains
unknown. This is a complete C++ reconstruction with a documented compiler
register-normalization step, not a source-only byte-match claim. Remove the
step when source/compiler choices reproduce the two cursor allocations.

## Integration checks

An independent normalized-object audit verifies all 79 bodies and their
relocations, with exactly eight bytes changed in the ten allowed register
fields. Public and private overloads retain the bindings of their complete
compiler-generated mangled symbols. The full module build detected two public
overloads incorrectly grouped with private callbacks during a symbol-scope
update; those exports were corrected before final verification.

The final native `Matching` build passes the complete documented G9SE8P matrix:
main DOL and 17 RELs, with all eighteen reference hashes byte-identical. All 68
relevant tests pass, including six register-normalizer tests for mutation
boundaries, idempotence, corruption, symbol binding, relocation guards and
failure without writing an output/stamp. Language/postprocessor policies and
source formatting checks pass. These results establish compilation and binary
identity; runtime and physical hardware were not tested.
