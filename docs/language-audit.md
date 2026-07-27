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

## Remaining queue

After the dashpanel and set-collision batch:

- 92 legacy `.c` paths still compile as C++;
- 50 of them are outside the protected areas;
- 42 belong to the protected `advertiseD`/`autosaveD` areas;
- 9 C-compiled sources still require an evidence decision;
- no source is approved for `-inline deferred`.

Update this file after every migration batch. A path leaves the queue only
after its configured command, GameCube objdiff and final artifact hashes pass.
