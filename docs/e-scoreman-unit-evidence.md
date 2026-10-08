# Complete enemy score-manager translation unit evidence

Positive C++ metadata for enemy/e_scoreman.cpp supplies fifteen methods,
class fields, a singleton, class-name pointer and vtable. The GameCube unit
has twelve emitted bodies; the three technic-point helpers, ResetVariable
and constructor inline. Two additional GameCube methods have no recovered
original names and retain explicit address-based C ABI boundaries. No PS2
instructions were inspected.

| Function | GameCube address | Bytes |
| --- | --- | ---: |
| SaveDestroyEnemyTotalGoal | 0x8011C0C4 | 24 |
| SaveDestroyEnemyTotal | 0x8011C0DC | 12 |
| fn_8011C0E8 | 0x8011C0E8 | 84 |
| fn_8011C13C | 0x8011C13C | 76 |
| ParalyzeEnemy | 0x8011C188 | 56 |
| TornadoEnemy | 0x8011C1C0 | 28 |
| DestroyEnemy | 0x8011C1DC | 28 |
| AddScore | 0x8011C1F8 | 108 |
| Exec | 0x8011C264 | 1012 |
| __dt | 0x8011C658 | 108 |
| DeleteInstance | 0x8011C6C4 | 40 |
| CreateInstance | 0x8011C6EC | 172 |

All twelve bodies occupy 0x8011C0C4–0x8011C798 (1,748 bytes). The preceding
0x8011C01C function is a trigonometric matrix helper, outside the manager.
The following function belongs to enemy power-core logic. Class lifecycle,
field accesses and the vtable anchor the complete surviving inventory.

Owned exception records occupy 0x8000AC88–0x8000ACC8 (64 bytes); six index
records occupy 0x80010D98–0x80010DE0 (72 bytes). Data at 0x802893D8 contains
the 15-byte class name, one alignment byte, and the 44-byte vtable at
0x802893E8. Four bytes of linker alignment follow. The class-name pointer at
0x8042B8C0 and singleton at 0x8042C6D0 are each four bytes with four trailing
alignment bytes. Their former auto-split symbol sizes included alignment;
the typed boundaries now distinguish it from owned objects. Shared player,
team, action, mode, task-parent and heap objects remain external. There are
no owned floating constants. Unemitted ENEMY_CRASH_POWER metadata storage is
not reconstructed as GameCube data.

The final GameCube class size is 0x5C rather than the older symbolic 0x54.
The reconstruction follows GameCube field accesses and allocation size;
release-specific fields and unnamed methods are documented as provisional.
PARAM_SCORE at offset 0x28 has positive metadata support. GameCube also passes
this+0x29 to an unnamed saved-state helper and places the first aligned counter
at 0x2C. ScoreSavedStateBase models that extra address as an empty base; neither
its original name nor base-versus-member identity is established. The external
helper copies saved checkpoint bytes, so a challenge-class name would be an
unsupported inference. The new counter at 0x58 retains a provisional field name.

Signed counters occupy 0x2C/0x30/0x34, player/team IDs 0x38/0x3C/0x40,
timers 0x44/0x48, flags 0x4C, and total/saved-total 0x50/0x54. Construction
clears the counters and timers and initializes the paralyze player ID to -1.
Goal-save snapshots the total and sets its flag. The two unnamed methods
increment the observed counters and conditionally synchronize saved state.
Destroy and tornado events use their observed 240- and 120-frame timers;
paralyze retains the exact player-state checks. Inlined score helpers preserve
the player/team lookup, null handling and award thresholds.

AddScore passes a reference-based PARAM_SCORE subobject address. This preserves
the non-null member-function receiver semantics and avoids the extra nullable
pointer-base adjustment emitted for an implicit pointer conversion. The
restart predicate uses the same metadata-backed local enum snapshot proven
with the complete summoning unit. Canonical names are propagated mechanically
through ten existing source consumers and three existing symbol fixers;
preexisting loose caller declarations are not silently reinterpreted.

The destroyed-enemy award helper holds a read-only reference to its player
pointer slot. The older metadata describes a pointer local; reference syntax
is a reconstruction choice, not an original-source claim. There are no writes
or calls between binding and the last pointer read, and the reference is unused
after the sole external call. It therefore preserves the observed pointer and
null-check behavior while reproducing the inlined register allocation. The
other eleven functions already matched without this adjustment.

All twelve bodies and all 77 owned effective relocations match raw C++ output.
No normalizer, deferred-inline mode or instruction adjustment is used. The
compiler emits the same duplicate weak TObject delete helper as the completed
summoning unit. The final link map explicitly discards that duplicate and its
exception records, selecting Task.cpp's definition at 0x8001895C. The linked
constructor cleanup pointer and all six exception-index entries are exact.

The complete supported G9SE8P release matrix passes with the source marked
Matching: main DOL and all seventeen RELs match all eighteen expected hashes.
All 62 automated tests, language and post-processor policies pass. Independent
source, surviving-atom, relocation and final-link reviews pass. Compilation and
binary comparison do not establish runtime or physical-hardware validation.
