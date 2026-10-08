# Enemy timer utility translation unit evidence

C++ symbolic metadata identifies `enemy/e_utility_system.cpp` and exactly two
namespace functions: `void nSystem::DecreaseTimer(s32&)` and
`void nSystem::IncreaseTimer(s32&)`. GameCube enemy timer callers and the paired
increment/decrement operations independently corroborate those reference
signatures. No PS2 instructions were inspected.

| Function | GameCube address | Bytes |
| --- | --- | ---: |
| `nSystem::DecreaseTimer` | `0x80137FE8` | 104 |
| `nSystem::IncreaseTimer` | `0x80138050` | 104 |

The complete surviving unit occupies `0x80137FE8–0x801380B8` (208 bytes).
Both functions are leaves, with no exception records or owned data, constants,
BSS or constructors. Their sole global dependency is the external mode-switch
singleton. The metadata's zero-address ENEMY_CRASH_POWER entry does not define
storage here.

The preceding five auto-grouped helpers operate on flags and a set-object
list; the last finishes its loop before `0x80137FE8`. The following body uses
quest/progress tables. Neither group implements a remaining metadata timer
method. Thus the complete two-method inventory and caller semantics establish
ownership independently of the original coarse auto split.

The native predicate reads signed bytes at mode offsets `0x1F`, `0x20` and
`0x21`, returning false when any is nonzero. Only when all are zero does the
helper decrement or increment its referenced signed integer. No clamp, null
check, or extra mode check is added. The exact original predicate name is not
established: `TimerCanAdvance` and private view field names are explicitly local
reconstruction labels. The source uses the observed GameCube offsets without
importing a different platform's mode layout.

Both functions match directly with ordinary automatic inlining; the local
predicate emits no extra standalone body. No deferred override or object
normalizer is added. Existing REL declarations/calls receive only canonical
symbol substitutions, retaining their provisional pointer ABI and arguments;
this does not claim their full classes have been reconstructed.

Both exported identities, bindings, offsets, sizes and effective relocations
match, with no extra allocated sections or helper bodies. The supported
G9SE8P main DOL and all 17 RELs compile and pass all 18 reference hashes.
All 62 automated tests, both language/post-processor policies and source-format
hooks pass. Compilation and binary comparison do not establish runtime
validation.
