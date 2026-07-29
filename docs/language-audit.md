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
- 9 of those C sources pending stronger language evidence;
- no approved `-inline deferred` source.

The protected `advertiseD` and `autosaveD` areas are not changed while their
owners have active work. Their 42 legacy C++ paths remain in the queue until a
coordinated follow-up.

## Completed batches

### Spring fragments

Migrated:

- `rel/spring_object.cpp`
- `rel/spring_dtor.cpp`
- `rel/spring_assets.cpp`
- `rel/spring_ctor.cpp`
- `rel/spring_clamp.cpp`

Language evidence:

- the corresponding PS2 symbol metadata retains an `o_spring.cpp` source
  marker;
- the same metadata identifies the `TObjSpring` constructor, destructor,
  methods and vtable as C++ symbols;
- the GameCube fragments implement the same object/vtable family and were
  already compiled with `-lang=c++`.

Validation:

- a controlled `.c`/explicit-language versus `.cpp`/inferred-language compile
  produced identical `.text`, `.rodata` and `.data`;
- functional symbols and relocation entries were identical; only the ELF
  `STT_FILE` source-name string changed from `.c` to `.cpp`;
- the complete build relinked all affected stage modules;
- `config/G9SE8P/build.sha1` verified all 18 configured artifacts;
- progress totals remained unchanged.

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

## Remaining queue

After the GameCube platform-main decision:

- 42 legacy `.c` paths still compile as C++;
- none of them are outside the protected areas;
- 42 belong to the protected `advertiseD`/`autosaveD` areas;
- 5 protected sources have direct C++ evidence but remain in C mode until their
  active changes are coordinated;
- no C-compiled game source still awaits a language decision;
- `movieD/cri/sfx.c` is a reviewed C-path/C++-compiler-mode exception, not a
  migration candidate;
- one source, `game/state_accessor.cpp`, has a reviewed `-inline deferred`
  override.

### Reviewed inline exception

`game/state_accessor.cpp` keeps its object-level `-inline deferred` override.
The disc supplies no map, DWARF or named symbols that establish a natural
source order for these anonymous accessors; that absence is recorded rather
than inferred away. The controlled source permutation declares the four
forced-active functions in reverse address order.
With ordinary `-inline auto`, CodeWarrior emits that declaration order:
`fn_800133C8`, `fn_800133A8`, `fn_800133A0`, `fn_80013398`. With the deferred
override, it emits the original GameCube address order:
`fn_80013398`, `fn_800133A0`, `fn_800133A8`, `fn_800133C8`. The latter matches
the target `.text` exactly, including the branchless comparison in
`fn_800133A8`; the ordinary mode does not. The target and both candidates have
no relocations, so there is no hidden relocation tradeoff.

The same controlled comparison was performed for `game/dvd_status.cpp`.
Removing its deferred override preserved the function instructions, jump-table
contents and relocation targets. Only compiler-generated local symbol numbers
changed, which do not affect the linked result. The redundant override was
therefore removed rather than allowlisted.

### Protected C++ migration debt

The following sources are classified in `protected_cpp_c_sources` without
changing their source, split or object configuration:

- `advertiseD/anim_handle.c`
- `autosaveD/menu_selectors.c`
- `autosaveD/table.c`
- `autosaveD/widget_rendering.c`
- `autosaveD/window_input.c`

Language evidence:

- the GameCube `anim_handle.c` callbacks belong to the vtable at
  `lbl_1_data_3740`; the adjacent deleting destructor and constructor both
  install that vtable, and the constructor initializes the same fields in a
  `0x38`-byte object;
- the correlated PS2 symbols identify the corresponding disable, enable,
  display, execute, destructor and constructor sequence as methods of
  `TAdvChallengeEme`;
- a controlled GameCube C++ compile with explicit C ABI reproduced
  `anim_handle.c` code, constants, relocations and functional symbols exactly;
  only the object-file source marker changed from `.c` to `.cpp`;
- the correlated PS2 metadata retains C++-mangled constructors, destructors and
  methods for `ADV_MENU`, `ADV_WINDOW` and `sADV_WINDOW_PARAM`;
- it retains the `ADV_WINDOW` vtable and class record;
- the methods cover the selection, lifecycle, update and rendering behavior
  reconstructed by these four GameCube fragments;
- `table.c` already identifies its deleting-destructor-shaped function and its
  call to CodeWarrior C++ `operator delete`.

These facts prove that the corresponding code belongs to C++ class
implementations; the current matching C fragments do not prove original C
source. PR #116 is an active draft reconstructing the same AutoSaveD classes,
and `advertiseD` has separately announced active local work. This audit
therefore makes no protected-area source, split or configuration change.
Migration must be coordinated with each owner, reviewed against the final
class layout and accepted only after the GameCube object diffs and all 18
artifact hashes remain exact.

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

The five C-mode paths with direct C++ evidence were also compiled in C++ mode
in an isolated temporary output directory. No protected source, split or
configuration was changed.

| current fragment | C++-mode result | integration consequence |
| --- | --- | --- |
| `advertiseD/anim_handle.c` | raw `.text` is identical; all 4 relocation types and offsets are retained | coordinate the final class and external ABI names with the active AdvertiseD reconstruction |
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

The 42 remaining `legacy_cpp_c_sources` already compile as C++. Cross-platform
metadata additionally retains the C++ unit markers `adv_overlay.cpp` and
`as_overlay.cpp`, plus the `TAutoSave`, `ADV_WINDOW`, `ADV_MENU`, `TAS_EMBLEM`,
`TAS_CONG` and `TAS_SAVE` class families. This establishes the module language,
but not every original GameCube translation-unit boundary: many current paths
are artificial matching fragments.

Complete the protected migration in this order:

1. Integrate the reconstructed logical AutoSaveD units from PR #116 after its
   language flags, target diffs and header provenance pass review. Remove every
   absorbed path from the two debt lists in the same change.
2. Re-audit the remaining AutoSaveD list after that integration. Rename only
   fragments that remain independent; merge fragments only where class, data
   and ordering evidence establishes one logical unit.
3. Repeat the same process for `advertiseD` after its active local branch is
   published and coordinated. Do not pre-rename paths that the owner may have
   merged or reconstructed.

Each completed batch must leave no stale policy entry, no `.c` path compiled as
C++ outside a reviewed vendor exception, and no newly introduced C-mode game
source. The final checkpoint is an empty `legacy_cpp_c_sources`,
`protected_cpp_c_sources` and `pending_c_evidence`, together with a clean
language-policy check and all 18 artifact hashes exact.

Until those owners coordinate integration, the checker permits this debt only
under `advertiseD/` and `autosaveD/`. A legacy C++/`.c` entry anywhere else is
a policy error.

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
