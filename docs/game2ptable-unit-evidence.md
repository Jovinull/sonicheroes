# Two-player game table translation unit evidence

Symbolic metadata identifies `game2pTable.cpp` as C++. The complete five-function
inventory correlates with GameCube callers, table references, and locator
fallbacks. No PS2 instructions were inspected. GameCube table counts and values
are authoritative: the other platform has different table lengths.

| Function | GameCube address | Bytes |
| --- | --- | ---: |
| `game2pCallIntroVoice` | `0x8011F3B0` | 416 |
| `game2pGetMainMemberNo` | `0x8011F550` | 240 |
| `game2pSetLimitTime` | `0x8011F640` | 168 |
| `game2pSetGoalPosition` | `0x8011F6E8` | 212 |
| `game2pSetStartPosition` | `0x8011F7BC` | 216 |

All surviving code occupies `0x8011F3B0–0x8011F894` (1,252 bytes). The preceding
return-only rendering/lifecycle body and following enemy-class getter are
outside the independently identified five-function inventory. Ownership also
includes `extab` at `0x8000AEFC–0x8000AF1C` (32 bytes), `extabindex` at
`0x80010F0C–0x80010F3C` (48 bytes), and data at `0x80289930–0x80289A78`.
The latter contains 324 bytes of tables and four trailing alignment bytes:
18 time records, one start position, nine goal positions, and five voice IDs.
No BSS, literal pool, constructor, or vtable belongs to this unit. Shared mode,
team and action globals remain external references.

The private views describe accessed GameCube offsets only. Metadata and native
accesses agree on signed mode/player/member bytes, team member numbers at
`0x110`, player pointers at `0x114`, stage at action offset `0x2C`, and start
locator selection through team offset `0x34`. Goal and start locator return
types preserve their distinct metadata identities and position prefixes.
The repeated stage 37 goal entry is retained, including first-match behavior.
Null output pointers still report successful lookups. Unsupported intro modes
retain the retail selector's lack of initialization; no default voice is
invented.

## Compiler evidence and measured remainder

With ordinary automatic inlining, callee-before-caller definitions produce all
five correct-sized bodies in the wrong order. Placing those definitions in
retail order instead prevents the intro function from inlining member selection:
intro shrinks to 220 bytes and total text to 1,056. Deferred automatic inlining
reproduces both the inline topology and the observed five-body emission order.
This is a whole-unit compiler setting, not a per-function workaround.

An explicit switch for the active-member result preserves the native branch
shape. Metadata-named cached `Stage_Current` locals recover the native global
and table load order. Those source changes make four bodies instruction-exact.
Twenty-four intro declaration/scope variants and five inline-local assignment
and lifetime variants leave the final allocation difference unchanged.

`fix_game2ptable_registers.py` records that remaining difference: 12 register
fields in ten instructions of the intro function. The team and previous-member
locals exchange r29/r30 from offset `0x18` through their last use at `0xDC`.
Physical stack saves/restores stay unchanged. Both registers are callee-saved,
call arguments and branch conditions agree, and both locals are dead after
`0xDC`. Independent native inspection also confirms that the two callees
reached while these locals are live neither read nor write r29/r30. The final
voice call occurs after both lifetimes and preserves its own saved registers. No opcode, immediate, branch, relocation, table or exception record is
changed. The tool carries no retail instruction words. Whole-text/function
hashes, exact function bounds/binding, and relocation checks fail closed;
repeated application is a no-op. Remove it when source/compiler choices recover
the allocation directly.

The whole-object audit checks all five symbol boundaries/bindings, all 50
effective relocation sites/types/targets/addends, and every owned section.
Raw compiler output differs only in those ten instruction words; normalized
output matches, with only the four natural data alignment bytes projected.
The supported G9SE8P main DOL and all 17 RELs compile and pass all 18
reference hashes with the whole unit enabled as Matching. All 70 automated
tests and both language/post-processor policies pass.
Compilation and binary comparison do not establish runtime validation.
