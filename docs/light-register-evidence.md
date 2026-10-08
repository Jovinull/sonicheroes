# Light loader register evidence

The complete `light.cpp` unit reconstructs 26 bodies across
`0x80052184–0x80053FB8`, with the C++ language/type evidence recorded in
[language-audit.md](language-audit.md). Twenty-five bodies now match directly.
The accepted source change expands the existing restoration loop directly in
`EndIgnoreLight`; the SDK calls, cached-world behavior and eight-light bound
are unchanged.

## Published remainder

`CLIGHT::Init` has ten register-field differences across seven of its 152
instructions (608 bytes). The destination and file-size values exchange r28
and r29 during loading. The entire unit is 7,732 text bytes. A fail-closed
normalizer changes only those register fields in compiler output. It does not
carry retail instruction words, change opcodes or inject data. This is not a
source-only byte-match claim.

The destination is defined at function offset 0x16c and size at 0x178. The
size checks consume the latter at 0x17c and 0x1ac. Destination copies at 0x1b4
and 0x1c8 and the size copy at 0x1d0 cover their remaining consumers. Both
registers are nonvolatile and explicitly saved/restored. The earlier table
initialization values are dead before these definitions.

Nonpositive size and allocation failure bypass the consumers. Both lifetimes
end by 0x1d4. The subsequent assignment pointer freshly defines r29 at 0x208;
that independent lifetime is unchanged. No path consumes either renamed value
through its old register or overwrites an overlapping unrelated value. Calls,
loads/stores, control flow, exception cleanup and saved incoming registers
therefore remain equivalent.

## Guards and source path forward

The tool checks ELF32 big-endian PowerPC shape, complete input/output text and
function hashes, global Init binding/offset/size, all 24 target relocations,
opcodes, plain register-copy form and each expected register field. The second
application repeats all guards and leaves the file unchanged. Atomic output
replacement and success-only stamps prevent failed runs from publishing an
incomplete object. Eight synthetic tests cover bounds, idempotence, malformed
input and metadata, instruction corruption and failed replacement cleanup.

Source trials compared metadata-local declarations, scopes, direct helper
bodies, expression forms, references and whole-unit inline/lifetime options.
Some direct-loading forms reproduce loading allocation but move the mismatch
to the subsequent assignment pointer. No fake use, barrier or padding was
introduced. Once source reproduces both lifetimes, remove the tool and build
step; its hash guards intentionally reject changed compiler output.

## Verification

Independent object comparison verifies all 26 normalized bodies, 263 effective
relocations, exception tables, small data and constant data. The data section
matches with its three natural trailing alignment bytes. Only ten file bytes
change across the seven instructions; all other bytes, symbols, sections and
relocation records stay intact.

A fresh native build with light marked Matching compiles G9SE8P main DOL and
all 17 RELs; all eighteen retail image hashes pass. All-source compilation,
progress/report generation, 63 automated tests, both policies and formatting
pass. An independent second review confirmed the live ranges and normalized
whole-object/relocation comparison. PS2 is a symbolic metadata reference only.
No runtime or physical-hardware validation was performed.
