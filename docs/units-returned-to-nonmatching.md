# Units returned to NonMatching

Forty-five post-processor steps carried a zlib-compressed copy of the retail
object and wrote it over whatever the compiler produced. The unit then measured
the original against itself: `build.sha1` passed because the artifact *was* the
artifact, and the source had no bearing on the result. Those steps are deleted
and their units are `NonMatching` again.

A forty-sixth, `fix_tenkyu_goalring_object.py`, reached the same result without
carrying anything. Its build step listed
`build/G9SE8P/stage40D/obj/rel/tenkyu_goalring.o` — the target object dtk writes
for that split — as a second input, and copied it over the compiler's object.
There was no blob to find, so the rule written for the other forty-five did not
see it. It is deleted too, and `rel/tenkyu_goalring` is in the table below.

**No source was removed.** Every reconstruction is still in the tree. What
follows is how far each one actually is, measured against the dtk target with
the step gone, so the work is a roadmap rather than a loss.

Reported progress moves from 10.43% to 7.49% of code and 5.96% to 5.62% of data,
and removing the forty-sixth takes it to 7.44% and 5.61%. That is the number the
sources actually earn.

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
| `rel/e_flyer_path_stage11` | 92 | 0 | 0 | 92 | 2268 |
| `rel/e_spider_stage11` | 108 | 10 | 31 | 67 | 965 |
| `rel/o_s11_door` | 109 | 25 | 47 | 37 | 1352 |
| `rel/o_s12_celestial_sphere` | 142 | 13 | 104 | 25 | 799 |
| `rel/object_effects_stage11` | 150 | 0 | 0 | 150 | 935 |
| `rel/e_strategy_rinoliner_stage11` | 151 | 8 | 24 | 119 | 990 |
| `rel/e_strategy_magician_stage11` | 175 | 2 | 50 | 123 | 2199 |
| `rel/e_s11_key_stage11` | 222 | 13 | 139 | 70 | 1640 |
| `rel/e_flyer_collision_stage11` | 232 | 8 | 39 | 185 | 1377 |
| `rel/e_rinoliner_collision_stage11` | 276 | 14 | 8 | 254 | 2574 |
| `rel/particle_test` | 317 | 0 | 0 | 317 | 735 |
| `rel/e_strategy_flyer_stage11` | 334 | 52 | 81 | 201 | 4833 |
| `rel/e_capture` | 362 | 33 | 31 | 298 | 5335 |
| `rel/put_particle` | 420 | 0 | 0 | 420 | 808 |
| `rel/e_wall_stage11` | 461 | 34 | 37 | 390 | 6670 |
| `rel/sp_dashpanel` | 475 | 0 | 0 | 475 | 740 |
| `game/rw_gcn_raster` | 483 | 165 | 291 | 27 | 3771 |
| `rel/light_collision_stage11` | 489 | 6 | 8 | 475 | 1168 |
| `rel/spboss_throw_object` | 517 | 0 | 1 | 516 | 794 |
| `rel/e_turtle_stage11` | 617 | 53 | 236 | 328 | 5025 |
| `rel/e_flyer_stage11` | 641 | 39 | 8 | 594 | 4582 |
| `rel/sp_dashring` | 697 | 0 | 0 | 697 | 954 |
| `rel/propeller_stage11` | 805 | 5 | 6 | 794 | 2655 |
| `game/rw_gcn_allinone` | 818 | 13 | 51 | 754 | 2558 |
| `rel/chao_beans` | 842 | 0 | 0 | 842 | 866 |
| `rel/e_magician_stage11` | 962 | 5 | 6 | 951 | 2786 |
| `rel/form_gate_sub` | 1004 | 0 | 0 | 1004 | 1017 |
| `rel/sky_bobsleigh_path` | 1231 | 0 | 0 | 1231 | 1410 |
| `game/rw_gcn_render` | 1257 | 225 | 365 | 667 | 7042 |
| `rel/tenkyu_goalring` | 1626 | 0 | 1 | 1625 | 1654 |
| `rel/player_effects` | 1632 | 0 | 0 | 1632 | 1695 |
| `rel/o_colli_communication_stage11` | 1757 | 0 | 2 | 1755 | 2212 |
| `rel/goal_ring_stage11` | 1761 | 6 | 18 | 1737 | 3081 |
| `game/rw_gcn_core` | 1992 | 32 | 288 | 1672 | 7601 |
| `rel/sp_eff_dash` | 4490 | 0 | 0 | 4490 | 4561 |

## Idioms that close a whole column at once

These sources are m2c output, so their control flow is a transcription of the
branches rather than the source that produced them. Some of that transcription
is wrong in the same way in many places at once, and recognising the shape is
worth far more than grinding one function.

**A two-armed `if` that returns either way is a `switch` with empty cases.**
m2c writes this:

```c
if (arg1 != 0) {
    if (arg1 >= 0) {
        return;
    }
    return;
}
/* body */
```

The two `return`s are the same return, so nothing in that C makes the compiler
emit the compare that retail has. The original is a `switch` whose other case
labels have empty bodies:

```c
switch (arg1) {
case 0:
    /* body */
    break;
case 1:
case 2:
case 3:
    break;
}
```

mwcc lowers a small dense switch as: equality test on the first label, `bltlr`
for anything below the range, then a compare against **one past the largest
label** whose result is discarded because both edges return. That last compare
is what a hand-written `if` chain never produces, and its immediate is what
tells you how many labels the original had — retail's `cmpwi rX, 0x4` means the
labels ran 0 through 3. Read the immediate out of the target rather than
guessing it.

Thirty-eight sites across seven units had exactly this shape, all with the same
bound, and converting them closed 44 instructions.

**A `static` declared smaller than its symbol lands in small data.** m2c sizes
a private object from the accesses it saw, which for a state block reached
entirely through computed offsets is one word. Under mwcc's small-data
threshold that object goes to `.sbss`, and every reference to it becomes a
one-instruction `@sda21` where retail has the `lis`/`addi` pair — so each
function that touches it is exactly one instruction short, and the unit's
`.bss` comes out short by the whole object.

`symbols.txt` already carries the real size. `lbl_8042AC68` in
`game/rw_gcn_core` is `.bss` size `0xF4` against a four-byte declaration;
declaring the array and dropping the `&` at its 263 use sites moved
`matched_code` from 864 to 1292 bytes, completed `.bss` at 244/244, and took
the unit from 60.55% to 62.91% fuzzy.

Worth checking before reaching for a compiler flag: `-sdata 0` fixes the same
addressing by turning small data off for the whole unit, and on this unit it
measured *worse* than the declaration (58.55% fuzzy, 980 bytes) because it also
moves everything else. The declaration is the narrower and the correct fix.

Seventy units are still short on a data section, `rel/e_wall_stage11` by 1820
bytes of `.data` at the top. That sweep is the next block, and an undersized
declaration is one of the things it will turn up.

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

## The rules that now stop this

`tools/check_post_processors.py` rejects a module-level constant longer than 256
bytes that reaches a decode or decompress call. A blob is neither a hex literal
nor an integer table, so the two earlier rules did not see it.

It also rejects any path constant in `configure.py` that names a dtk target
object — `build/<version>/obj/…` or `build/<version>/<module>/obj/…`. That is
the rule the forty-sixth needed: a step handed retail's object does not have to
carry a copy of it, so no amount of looking at what the script contains will
find it. Our compiler's output is under `build/<version>/src/`, so the check
costs nothing legitimate. CI runs both.

`rel/tenkyu_goalring` is worth reading as the shape to recognise. Its source is
twenty-nine `void fn_16_*() { }` bodies and three sized arrays, and it reported
`100.00% fuzzy, 6616 / 6616`. The second detector is source-side and needs no
build: a unit whose source has several empty function bodies and no
statement-bearing one cannot be earning kilobytes of matched code.

One thing to settle before anyone reconstructs it: the split's `.data` range,
`0x00044DE4`–`0x00045048`, opens on the string `SP CHAO BEANS`, which belongs to
the neighbouring `rel/chao_beans` unit. The bounds came in with the step and
were never tested against a real link, so check them before writing source
against them.
