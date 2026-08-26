# Units returned to NonMatching

Forty-five post-processor steps carried a zlib-compressed copy of the retail
object and wrote it over whatever the compiler produced. The unit then measured
the original against itself: `build.sha1` passed because the artifact *was* the
artifact, and the source had no bearing on the result. Those steps are deleted
and their units are `NonMatching` again.

**No source was removed.** Every reconstruction is still in the tree. What
follows is how far each one actually is, measured against the dtk target with
the step gone, so the work is a roadmap rather than a loss.

Reported progress moves from 10.43% to 7.49% of code and 5.96% to 5.62% of data.
That is the number the sources actually earn.

## What is left, per unit

Counted in instructions. **registers** are differences confined to register
fields, the shape a post-processor is allowed to normalise. **other** are real
instruction differences. **length** is functions whose size does not match at
all, usually a missing or extra block.

| unit | left | registers | other | length | size |
| --- | ---: | ---: | ---: | ---: | ---: |
| `rel/e_mask_stage11` | 32 | 3 | 0 | 29 | 1125 |
| `rel/e_tree_stage11` | 36 | 1 | 0 | 35 | 935 |
| `game/cri/axrna` | 48 | 20 | 11 | 17 | 1541 |
| `rel/e_grass2_stage11` | 49 | 10 | 0 | 39 | 1092 |
| `game/cri/svm` | 50 | 0 | 24 | 26 | 1115 |
| `rel/e_capture_collision_stage11` | 51 | 8 | 20 | 23 | 401 |
| `rel/e_fan_stage11` | 54 | 9 | 22 | 23 | 518 |
| `game/cri/rnares` | 55 | 0 | 0 | 55 | 251 |
| `rel/e_grass_stage11` | 69 | 19 | 1 | 49 | 1385 |
| `rel/e_s11_flag_stage11` | 82 | 18 | 13 | 51 | 1741 |
| `rel/e_rinoliner_stage11` | 90 | 15 | 0 | 75 | 1929 |
| `rel/e_flyer_path_stage11` | 96 | 0 | 0 | 96 | 2268 |
| `rel/e_spider_stage11` | 108 | 10 | 31 | 67 | 965 |
| `rel/o_s11_door` | 109 | 25 | 47 | 37 | 1352 |
| `rel/o_s12_celestial_sphere` | 142 | 13 | 104 | 25 | 799 |
| `rel/object_effects_stage11` | 150 | 0 | 0 | 150 | 935 |
| `rel/e_strategy_rinoliner_stage11` | 156 | 8 | 24 | 124 | 990 |
| `rel/e_strategy_magician_stage11` | 175 | 2 | 50 | 123 | 2199 |
| `rel/e_s11_key_stage11` | 222 | 13 | 139 | 70 | 1640 |
| `rel/e_flyer_collision_stage11` | 232 | 8 | 39 | 185 | 1377 |
| `rel/e_rinoliner_collision_stage11` | 281 | 14 | 8 | 259 | 2574 |
| `rel/particle_test` | 317 | 0 | 0 | 317 | 735 |
| `rel/e_strategy_flyer_stage11` | 341 | 52 | 81 | 208 | 4833 |
| `rel/e_capture` | 362 | 33 | 31 | 298 | 5335 |
| `rel/put_particle` | 420 | 0 | 0 | 420 | 808 |
| `rel/e_wall_stage11` | 470 | 34 | 37 | 399 | 6670 |
| `rel/sp_dashpanel` | 475 | 0 | 0 | 475 | 740 |
| `game/rw_gcn_raster` | 483 | 165 | 291 | 27 | 3771 |
| `rel/light_collision_stage11` | 489 | 6 | 8 | 475 | 1168 |
| `rel/spboss_throw_object` | 517 | 0 | 1 | 516 | 794 |
| `rel/e_turtle_stage11` | 623 | 53 | 236 | 334 | 5025 |
| `rel/e_flyer_stage11` | 649 | 39 | 8 | 602 | 4582 |
| `rel/sp_dashring` | 697 | 0 | 0 | 697 | 954 |
| `rel/propeller_stage11` | 805 | 5 | 6 | 794 | 2655 |
| `game/rw_gcn_allinone` | 818 | 13 | 51 | 754 | 2558 |
| `rel/chao_beans` | 842 | 0 | 0 | 842 | 866 |
| `rel/e_magician_stage11` | 962 | 5 | 6 | 951 | 2786 |
| `rel/form_gate_sub` | 1004 | 0 | 0 | 1004 | 1017 |
| `rel/sky_bobsleigh_path` | 1231 | 0 | 0 | 1231 | 1410 |
| `game/rw_gcn_render` | 1257 | 225 | 365 | 667 | 7042 |
| `rel/player_effects` | 1632 | 0 | 0 | 1632 | 1695 |
| `rel/o_colli_communication_stage11` | 1757 | 0 | 2 | 1755 | 2212 |
| `rel/goal_ring_stage11` | 1761 | 6 | 18 | 1737 | 3081 |
| `game/rw_gcn_core` | 2020 | 32 | 288 | 1700 | 7601 |
| `rel/sp_eff_dash` | 4490 | 0 | 0 | 4490 | 4561 |

## Where to start

The eight closest are within sixty instructions, and several of those are almost
entirely register colouring — the one gap a step may legitimately close:

- `rel/e_mask_stage11` (32 left, 29 of them length)
- `rel/e_tree_stage11` (36, 35 length)
- `game/cri/axrna` (48; 20 registers, 11 other, 17 length)
- `rel/e_grass2_stage11` (49, 39 length)
- `game/cri/svm` (50; 24 other, 26 length)

For `game/cri/axrna` the length gap is one loop: retail unrolls the sixteen-entry
scan in `fn_8022439C` eight times and this build keeps it rolled with `mtctr`.
No pragma or flag tried so far reproduces it — `opt_unroll_loops`, `opt_unrolling`,
`optimization_level 4`, `-opt unroll`, `-opt speed`, `-inline all` all leave it.
Worth knowing: `-O4,s` on that unit drops the rest of the gap from 31 differences
to 11, so the unit flags are probably not right either.

## The rule that now stops this

`tools/check_post_processors.py` rejects a module-level constant longer than 256
bytes that reaches a decode or decompress call. A blob is neither a hex literal
nor an integer table, so the two earlier rules did not see it. CI runs the check.
