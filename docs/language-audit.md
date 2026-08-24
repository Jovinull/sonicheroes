# Source-language migration audit

This file records decisions and validation results for the C/C++ migration.
It contains only the minimum symbolic facts needed for review. It must not
contain proprietary executables, extracted code or complete symbol dumps.

The GameCube build `G9SE8P` is authoritative. PS2 metadata is used only as a
cross-platform classification lead and every completed batch must preserve the
GameCube artifacts.

## Baseline

The initial configured-command audit found 134 game-owned sources:

- 115 compiled as C++ through `.c` plus `-lang=c++`;
- 19 compiled as C;
- 9 of those C sources were initially pending stronger language evidence;
- no approved `-inline deferred` source.

Those nine initial decisions are now closed: `game/main.c` has positive C
source evidence and the other eight are explicitly recorded as reviewed C ABI
boundaries whose historical file language remains unresolved. The current
policy therefore has no `pending_c_evidence` entry.

The coordinated `advertiseD` reconstruction has now replaced all 30 of its
legacy C++/`.c` fragments. AutoSaveD remains protected while PR #116 is a
draft: its 12 legacy C++/`.c` fragments and four C-mode fragments with direct
C++ evidence remain in the queue.

### Integrated-link invariant

A 100% object diff is necessary but not sufficient for integration. Object
comparison can correlate relocations by target address while two reconstructed
objects still spell the same external ELF symbol differently. A completed
batch must therefore run `ninja progress`, which links the DOL and every REL
and verifies all 18 hashes through `build/G9SE8P/ok`; `all_source` or a green
per-function diff alone is not the completion gate.

Post-compile rename targets for externally visible symbols must use the current
canonical name in `config/G9SE8P/symbols.txt`. The combined C++ batch exposed
stale address-label aliases for the `TObject` constructor, destructor and
delete routine, RenderWare callbacks, `RsGlobal`, pathname helpers and endian
converter. Replacing those aliases changed only source or ELF symbol names,
not instructions; every matching source object remained complete in objdiff.

## Completed batches

### AdvertiseD overlay

PR #125 replaces the legacy AdvertiseD fragments with 21 C++ source objects
covering the complete overlay. Its retained `prolog.c` stays in the reviewed C
ABI-boundary category.

Language and boundary evidence:

- the correlated PS2 prototype retains the AdvertiseD class, method and source
  names used to reconstruct the logical C++ units;
- GameCube constructors, destructors, vtables and exception metadata
  independently establish C++ for the class-owned code;
- the GameCube REL remains the authority for every boundary, instruction,
  relocation and owned data range.

Validation:

- all 434 reconstructed source functions and all 21 source objects match;
- the linked AdvertiseD REL is byte-identical to retail;
- `adv_2p.cpp` and `adv_draw.cpp` retain their reviewed
  `-inline deferred,noauto` modes because natural emission does not reproduce
  the target order and data layout;
- all 30 obsolete AdvertiseD paths and the completed protected
  `anim_handle.c` entry were removed from the language-policy debt lists.

### Spring translation unit

`rel/o_spring.cpp` reconstructs the complete shared retail translation unit.
The implementation includes are organizational only; the build has one source
command, one compiler object and one contiguous split in each of the thirteen
stage modules that share this revision. Stage40D contains a different revision
and remains outside this claim.

Language evidence:

- the corresponding PS2 symbol metadata retains an `o_spring.cpp` source
  marker;
- the same metadata identifies the `TObjSpring` constructor, destructor,
  methods and vtable as C++ symbols;
- the GameCube constructor, destructor, methods, two-base vtable layout and
  adjustor thunk independently establish the same C++ object family;
- the contiguous GameCube range fixes the complete unit at `.text`
  `0x88C`–`0x18A4`, including all thirteen functions.

Validation:

- `.text`, `.ctors`, `.rodata` and `.data` all match byte-for-byte, including
  every relocation;
- `-inline auto` emits the transform helper before `springExec`, while
  `-inline deferred,auto` emits the retail `springExec`-then-helper order. The
  PS2 `o_spring.cpp` marker, class relationships and contiguous GameCube object
  establish that these routines belong to one natural source family rather
  than unrelated fragments, and deferred mode reproduces the complete retail
  function and section order;
- ordinary multiple-inheritance C++ emits the retail eight-byte secondary-base
  adjustor. The post-compile normalizer removes only the compiler-only
  standalone forwarding method and duplicate class vtable, then retargets and
  names that generated adjustor; it does not add or replace instructions;
- the unreferenced transform helper is explicitly retained by each affected
  module's linker configuration;
- the complete build relinked all thirteen affected stage modules;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- the language-policy check passes with `rel/o_spring.cpp` recorded as an
  approved deferred source.

### Tri-spring and switch fragments

Migrated 13 `rel/tri_spring_*`, `rel/switch_*` and
`rel/push_pull_switch_register.cpp` paths.

Language evidence:

- the corresponding PS2 metadata retains `o_3spring.cpp` and `o_switch.cpp`
  source markers;
- it identifies `TObj3Spring`, `TObjTriSpring`, `TObjSwitch` and
  `TObjSwitchPushPull` constructors, destructors, methods and vtables;
- the GameCube fragments implement those object/vtable families and were
  already compiled with `-lang=c++`.

Validation:

- all 13 configured commands remained C++ with the object-level language
  overrides removed;
- the complete build relinked the affected stage modules;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### Dashpanel and set-collision fragments

Migrated five `rel/dashpanel_*` and `rel/set_collision_*` paths.

Language evidence:

- the corresponding PS2 metadata retains `o_dashpanel.cpp` and
  `o_set_collision.cpp` source markers;
- it identifies `TObjDashpanel` and `TObjSetCollision` constructors,
  destructors, methods and vtables;
- the GameCube fragments implement those object/vtable families and were
  already compiled with `-lang=c++`.

Validation:

- all five configured commands remained C++ with the object-level language
  overrides removed;
- the complete build relinked the affected stage modules;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### Object registration fragments

Migrated 14 `rel/*_register` paths for propeller, light/invoke collision,
cannon, ironball, jump panel, checkpoint, container, weight, lens-flare and
goal-ring families.

Language evidence:

- the local PS2 metadata retains the corresponding C++ unit markers,
  including `o_propeller.cpp`, `o_light_colli.cpp`, `o_invoke_colli.cpp`,
  `o_weight.cpp`, `o_weight_ext.cpp`, `ef_lensflare.cpp` and
  `o_goalring.cpp`;
- the same metadata identifies the associated `TObj*` class, constructor,
  method, class-record and vtable families;
- the GameCube fragments register those same object families, contain C++
  linkage declarations and were already compiled with `-lang=c++`.

Validation:

- all 14 configured commands remained C++ with the object-level language
  overrides removed;
- the complete build relinked every affected stage module;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### Object asset fragments

Migrated 13 `rel/*_assets` paths for pawn, item box, pole, case, roll door,
signal, dash ring, reel, laser fence, big rings, cage, target and fan
families.

Language evidence:

- local PS2 metadata retains the corresponding C++ unit markers
  (`e_pawn.cpp` and the relevant `o_*.cpp` units);
- it also identifies the associated constructors, methods, class records and
  vtables, including `TObjEnemyPawn`, `TObjItembox`, `TObjDashring`,
  `TObjLaserfence`, `TObjBigrings` and the remaining object families;
- the GameCube fragments provide data/factory portions of those same families
  and were already compiled with `-lang=c++`.

Validation:

- all 13 configured commands remained C++ without per-object language
  overrides;
- the complete build relinked every affected stage module;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### System and sample fragments

Migrated the 12 object/registration fragments for system objects 1-4 and
sample objects 1-2.

Language evidence:

- local PS2 metadata retains `o_system1.cpp` through `o_system4.cpp`,
  `o_sample.cpp` and `o_sample2.cpp` unit markers;
- it identifies the matching `TObjSystem1` through `TObjSystem4`,
  `TObjSample` and `TObjSample2` class-record/vtable families;
- the GameCube fragments split those same six units into object and
  registration portions, all already compiled with `-lang=c++`.

Validation:

- all 12 configured commands remained C++ without per-object language
  overrides;
- the complete build relinked every affected stage module;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### Shared object-family fragments

Migrated ten small `rel/obj_*` and `rel/scroll_ring_*` fragments.

Language evidence:

- these are artificial GameCube split fragments located inside already
  identified C++ object-family runs, not standalone C translation units;
- their neighboring runs correspond to local PS2 C++ markers such as
  `o_sample.cpp`, `o_switch.cpp`, `o_set_collision.cpp`, `o_ironball.cpp`,
  `o_dashpanel.cpp` and `o_ring.cpp`;
- the PS2 metadata also retains the matching `TObject` and `TObjScrollRing`
  class/vtable families;
- the GameCube fragments require C++ linkage or language features (including
  inheritance and a virtual call) and were already compiled with `-lang=c++`.

Validation:

- all ten configured commands remained C++ without per-object language
  overrides;
- the complete build relinked every affected stage module;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### RenderWare platform callback fragments

Migrated `game/object_dispatch.cpp`, `game/path.cpp`, `game/time.cpp` and
`game/task_create.cpp`. These remain separate reconstruction fragments because
the GameCube evidence establishes each function range but not the original
translation-unit boundaries.

Language evidence:

- their implementations correlate with the RenderWare platform callbacks
  `psPathnameDestroy`, `psPathnameCreate`, `psTimer` and
  `psCameraShowRaster`;
- the corresponding PS2 callbacks retain C linkage in the same platform-code
  run as the private C++-mangled `TimerHandler__Fi`, establishing C++ compiler
  mode with a C ABI for that counterpart;
- the GameCube fragments now express that distinction with `.cpp` paths and
  explicit `extern "C"` boundaries rather than treating an unmangled symbol as
  proof of C source.

Validation:

- controlled C and C++ compiles produced identical `.text` for three fragments;
- the pathname-create fragment required only the explicit `void *` conversion
  that C++ requires;
- the complete build relinked `main.dol` and all modules;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### Game endian-conversion translation unit

Reconstructed `game/Endian.cpp` (`.text` `0x8004BECC`–`0x8004C160`) as C++.

Language and boundary evidence:

- the PS2 debug symbols independently retain the neighboring
  `TEndianCnv::ConvAnyParameter`, `TEndianCnv::ps2uNtoHS` and
  `TEndianCnv::ps2uNtoHL` C++ conversion family;
- the five-function GameCube conversion run terminates in its own static
  initializer and corresponding `.ctors` word at `0x802398D0`; the preceding
  object's initializer ends immediately before `0x8004BECC`, establishing
  both ends of the object independently of instruction similarity.

Validation:

- all six functions, 660 bytes of `.text`, and the four-byte `.ctors` section
  match exactly in objdiff;
- the fresh build linked every configured artifact;
- `config/G9SE8P/build.sha1` verified all 18 artifacts;
- the language-policy check passed with the source compiled in C++ mode.

### GameCube platform heap

Migrated `game/heap.cpp` while preserving explicit C linkage for the public
memory boundary and C++ linkage for its private helpers.

Language evidence:

- the GameCube unit provides the same memory-function boundary represented on
  PS2 by `psGetMemoryFunctions`, `Free_BW` and `MAlloc_BW`;
- those PS2 public entries retain C linkage, while their neighboring private
  allocator helpers are C++-mangled;
- a controlled GameCube C++ compile preserved all function code;
- CodeWarrior C++ declaration-order `.sbss` emission reproduces the target
  variable order directly. The former C reconstruction declared the variables
  in reverse to compensate for C first-reference emission.

Validation:

- all eleven functions, exception records, relocations and 32 bytes of `.sbss`
  match the GameCube target;
- the complete build relinked `main.dol` and all modules;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

### GameCube platform main

`game/main.c` remains a confirmed C source. This is a platform-specific
decision based on the matching target, not an inference from its unmangled
entry points.

Evidence and validation:

- the natural C reconstruction matches all seven functions, exception records,
  relocations and the unit-owned 16-byte `.bss`;
- a direct C++ compile makes `main` eight bytes larger;
- C++ with the public C ABI and equivalent typed structures restores the exact
  size but changes six instructions through register allocation;
- the PS2 platform startup run is C++-compiled, demonstrating why its language
  cannot be copied blindly to a platform-specific GameCube unit;
- the reviewed C form keeps all 18 configured artifact hashes exact without a
  deferred-inline override or register-forcing workaround.

### Game-owned main loop

Added `game/main/main.cpp`, corresponding to the original game-owned
`main.cpp` rather than the unrelated GameCube platform entry point above.
The extra directory prevents the two basenames from resolving to the same
build object.

Language evidence:

- local PS2 beta DWARF identifies the correlated unit as `main.cpp`;
- the same metadata identifies `MAIN::Init()` and signed
  `MAIN::Loop()` methods and the local `MOBJECT_RETURN` enum;
- the GameCube functions reproduce those method relationships and call the
  neighboring `TMainTask` class constructor.

Validation:

- all three functions, exception records, relocations, strings, jump table,
  small data and small BSS match the GameCube target;
- CodeWarrior's four writable-string definitions use staging names so their
  declaration order remains original without triggering a local-address-base
  optimization absent from the target; a post-compile symbol-only rename
  restores the retail labels;
- the complete build relinked the DOL and all modules;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts and the DOL
  retained SHA-1 `9214426b8a3fb1d6fe3dcff09bcc1a959e1e04a8`.

### RenderWare skeleton

Added `game/skeleton.cpp` for the complete GameCube RenderWare skeleton range,
including camera sizing, initialization and shutdown, pathname forwarding,
event dispatch, raster presentation and error reporting.

Language evidence:

- the corresponding PS2 symbols retain the same `RsInitialize`,
  `RsRwInitialize`, `RsRwTerminate`, `RsEventHandler`,
  `RsCameraShowRaster` and `RsErrorMessage` interface;
- that PS2 platform-code run uses C linkage for the public RenderWare
  callbacks alongside a private C++-mangled timer handler;
- the GameCube unit is therefore reconstructed in C++ mode with explicit C
  linkage at the RenderWare boundary, consistent with the adjacent callback
  fragments.

Validation:

- all ten functions in `.text` `0x80011C20` through `0x8001234C` match
  byte-for-byte;
- the complete `extab`, `extabindex`, `.data`, `.bss` and `.sdata` sections
  and their relocations match;
- the complete build relinked `main.dol` and all modules;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts.

### HAnim helpers

Added `game/hAnim.cpp` for the complete HAnim helper unit, including hierarchy
node lookup, animation-key conversion, skin hierarchy attachment and
recursive frame discovery.

Language evidence:

- the PS2 beta symbols identify the same ordered run as methods of
  `HAnimClass`, followed by its constructor, destructor and
  `__sinit_hAnim.cpp`;
- the GameCube unit contains the corresponding C++-mangled class methods,
  global-object destructor registration and `.ctors` entry;
- the source is therefore reconstructed as C++ rather than relying on a
  C-path/C++-mode exception.

Validation:

- all eleven functions in `.text` `0x800BCE78` through `0x800BD1E8` match
  byte-for-byte;
- the complete `extab`, `extabindex`, `.ctors`, `.bss`, `.sbss` and
  `.sdata2` sections and their relocations match;
- the four-byte linker-alignment gap following the unit's 12-byte destructor
  record is explicitly excluded from its `.bss` object;
- the language-policy check and all independent object-level gates pass;
- a clean full link currently stops in pre-existing upstream code:
  `dvd.c` references the missing `__DVDIsBlockInWaitingQueue`, while the
  in-progress GX sources reference the unconfigured `__gxVerif`; this unit
  introduces neither reference.

### Reviewed C ABI and middleware boundaries

The policy distinguishes positive C source evidence from an existing boundary
that is reviewed in C mode but cannot be assigned a historical file language
honestly. `game/main.c` is the sole `confirmed_c_sources` entry. The following
eight paths are instead `reviewed_c_boundary_sources`:

- `advertiseD/prolog.c`
- `autosaveD/prolog.c`
- `movieD/prolog.c`
- `rel/prolog.c`
- `movieD/cri/sfxahn.c`
- `movieD/cri/sfxcnv.c`
- `movieD/cri/sfxset.c`
- `movieD/cri/sud.c`

GameCube validation:

- all eight compile in the configured C mode and match their owned GameCube
  code, data and relocations;
- the four module prologs were also compiled as C++ inside an explicit
  `extern "C"` boundary in an isolated output directory;
- for every prolog, `.text`, owned `.data`, relocation entries and functional
  symbols were identical to the C object; only the local ELF `STT_FILE` source
  marker changed;
- therefore the linked GameCube binary cannot distinguish C source from C++
  source with C linkage for those prologs.

Cross-platform validation used only local symbol metadata from the North
American retail PS2 executable and `stdump` v2.1:

- `stdump identify` found `.symtab` but no `.mdebug`/DWARF source-file table,
  and `stdump files` returned no file records;
- the PS2 overlay exposes mangled prolog names for the advertise, autosave and
  movie modules, establishing C++ linkage for those PS2 counterparts but not
  for the platform-specific GameCube entry stubs;
- the SFX/SUD symbols expose a C ABI and correlate the middleware families, but
  without a source-file/language record they do not prove a historical `.c`
  filename.

The result is intentionally conservative. These paths remain matching C ABI
boundaries and are not silently relabeled as historically confirmed C. A new
entry in this category still requires a reviewed rationale and complete
GameCube validation; the category is not a general escape hatch for new C
files.

## Remaining queue

After the GameCube platform-main decision:

- 12 legacy `.c` paths still compile as C++;
- none of them are outside the protected areas;
- all 12 belong to the protected `autosaveD` area;
- 4 protected sources have direct C++ evidence but remain in C mode until their
  active changes are coordinated;
- no C-compiled game source is silently unclassified: one has positive C
  evidence and eight are explicitly reviewed C ABI boundaries that do not
  claim a historical source extension;
- `movieD/cri/sfx.c` is a reviewed C-path/C++-compiler-mode exception, not a
  migration candidate;
- five sources have reviewed deferred-inline modes:
  `game/skyfs_adx.c`, `game/modeswitch.cpp`, `game/e_paralysis.cpp`,
  `advertiseD/adv_2p.cpp` and `advertiseD/adv_draw.cpp`.

### Reviewed inline exceptions

`game/skyfs_adx.c` needs `-inline deferred`: correlated PS2 metadata establishes
the unified translation-unit order, and the controlled GameCube comparison
shows that ordinary auto inlining changes accessor emission and call sites.
The deferred form reproduces all 19 functions, relocations and owned sections.

`advertiseD/adv_2p.cpp` and `advertiseD/adv_draw.cpp` need the combined
`deferred,noauto` mode to preserve their reviewed function emission and linked
data layout. Both remain exact as part of the complete AdvertiseD object and
REL validation. The policy treats comma-separated inline modes as exact tokens
and rejects unreviewed deferred use.

`game/modeswitch.cpp` also keeps an object-level `-inline deferred` override.
The PS2 beta debug symbols identify the original C++ source and its
`MODESWITCH` constructor, destructor, and setter. Declaring those three
functions in constructor/destructor/setter order under ordinary
`-inline auto` emits the exception records in that same order, while the
GameCube object records setter/destructor/constructor. Deferred emission
reverses the source order and reproduces the target `.text`, `extab`, and
`extabindex`, including every function and exception-table relocation. Its
initializer arrays must remain writable at the same time: const qualification
under deferred emission moves them to `.rodata`, whereas the writable
declarations reproduce the target `.data` byte-for-byte.

`game/e_paralysis.cpp` keeps an object-level `-inline deferred` override for the
same reason. The PS2 beta debug symbols name the original translation unit and
its `TEnemyParalysis` and `sParalysisParam` methods, and the GameCube vtable,
constructor/destructor cleanup records, `TEnemyParalysis` string, private
resource data and static initializer establish the retail unit boundary
independently. Deferred emission reproduces the PS2 method order in the
GameCube object and preserves the retail constructor and destructor exception
metadata. All ten functions and every owned section match byte for byte.

The following sources are classified in `protected_cpp_c_sources` without
changing their source, split or object configuration:

- `autosaveD/menu_selectors.c`
- `autosaveD/table.c`
- `autosaveD/widget_rendering.c`
- `autosaveD/window_input.c`

Language evidence:

- the correlated PS2 metadata retains C++-mangled constructors, destructors and
  methods for `ADV_MENU`, `ADV_WINDOW` and `sADV_WINDOW_PARAM`;
- it retains the `ADV_WINDOW` vtable and class record;
- the methods cover the selection, lifecycle, update and rendering behavior
  reconstructed by these four GameCube fragments;
- `table.c` already identifies its deleting-destructor-shaped function and its
  call to CodeWarrior C++ `operator delete`.

These facts prove that the corresponding code belongs to C++ class
implementations; the current matching C fragments do not prove original C
source. PR #116 is an active draft reconstructing the same AutoSaveD classes.
Migration must be coordinated with its owner, reviewed against the final class
layout and accepted only after the GameCube object diffs and all 18 artifact
hashes remain exact.

### AutoSaveD draft inline audit

PR #116 commit `e78d889` was compiled in an isolated temporary tree against
the proposed GameCube splits. This is evidence for revising the draft, not
approval to edit or integrate the protected area:

- `ADV_MENU.cpp` needs both halves of one `-inline noauto,deferred` override.
  `noauto` preserves the out-of-line `Commit` calls and matching function
  bodies; `deferred` emits the 13 functions in the target order. Twelve
  functions match exactly, while `UpdateQUAD2` remains four bytes short and
  97.273% matching.
- `ADV_WINDOW.cpp` needs `deferred` to reproduce its 147-byte `.data` and put
  the vtable at offset `0x4C`; `noauto` independently preserves the matching
  call structure. The draft still duplicates six functions owned by
  `ADV_WINDOW_DISP.cpp`, omits the 140-byte parameter assignment operator,
  emits 24 rather than 40 bytes of `.bss`, and has incomplete rodata and
  `InitializeCore`.
- The six implemented `ADV_WINDOW_DISP.cpp` functions need `noauto` for their
  bodies and `deferred` for target order. The proposed unit remains incomplete:
  it supplies 1,260 of 5,228 text bytes and 8 of 680 rodata bytes.
- `autosaveD/prolog.c` needs no override. Inherited auto reproduces all 196
  text bytes and all 72 data bytes exactly. Deferred reverses `_prolog`,
  `_epilog` and `_unresolved`, producing a different raw text section even
  though a per-symbol diff can still report each body as matching.

No AutoSaveD path is added to `deferred_sources` until the draft removes its
blanket and duplicate overrides, completes the proposed logical units, records
their final boundaries and relocation results, and preserves all artifacts.

### AutoSaveD draft header provenance

The public-header comparison for PR #116 commit `e78d889` resolved the
provenance question with reproducible CC0 sources:

- 15 RenderWare headers are exact blobs from BFBB commit
  `ea82f4f521ab87b035728d64ab60c08a40aac2e6`; `rwcore.h` adds the local
  `rsglobal.h` include, and `rsglobal.h` is a small project-specific
  declaration;
- the MSL headers correlate with SMS commit
  `b1cfdf687911c5bcc51a5e3715f132600ab32272`; `stdarg.h`, `stddef.h` and
  `fdlibm.h` add only source comments, while `float.h` and `math.h` also adapt
  include or declaration scope;
- BFBB, SMS and the lm-decomp repository named by the `fdlibm.h` comment all
  declare CC0-1.0.

Before the draft leaves draft status, replace the informal `rwsdk/README.md`
wording with a pinned attribution table and identify those local adaptations.
No binary, SDK archive or extracted proprietary source is needed.

### Protected C++ dry run

The four AutoSaveD C-mode paths with direct C++ evidence were also compiled in C++ mode
in an isolated temporary output directory. No protected source, split or
configuration was changed.

| current fragment | C++-mode result | integration consequence |
| --- | --- | --- |
| `autosaveD/menu_selectors.c` | raw `.text` is identical; all 53 relocation types and offsets are retained | absorb into the reconstructed `ADV_MENU` logical unit rather than preserve C-shaped free functions |
| `autosaveD/table.c` | raw `.text` is identical; its one relocation is retained | absorb into `ADV_MENU`; the current pre-mangled `__dl__FPv` placeholder is double-mangled by a naive C++ compile |
| `autosaveD/window_input.c` | raw `.text` is identical; all 11 relocation types and offsets are retained | absorb into the reconstructed `ADV_WINDOW` logical unit and resolve its member/external ABI names together |
| `autosaveD/widget_rendering.c` | does not compile as C++ because the C-only `fn_2_25A8()` non-prototype is called with both three and four arguments | reconstruct the typed member/overload interface in `ADV_WINDOW_DISP`, then repeat the object and relocation comparison |

The matching raw instructions show that four bodies do not need semantic
rewrites merely to enter C++ mode. They do not make a mechanical flag switch
safe: C++ changes the free-function and external symbol names, and wrapping
everything in `extern "C"` would preserve the current C-shaped reconstruction
instead of expressing the evidenced classes. The protected logical-unit
reconstruction must establish the final member names, boundaries and C ABI
edges before the paths are renamed.

### Protected integration plan

The 12 remaining `legacy_cpp_c_sources` already compile as C++. Cross-platform
metadata retains the C++ unit marker `as_overlay.cpp`, plus the `TAutoSave`,
`ADV_WINDOW`, `ADV_MENU`, `TAS_EMBLEM`, `TAS_CONG` and `TAS_SAVE` class
families. This establishes the module language, but not every original
GameCube translation-unit boundary: many current paths are artificial matching
fragments.

Complete the protected migration in this order:

1. Integrate the reconstructed logical AutoSaveD units from PR #116 after its
   language flags, target diffs and header provenance pass review. Remove every
   absorbed path from the two debt lists in the same change.
2. Re-audit the remaining AutoSaveD list after that integration. Rename only
   fragments that remain independent; merge fragments only where class, data
   and ordering evidence establishes one logical unit.

Each completed batch must leave no stale policy entry, no `.c` path compiled as
C++ outside a reviewed vendor exception, and no newly introduced C-mode game
source. The final checkpoint is an empty `legacy_cpp_c_sources`,
`protected_cpp_c_sources` and `pending_c_evidence`, together with a clean
language-policy check and all 18 artifact hashes exact.

Until the AutoSaveD owner coordinates integration, the checker permits this
debt only under `autosaveD/`. A legacy C++/`.c` entry anywhere else is a policy
error.

### GetSpParam

Added `game/GetSpParam.cpp` as a C++ translation unit.

Language and boundary evidence:

- local PS2 debug metadata retains the `GetSpParam.cpp` source marker and the
  `GetSpParam` constructor, destructor and method family;
- the correlated GameCube range has the same ordered 11-method family,
  destructor and static initializer;
- the GameCube object requires C++ exception metadata and global construction.

Validation:

- all 13 functions and the complete `.text`, exception, constructor, BSS and
  floating-constant sections match the GameCube target byte-for-byte;
- the complete build relinked and verified all 18 configured artifacts;
- the language-policy check passes without an exception.

### `game/dAnim.cpp`

`game/dAnim.cpp` and its constructor emission fragment are C++.

Evidence and rationale:

- the PS2 beta metadata retains the `dAnim.cpp` source marker together with
  `DAnimClass` methods, its constructor and its destructor;
- the GameCube run has the same method sequence and RenderWare morph-animation
  calls, followed by the `DAnimClass` global-object initializer;
- both configured C++ objects match their complete text and owned section
  ranges byte-for-byte.

The four-byte constructor is compiled as a separate reconstruction object.
Keeping its empty definition visible in the body object suppresses a constructor
call in the static initializer, while emitting the definition separately
preserves the original constructor-after-initializer text order.

### `game/eventCore.cpp`

`game/eventCore.cpp` is C++.

Evidence and rationale:

- the PS2 beta metadata retains the `eventCore.cpp` source marker,
  `EventVoiceList::GetTopVoiceOffset(int)` and the class-owned
  `eventVoiceTopList` table;
- the GameCube function performs the same event-number lookup against the
  corresponding 64-entry table;
- the configured C++ object matches its complete text and read-only-data ranges
  byte-for-byte.

### `game/SeqFlagCtrl.cpp`

`game/SeqFlagCtrl.cpp` is C++.

Evidence and rationale:

- the PS2 beta metadata retains the `SeqFlagCtrl.cpp` source marker, the
  `TQuestSeqCtrl::CheckSequenceVars(int)` and
  `TQuestSeqCtrl::SetSequenceVars(int)` methods, and the class-owned `seqVars`
  array;
- the GameCube pair performs the same bounded bit lookup and update against the
  corresponding 128-byte array;
- the configured C++ object matches its complete text and uninitialized-data
  ranges byte-for-byte.

### `game/expasm.cpp`

`game/expasm.cpp` is C++.

Evidence and rationale:

- the PS2 beta metadata retains the `expasm.cpp` source marker and
  `Expand2(void*, void*)` symbol;
- the GameCube function is the corresponding bitstream decompressor, including
  the same literal-byte, short-back-reference and long-back-reference forms;
- the configured C++ object matches its complete text range byte-for-byte.

### Movie playback controller

Added `game/moviePlay.cpp` as a C++ translation unit.

Language and boundary evidence:

- local PS2 debug metadata retains the `moviePlay.cpp` marker, the
  `MOVIE_PLAY` method family, `MovieLists` static member and `MoviePlay`
  instance;
- the correlated GameCube range has the same ordered conversion, loop, end and
  initialization methods and the same 29-entry movie table;
- the mangled member functions and static member require C++ linkage.

Validation:

- all five GameCube-emitted functions and every owned code, exception and data
  section match byte-for-byte;
- the complete build relinked and verified all 18 configured artifacts;
- the language-policy check passes without an exception.
### CRI SFX compiler-mode exception

`movieD/cri/sfx.c` remains a `.c` source and retains `-lang=c++`.

Evidence and rationale:

- it is part of the CRI SFX vendor middleware boundary and sits beside the
  C-compiled `sfxahn.c`, `sfxcnv.c` and `sfxset.c` units;
- its externally visible API retains C linkage;
- the matching GameCube object requires CodeWarrior C++ declaration-order
  `.bss` emission; C mode emits those declarations in first-reference order;
- renaming a vendor C-path source without positive C++ source evidence would
  overstate what the binary match proves.

The policy therefore tracks it in `c_sources_compiled_as_cpp`. New game-owned
sources may not use this exception as an escape hatch.

Update this file after every migration batch. A path leaves the queue only
after its configured command, GameCube objdiff and final artifact hashes pass.

### Game Task translation unit

`game/Task.cpp` is reconstructed as C++.

Evidence and rationale:

- PS2 beta DWARF positively identifies the original translation unit as
  `Task.cpp` and supplies the `TMainTask`, `TObject`, heap, task-list, and sleep
  flag names;
- the GameCube virtual-table order, constructor record, exception tables, and
  mangled member symbols independently establish C++ classes and linkage;
- the retail GameCube object and the following PS2 `Memory.cpp` method order fix
  the boundary at `0x80016514`–`0x800189A4`;
- all 34 functions and every owned section match byte-for-byte in objdiff.

CodeWarrior must see mutually recursive inline and destructor bodies before
their retail call sites, but then emits their out-of-line copies in dependency
order. The post-compile normalizer moves those already-matching function and
exception-record units into the retail order and restores split symbol names;
it does not synthesize or alter instructions.

### Game memory translation unit

`game/Memory.cpp` is reconstructed as C++.

PS2 beta DWARF positively identifies `Memory.cpp`, the `THeapCtrl` and `sHeap`
types, all member fields, and all six methods. The contiguous GameCube method
order fixes the original boundary at `0x800189A4`–`0x80018C0C`. All six
functions and every owned section match byte-for-byte in objdiff.

As in `Task.cpp`, CodeWarrior emits the deleting operator before the destructor
whose cleanup uses it. The post-compile normalizer moves the already-matching
function and exception records into retail source order without changing
instructions.

### Game action translation unit

`game/action.cpp` is reconstructed as C++.

The GameCube object directly establishes the language through its mangled
`ACTION` and `FADESCREEN` member symbols, virtual calls, static initializer and
exception metadata. The preceding `Memory.cpp` boundary and the contiguous
retail symbols fix this unit at `0x80018C0C`–`0x8001D764`. All 61 functions
across the five retail split objects match byte-for-byte in objdiff.

`ACTION::Loop` needs `opt_lifetimes off` and a function-scope iterator aggregate
to reproduce CodeWarrior's original register interference graph. Its task loops
remain ordinary indexed C++ and compile to the retail pointer walks. The
post-compile helper restores split symbols, uses the existing retail
switch-table data, and removes a duplicate weak inline-destructor atom that
GC/1.3.2 emits only because the reconstructed unit is compiled in isolation.
It does not alter the instruction bytes of any retail function.

The five entries in `splits.txt` are build fragments of this one C++ source,
not evidence for five original translation units. The four continuation files
contain only an include of `action.cpp`; their purpose is to preserve the
retail object boundaries required by the MetroWerks linker.

### `game/SpAdvStgFailed.cpp`

The PS2 beta debug symbols identify the `SpAdvStgFailed` class, its
`StartFadeOut`, `Disp`, `Exec`, constructor, destructor, and `GoStageFailed`
family. The GameCube virtual table independently fixes the class relationship
and method ordering. The contiguous resource table, resource globals, exception
records, and seven-function code range establish the code object's owned
sections.

The 112-byte animation workspace at `0x80303EC8` is deliberately emitted by the
data-only build fragment `game/SpAdvStgFailed_bss.cpp`. A controlled GameCube
compile showed that the code object emits regular BSS after `hAnim.cpp`'s BSS,
while the retail workspace precedes it. Assigning both the code and workspace
to `SpAdvStgFailed.cpp` therefore creates a linker-order cycle; correlated PS2
names identify the data, but do not override this GameCube ownership evidence.

All seven functions and every assigned section, including the separate BSS
fragment, match byte-for-byte. GC/1.3.2 emits a duplicate weak copy of
`TObject::operator delete` when this reconstruction is compiled independently;
the post-compile normalizer removes that compiler-only atom and leaves
exception cleanup bound to the existing retail `TObject` delete routine. It
does not alter any retail function instruction bytes.
