# Source language and compiler evidence

Sonic Heroes' own game code is C++ by default. C is used only where there is
positive evidence for C linkage or where the source belongs to a known C
library. This is a source-fidelity rule: a byte match proves the generated
binary, but it does not by itself prove the original source language, linkage,
class structure or compiler flags.

The machine code in the GameCube binary remains authoritative. Cross-platform
symbols and type information are evidence for names, signatures, classes and
translation-unit structure, but they do not replace a GameCube objdiff.

## GameCube target and PS2 evidence

This project reconstructs the North American GameCube build `G9SE8P`. A
legally obtained North American PS2 retail executable inspected locally during
the language audit retained a Metrowerks symbol table, string table, module
sections and C++-mangled class symbols. It also retained synthetic source-name
markers for hundreds of `.cpp` units. This is strong evidence that the shared
game code was predominantly C++, and it can help classify corresponding units.

The PS2 build is not the matching target. Platform-specific files, source
boundaries, compiler options and implementations can differ. A PS2 name or
`.cpp` marker is accepted only after the symbol or unit is correlated with the
GameCube build; the resulting GameCube object must still pass objdiff. An
unmangled callback may still live in a C++-compiled unit through `extern "C"`;
linkage and compiler language must be recorded as separate conclusions.

This audit does not make proprietary PS2 material part of the project:

- contributors do not need a PS2 disc or executable;
- no disc image, executable, extracted code or complete symbol dump is stored
  or linked by this repository;
- maintainers record only classifications and small, necessary symbolic facts;
- anyone doing their own cross-platform check must use a copy they are legally
  entitled to inspect and keep it in an ignored local location such as `orig/`.

### Optional PS2 symbol workflow

Cross-platform symbol analysis is optional. It classifies source language,
linkage, names and class relationships; it does not establish a GameCube code
match.

1. Keep a legally obtained PS2 executable only in an ignored local path. Never
   upload it or add a download link.
2. Inspect it locally with a public symbol-analysis tool such as
   [ccc](https://github.com/chaoticgd/ccc), and record the tool version and game
   region used for the check.
3. Look for C++-mangled methods, constructors, destructors, vtables, source-name
   markers and neighboring class symbols. Treat an unmangled name as linkage
   evidence only.
4. Correlate the PS2 fact with the GameCube target through behavior, call or
   data relationships, strings, class context or other independent evidence.
   Addresses are platform-specific and do not correlate a function by
   themselves.
5. Record only the minimum symbolic facts in the pull request: the GameCube
   unit, the corresponding PS2 symbol or source marker, the inference, its
   confidence and the GameCube objdiff/relocation result. Mark any proposed
   translation-unit boundary as a hypothesis unless direct metadata supports
   it.

The useful PS2 input is metadata in the executable, not its program code. For
the North American retail build used in the audit, the local executable is
commonly named `SLUS_207.18`. A contributor who owns that build may keep it at
an ignored path such as `orig/ps2/SLUS_207.18`; this name is an identifier, not
a download instruction.

With the public MIT-licensed
[Chaos Compiler Collection](https://github.com/chaoticgd/ccc) installed, inspect
only the view needed for the current question:

```sh
stdump identify orig/ps2/SLUS_207.18
stdump files --sort-by-address orig/ps2/SLUS_207.18
stdump functions --sort-by-address orig/ps2/SLUS_207.18
stdump globals --sort-by-address orig/ps2/SLUS_207.18
stdump sections orig/ps2/SLUS_207.18
```

`identify` establishes which symbol formats are actually present. `files`
provides source markers; `functions` and `globals` provide names and typed facts
only when the table contains them; `sections` supplies context. Empty or
incomplete output is not evidence for C. Raw ELF sections and symbol spellings
can be checked locally with `readelf -SW` and `readelf -Ws`; retain the raw name
if a demangler does not recognize it.

PS2Recomp and MIPS code analyzers are not required for a source-language
decision. They may generate code or disassembly that cannot be published here,
while the symbol table already supplies the allowed evidence. Prefer symbol
metadata and do not generate extra proprietary output without a separate,
necessary research purpose.

Use this minimal record in a pull request:

```text
GameCube unit:
GameCube symbol or behavior:
PS2 region/build:
PS2 symbolic fact:
Independent correlation:
Inference (language/linkage/name/TU):
Confidence:
GameCube objdiff and relocation result:
```

Do not include a PS2 address unless it is indispensable to explain the local
correlation, and never include a listing, dump, personal path or code excerpt.

Do not attach tool dumps, extracted assembly, executables or complete symbol
lists. Public analysis tools are reproducibility aids; their output is not a
substitute for reviewing the evidence or matching the GameCube object.

## New source

- New game-owned translation units use `.cpp` and compile as C++.
- A new `.c` file under `game`, `rel`, `advertiseD`, `autosaveD` or `movieD`
  must be added to the reviewed C allowlist in
  `config/G9SE8P/language_policy.json`.
- Do not use `extern "C"` merely to keep a C-shaped reconstruction when the
  evidence identifies a C++ method. C linkage remains appropriate for real C
  boundaries and for temporary unknown symbols, but the reason must be clear.
- Shared declarations belong in `include/`; private declarations stay in their
  translation unit.

Most repository `.c` files explicitly compiled with `-lang=c++` are listed as
legacy paths in the policy file. The compiler already treats those files as
C++; migration aligns the extension and build configuration with the effective
language rather than rewriting working code.

There are two reviewed exceptions. `movieD/cri/sfx.c` remains a C-path vendor
source while compiling in C++ mode. This CRI middleware unit exposes a C
boundary and belongs beside the other `sfx*.c` sources, but the matching
GameCube build requires CodeWarrior's C++ declaration-order `.bss` emission
instead of its C first-reference order.

`game/skyfs_adx.c` is positively identified as C by the PS2 beta DWARF
filename and language metadata, while its GameCube object requires
CodeWarrior's C++ compilation path. The same evidence establishes that the
previous state, DVD-status, accessor and file-system fragments are one source
file. Both exceptions remain in `c_sources_compiled_as_cpp`, retain explicit
`-lang=c++`, and are not part of the extension-migration queue.

Migrate them in reviewable, module-sized batches:

1. record direct C++ evidence and inspect correlated PS2 symbol/source metadata
   when that counterpart exists;
2. capture the current GameCube object and objdiff result;
3. rename `.c` to `.cpp`, update `configure.py` and every split path, and remove
   only the now-redundant `-lang=c++` override;
4. rebuild the affected object and require identical code, data and relocations;
5. run the complete artifact hash check and remove the old path from
   `legacy_cpp_c_sources`.

Do not combine that mechanical rename with class reconstruction or other
semantic changes. A mass rename would touch hundreds of split entries, obscure
regressions and collide with active work. Coordinate ownership before touching
an area with active work, especially `advertiseD` or `autosaveD`.

## Evidence levels

A language decision should record the strongest available evidence:

1. A mangled CodeWarrior symbol, constructor, destructor, vtable or class method
   is direct C++ evidence.
2. An unmangled symbol in a reliable map is C-linkage evidence, but it may still
   be an `extern "C"` function compiled by a C++ compiler.
3. Known original library source or matching SDK versions can establish the
   library language.
4. Cross-platform PS2 or PC symbols can establish names, signatures and class
   membership after the function is independently correlated with the
   GameCube build.
5. Compiler-specific data emission can distinguish modes when the target order
   is reproduced directly: record the declarations, relocations and full
   artifact result, not only the raw `.text`.
6. A byte match alone does not establish C versus C++.

Exception metadata also has a narrow meaning: one `extab`/`extabindex` record
can establish a function range, but it does not establish an original
translation-unit boundary. A one-function source may remain a reconstruction
fragment until cross-references, private data, alignment, map/debug metadata or
correlated platform evidence establishes the enclosing unit.

Guesses stay marked as guesses. The policy file separates confirmed C sources
from sources that are temporarily allowed to remain C while evidence is being
collected. It separately records `protected_cpp_c_sources`: sources with direct
C++ evidence that still compile as C only because an active protected-area
change must be integrated first. This is migration debt, not a C allowlist and
not permission to edit another contributor's work. No new path may be added to
either temporary list merely to make CI pass.

A protected C++/C-mode source must be migrated after coordinating with the
active owner. The integration change reconstructs the C++ class or method
shape, uses `.cpp`, updates build and split paths, and must preserve the
GameCube objdiff and all configured artifact hashes. Until that coordinated
change is ready, central policy and documentation may record the evidence but
the protected source, split and object configuration stay untouched.

Public symbol indexes, community disassemblies and small necessary textual
symbol-name excerpts are acceptable references. A contributor may inspect a
legally obtained copy locally under `orig/`, which is ignored and blocked by the
commit hook. Never commit or link disc images, executables, extracted assembly,
complete proprietary symbol dumps, leaked source or other proprietary
artifacts; see `LEGAL.md`.

## Inline policy

`-inline deferred` is not a language switch. It can change inlining and function
emission order, so applying it globally can invalidate matching objects even
when section sizes remain unchanged.

Before enabling a deferred mode for a game-owned translation unit, document:

- the natural source order suggested by symbols, DWARF or class structure;
- the order emitted by each candidate compiler flag;
- the GameCube objdiff and relocation result;
- at least one concrete reason the deferred result represents the original
  build rather than a convenient permutation.

The approved deferred list is deliberately narrow. At present,
`game/skyfs_adx.c` is the only reviewed entry. Natural PS2 symbol order and
GameCube section adjacency establish the unified TU order; `-inline auto`
changes the accessor emission and call sites, while `-inline deferred`
reproduces all 19 functions, relocations, and owned sections byte-for-byte and
passes the retail DOL SHA-1 gate. A source must be added to `deferred_sources`
in the policy file in the same reviewed change that records the evidence, and
stale entries must be removed with the flag they approved. Multiple
object-level `-inline` overrides are rejected as ambiguous.

## Pull-request requirements

For language, linkage or inline changes:

- keep the change to one logical translation unit or one mechanical module;
- state the evidence and whether it is GameCube, PS2, PC or known-library
  evidence;
- show the before/after objdiff result;
- do not turn matching objects into non-matching objects in a mechanical
  language-only change;
- run `python tools/check_language_policy.py`, `ninja` and the artifact SHA-1
  check.

Existing matching work is a test oracle, not disposable work. Refactor it
incrementally when evidence improves the source reconstruction, preserving the
binary at every completed step.
