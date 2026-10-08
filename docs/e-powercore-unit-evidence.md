# Complete enemy power-core translation unit evidence

Positive C++ metadata for enemy/e_powercore.cpp identifies twenty-one methods,
the power-core object and manager, their fields and owned storage. Fourteen
functions survive; seven constructors/helpers inline into their callers. No
PS2 instructions were inspected.

| Function | GameCube address | Bytes |
| --- | --- | ---: |
| DecideTypeFromLeaderPlayerNumber__18TEnemyPowerCoreManFi | 0x8011C798 | 520 |
| EntryEx__18TEnemyPowerCoreManFPC5RwV3di | 0x8011C9A0 | 452 |
| Entry__18TEnemyPowerCoreManFPC5RwV3di | 0x8011CB64 | 52 |
| Exec__18TEnemyPowerCoreManFv | 0x8011CB98 | 536 |
| __dt__18TEnemyPowerCoreManFv | 0x8011CDB0 | 116 |
| DeleteInstance__18TEnemyPowerCoreManFv | 0x8011CE24 | 32 |
| GetInstance__18TEnemyPowerCoreManFv | 0x8011CE44 | 172 |
| CreateInstance__18TEnemyPowerCoreManFv | 0x8011CEF0 | 164 |
| TDisp__15TEnemyPowerCoreFv | 0x8011CF94 | 192 |
| Disp__15TEnemyPowerCoreFv | 0x8011D054 | 248 |
| Exec__15TEnemyPowerCoreFv | 0x8011D14C | 1044 |
| __dt__15TEnemyPowerCoreFv | 0x8011D560 | 172 |
| Finalize__15TEnemyPowerCoreFv | 0x8011D60C | 24 |
| Initialize__15TEnemyPowerCoreFv | 0x8011D624 | 332 |

The complete text occupies 0x8011C798–0x8011D770 (4,056 bytes), immediately
after the independently reconstructed score manager. The following 0x8011D770
stub is TObjPlayerFlame::TDisp, anchored by that class's separate vtable and
string; its collision table starts at 0x802894F8 and is excluded here.

Owned exception records occupy 0x8000ACC8–0x8000ADE0 (280 bytes), with eleven
index rows at 0x80010DE0–0x80010E64 (132 bytes). Data at
0x80289418–0x802894F4 (220 bytes) contains three RGBA-real colors, one collision
record, both class strings and two 44-byte vtables. Four trailing bytes are
linker alignment. BSS at 0x803E7F00–0x803E7F88 contains two 68-byte UVFXInfo
records; GameCube places each matrix at offset 4, rather than importing older
platform alignment. Small data at 0x8042B8C8–0x8042B8E0 holds the two-clump
array, two timers and two class-name pointers. Small BSS at
0x8042C6D8–0x8042C6E0 contains the UV animation pointer and manager singleton.
The 48-byte constant pool occupies 0x8042EB38–0x8042EB68. All six file-local
objects retain metadata-backed local binding. No neighboring object storage
or the unemitted ENEMY_CRASH_POWER declaration is annexed.

Allocation sizes are 0xEC for TEnemyPowerCore and 0x54 for its manager, agreeing
with symbolic metadata. The core derives from TObject, C_COLLI and PARAM_SCORE.
C_COLLI is 0x88 bytes; its collision initialization return/parameter types have
independent metadata support. PARAM_SCORE at 0xB0 overlaps the first member
through the observed empty-base layout. It is not a ring-parameter base.
Shared player/team/action/task state and database resources remain external.
The referenced database constructor/search/singleton contract agrees with the
completed database unit; only canonical external names are propagated here.

The parameter constructor intentionally repeats the position-z clear and leaves
speed-z uninitialized, as observed in GameCube. No zero initialization is added
to hide that behavior. The source retains real new-expression cleanup,
collision lifetime, clump ownership, UV animation and rendering operations.
Independent review verifies all fourteen original function containers and
owned data imply 258 effective relocations in the unified unit.

Ordinary automatic inlining leaves GetInstance calling the later CreateInstance
body, while GameCube duplicates that body inside GetInstance and also retains
its independent external definition. Positive cpp metadata and external callers
require both ordinary exported methods. Whole-unit auto,deferred enables the
forward inlining; reversed ordinary definition order restores all fourteen
surviving bodies to their observed order. Neither historical source line order
nor original compiler flags are asserted. No address-taking anchor or object
normalizer is introduced.

Explicit component initialization of the rendering sphere reproduces Disp's
loads and stores. TDisp uses a local reference to its file-local timer entry;
the reference names the same scalar for comparison and update, without changing
when the UV animation advances. All fourteen bodies, owned sections and all
258 effective relocations match after normal duplicate weak-delete resolution
and the four bytes of linker alignment. The compiler's redundant TObject
delete body and exception records are accounted separately, as in the completed
summoning and score-manager units.

Sixty-two existing source consumers and five existing symbol fixers receive only
canonical same-address symbol substitutions and formatting. The collision
constructor/destructor and referenced database API names have positive metadata
and prior complete-unit evidence. No unrelated behavior or signatures are
changed in those consumers. The initial full build found two stale collision
names in shared spring includes; those references were corrected and all affected
consumers rebuilt. The complete supported G9SE8P matrix then passed: main DOL
and all seventeen REL hashes are identical. All 62 automated tests, language
policy and 54 existing post-processor checks pass. Independent final-link review
confirms all fourteen function addresses, owned storage and eleven exception
index rows; the redundant weak delete and associated records are discarded in
favor of the existing Task implementation. The linked constant-section flags
match the baseline linker convention despite the reference object's different
writable flag. Runtime and physical-hardware validation were not performed.
