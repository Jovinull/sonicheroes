# Enemy RenderWare frame-search utility evidence

Symbolic compilation unit `0x9af5c5` names enemy/e_utility_rw.cpp and explicitly
classifies it as C++. Its two surviving functions are the public namespace
search and a local callback. GameCube frame-child traversal, animation frame-ID
lookup and the already-correlated motion-path setup caller independently
establish identity. No PS2 instructions were inspected.

| Function | Address | Bytes |
| --- | --- | ---: |
| `nRenderWare::SearchFrameFromFrameID(RwFrame*, s32)` | `0x8011B5A8` | 60 |
| static `callbackSearchFrameID(RwFrame*, void*)` | `0x8011B5E4` | 112 |

The complete text range is `0x8011B5A8–0x8011B654` (172 bytes). Exception
records occupy `0x8000AC08–0x8000AC18` (16 bytes) and their index occupies
`0x80010CD8–0x80010CF0` (24 bytes). No data, constants, zero-initialized
storage or additional function belongs here. The neighboring vector constructor
and SDK animation routines are excluded. Metadata callbackSearchObject and
crash-vector declarations have zero addresses and supply no emitted storage.
The callback's local binding follows its subroutine metadata classification.

The wrapper initializes an eight-byte sSearchFactor with a null result frame
and signed frame ID, traverses the supplied parent's children and returns the
recorded result. It does not test the parent itself. The callback queries each
visited frame's ID, records a match or recursively traverses children, and
always returns the input frame. Once a result exists, subsequent callbacks
skip their search work. Returning null to halt enumeration would change the
observed callback contract and is not introduced.

The opaque RwFrame requires no reconstructed SDK layout. SDK child-enumeration
and ID-query functions retain external bindings. Both bodies match directly
on their first complete compile, including the static callback references and
exception records, with no normalizer or deferred-inlining override. All eleven effective relocations match: seven text references and four
exception-index references. All function identities, offsets, sizes and bindings
agree, as do all section payloads, flags and alignment. Two existing consumer
files contain only canonical name substitutions and formatting changes.
Independent whole-object, source-contract and caller reviews pass.

All-source compilation of the supported G9SE8P main DOL and seventeen RELs
passes, and all eighteen reference image hashes pass. Progress/report
generation, 62 automated tests and both policies pass. Compilation and binary
comparison do not establish runtime or physical-hardware validation.
