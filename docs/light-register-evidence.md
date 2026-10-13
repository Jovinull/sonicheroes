# Native light unit evidence

The complete `light.cpp` unit reconstructs all 26 bodies across
`0x80052184–0x80053FB8`, with the C++ language/type evidence recorded in
[language-audit.md](language-audit.md). All 7,732 instruction bytes now match
native compiler output, without an object postprocessor.

The loader keeps the file size in a local file-state aggregate and selects the
default destination with an explicit null check. Together these source choices
reproduce both the loader allocation and the later `AssignData` pointer
lifetime. The checks, allocation, bounded copy, release and error paths remain
unchanged. The aggregate is a reconstruction choice; retained metadata names a
scalar file-size local and does not establish this original source declaration.
No instruction bytes are rewritten and compiler settings remain unchanged.

The earlier direct eight-light restoration loop in `EndIgnoreLight` is
unchanged, including its SDK calls and cached-world behavior.

An independent raw-object audit verifies all 26 instruction bodies in order,
all 263 effective relocations, and every owned non-text section and alignment.
The owned sections contain 232 exception-table bytes, 276 exception-index bytes,
144 data bytes, eight small-data bytes and 16 constant bytes. Three natural
zero alignment bytes follow the 141 authored data bytes. No extra functions
are emitted. Only `Init` differs from the former unnormalized compiler output;
all other functions and non-text storage are unchanged. The register fixer,
its build rule and its synthetic tests have been removed.

An independent final-ELF audit verifies all six owned ranges, all 26 function
addresses and sizes, and all 263 resolved relocation sites against the original
DOL.

The supported G9SE8P all-source and release builds pass. A freshly linked main
DOL and all seventeen RELs match all eighteen reference hashes. All 196 automated
tests, the language policy and all 64 remaining postprocessor checks pass.
Formatting and diff checks pass. PS2 is a symbolic metadata reference only.
Compilation and byte matching do not establish runtime or physical-hardware
validation.
