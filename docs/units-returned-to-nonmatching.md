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
all, charged only the size delta. **previous** is the value this
table last carried, so a row that moved says which way.

**The table is now sorted by objdiff percentage, not by `left`.** That is the
measure the project reports and the one that decides whether a change helped.
`left` is kept beside it because it says what *kind* of gap remains, which the
percentage does not.

**`left` is a lower bound, not a score.** A function whose size does not match
is charged its size delta and nothing else, so its content is never counted.
Close that size gap and the column can *rise* even though the unit improved —
`rel/e_mask_stage11` went from 32 to 224 that way while its objdiff percentage
went up, because 197 instructions that were hidden behind a length mismatch are
now visible. Use this table to pick a target and to see the shape of a gap;
decide whether a change helped with `build/G9SE8P/report.json`.

| unit | objdiff | left | registers | other | length | size | previous |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| `game/cri/axrna` | 97.44 | 48 | 20 | 11 | 17 | 1541 | 48 |
| `rel/e_fan_stage11` | 95.90 | 47 | 14 | 18 | 15 | 518 | 47 |
| `rel/e_mask_stage11` | 94.36 | 145 | 16 | 111 | 18 | 1125 | 224 |
| `game/cri/svm` | 94.24 | 50 | 0 | 24 | 26 | 1115 | 50 |
| `rel/e_capture_collision_stage11` | 94.00 | 63 | 21 | 20 | 22 | 401 | 63 |
| `rel/o_s12_celestial_sphere` | 92.72 | 154 | 24 | 106 | 24 | 799 | 142 |
| `rel/e_s11_flag_stage11` | 91.27 | 53 | 4 | 9 | 40 | 1741 | 92 |
| `rel/e_strategy_flyer_stage11` | 90.17 | 271 | 51 | 82 | 138 | 4833 | 334 |
| `rel/e_grass_stage11` | 89.48 | 90 | 30 | 11 | 49 | 1385 | 89 |
| `rel/e_grass2_stage11` | 88.41 | 61 | 27 | 7 | 27 | 1092 | 61 |
| `rel/e_tree_stage11` | 87.75 | 49 | 13 | 0 | 36 | 935 | 32 |
| `rel/o_s11_door` | 87.54 | 119 | 35 | 49 | 35 | 1352 | 109 |
| `rel/e_turtle_stage11` | 86.83 | 364 | 49 | 3 | 312 | 5025 | 369 |
| `rel/e_spider_stage11` | 85.75 | 252 | 30 | 166 | 56 | 965 | 109 |
| `rel/e_capture` | 85.50 | 438 | 35 | 142 | 261 | 5335 | 358 |
| `rel/e_s11_key_stage11` | 84.48 | 218 | 13 | 142 | 63 | 1640 | 226 |
| `rel/e_rinoliner_stage11` | 84.09 | 77 | 13 | 0 | 64 | 1929 | 88 |
| `rel/e_wall_stage11` | 83.81 | 467 | 49 | 39 | 379 | 6670 | 464 |
| `game/rw_gcn_raster` | 82.07 | 480 | 162 | 291 | 27 | 3771 | 480 |
| `rel/e_strategy_magician_stage11` | 81.82 | 218 | 3 | 94 | 121 | 2199 | 150 |
| `rel/e_strategy_rinoliner_stage11` | 81.58 | 114 | 0 | 0 | 114 | 990 | 115 |
| `rel/e_flyer_stage11` | 80.22 | 595 | 38 | 8 | 549 | 4582 | 641 |
| `rel/e_rinoliner_collision_stage11` | 78.53 | 271 | 14 | 8 | 249 | 2574 | 276 |
| `rel/e_flyer_collision_stage11` | 77.97 | 240 | 21 | 39 | 180 | 1377 | 232 |
| `rel/e_flyer_path_stage11` | 77.83 | 155 | 0 | 0 | 155 | 2268 | 84 |
| `game/cri/rnares` | 69.38 | 55 | 0 | 0 | 55 | 251 | 55 |
| `game/rw_gcn_render` | 68.07 | 918 | 188 | 57 | 673 | 7042 | 1253 |
| `rel/object_effects_stage11` | 63.59 | 148 | 0 | 0 | 148 | 935 | 148 |
| `game/rw_gcn_core` | 62.91 | 1992 | 81 | 228 | 1683 | 7601 | 1992 |
| `rel/e_magician_stage11` | 59.49 | 943 | 16 | 6 | 921 | 2786 | 932 |
| `rel/propeller_stage11` | 53.50 | 804 | 4 | 6 | 794 | 2655 | 804 |
| `rel/particle_test` | 49.50 | 317 | 0 | 0 | 317 | 735 | 317 |
| `game/rw_gcn_allinone` | 49.32 | 811 | 13 | 55 | 743 | 2558 | 822 |
| `rel/light_collision_stage11` | 43.31 | 489 | 5 | 8 | 476 | 1168 | 487 |
| `rel/put_particle` | 41.58 | 420 | 0 | 0 | 420 | 808 | 420 |
| `rel/goal_ring_stage11` | 32.62 | 1780 | 7 | 27 | 1746 | 3081 | 1780 |
| `rel/spboss_throw_object` | 30.55 | 519 | 0 | 1 | 518 | 794 | 517 |
| `rel/sp_dashpanel` | 29.38 | 474 | 0 | 0 | 474 | 740 | 475 |
| `rel/sp_dashring` | 22.95 | 696 | 0 | 0 | 696 | 954 | 697 |
| `rel/o_colli_communication_stage11` | 15.34 | 1756 | 0 | 2 | 1754 | 2212 | 1756 |
| `rel/sky_bobsleigh_path` | 11.58 | 1231 | 0 | 0 | 1231 | 1410 | 1231 |
| `rel/player_effects` | 3.71 | 1632 | 0 | 0 | 1632 | 1695 | 1632 |
| `rel/chao_beans` | 2.77 | 842 | 0 | 0 | 842 | 866 | 842 |
| `rel/tenkyu_goalring` | 1.72 | 1625 | 0 | 0 | 1625 | 1654 | 1625 |
| `rel/sp_eff_dash` | 1.54 | 4490 | 0 | 0 | 4490 | 4561 | 4490 |
| `rel/form_gate_sub` | 1.22 | 1004 | 0 | 0 | 1004 | 1017 | 1004 |

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

**`(...)` in an m2c extern is "unknown", never "variadic".** m2c writes an
ellipsis whenever it could not infer a prototype. mwcc reads that as a genuine
variadic function and emits the PPC EABI marker `crclr cr1eq` before every call
to it, so each call site is one instruction longer than retail's.

Three of these have signatures already established by the hand-written units,
and correcting them across sixteen files moved fifteen units and 160 bytes of
matched code:

```c
void  __dt__7TObjectFv(void*, s32);          /* was (...) */
void  __dl__FPv(void*);                      /* was (...) */
void* __ct__7TObjectFP7TObject(void*, void*); /* was (...) */
```

**241 spurious `crclr` remain across eighteen units, and every one of those
targets contains zero.** No function these units call is variadic in retail, so
every remaining `(...)` extern is wrong. `rel/e_wall_stage11` leads with 39,
then `rel/e_strategy_magician_stage11` with 33 and `rel/e_flyer_path_stage11`
with 31. Count them with the instruction word `0x4CC63242`.

The tree itself supplies a good part of the answer. A symbol an m2c unit
declares as `(...)` is often declared properly in a hand-written unit, in
several spellings that are the same ABI — `void*`/`TObject*`/`C_COLLI*`,
`int`/`s32`/`M2C_UNK`. Collapsing each parameter position to its category
(pointer, float, integer) and requiring every spelling in the tree to agree on
it yields one prototype worth adopting; anything that disagrees is left alone.
That adopted 106 declarations, of which 100 held. It moved six units — up to
+2.38% on `rel/e_strategy_magician_stage11` — and took the spurious `crclr`
count from 241 to 228.

Six files had to be reverted at that step. Most of it was the *return* type:
m2c's `TObject*` is assigned to a `TObject*` in the file, and a canonicalised
`void*` does not convert back implicitly in C++. The return type never affects
whether mwcc emits `crclr` — only the ellipsis does — so adopting the parameter
list alone and keeping m2c's return recovers `rel/e_magician_stage11` (+1.86%)
and `rel/e_turtle_stage11` (+0.16%).

Four are still out, for two different reasons. `rel/o_colli_communication_stage11`
and `rel/e_rinoliner_stage11` do not compile even with the parameters alone.
`rel/e_flyer_path_stage11` (-0.17%) and `rel/e_wall_stage11` (-0.07%) compile
and measure *worse*, which means an adopted parameter is wrong for the call
sites in those files.

`rel/e_wall_stage11` is the case to study, because its 39 `crclr` come from
eight callees and **not one of them has a consistent call arity inside the
file**: `fn_80018A34` is called with two, three and four arguments;
`fn_8019E8EC` with none, one and two; `fn_8019ED68` with four, five and six.
m2c guessed a different shape at each site because it believed the function was
variadic. There is no rule that resolves that — each call site has to be read
against the target's register setup. Attribute them by scanning our `.text` for
`0x4CC63242` and taking the symbol of the next `bl`.

Beyond that, deriving the rest is not purely mechanical, and it is worth
knowing why before someone tries. Two obstacles came up:

- A mangled name carries its own signature — `Vibrate__15TEnemyParalysisFP7RwFrame15RwOpCombineType`
  is `(RwFrame*, RwOpCombineType)` plus `this` — but only 32 of the 322
  ellipsis externs are mangled. The other 290 are `fn_XXXX` and have to be
  typed from their call sites.
- m2c sometimes emits calls to the same symbol with **different argument
  counts**: `fn_8019E8EC` in `rel/e_wall_stage11` is called once with none and
  nineteen times with one. At least one of those is m2c guessing, and which one
  has to be settled against the target's register setup at the call site rather
  than by majority.

**A constant multiply that retail keeps in a register.** `fn_8022C300` in
`game/rw_gcn_render` is `li r3, 0x16` then `mullw r3, r3, r0`, where this build
folds it to one `mulli`. Same cause as the record flag fold — propagation sees
the literal — and the same fix, `-opt nopropagation` on the unit.

**A struct four bytes too narrow shifts every field after it.**
`rel/particle_test` stored to 0x2c and 0x34 where the target uses 0x30 and
0x38: its `motion` member is a two-word structure, not one pointer. The give-away
is that *both* offsets are wrong by the same amount, so the fix is one padding
member rather than two field edits.

**m2c names a dropped parameter for you.** When it decides a function takes
one argument but the target reads r4, it still calls that parameter `arg1` —
the number is the register position it came from, not the position in the list
it wrote. So a function whose *first* declared parameter is named `arg1` is
missing `arg0`:

```c
void fn_8_B9548(s32 arg1)      /* target: mr r3, r4; bl fn_8_90B10 */
{
	fn_8_90B10(arg1);
}
```

Sixty-seven functions across twenty files have that shape, and it is a one-line
grep: the first parameter's name. Prepending `void* arg0` moved nine units,
`game/rw_gcn_render` by +1.22. Three files have to be left out because a call
site inside the file then needs the argument too, and one measures worse.

**A `(...)` extern can hide a lost argument.** m2c cannot see an argument that
was already in the right register. `fn_8_C4B58` in `rel/e_tree_stage11` calls
`fn_8013F484` right after `mr r30, r3`, so r3 still holds the function's own
first parameter and m2c wrote `fn_8013F484()` — no arguments at all. Give the
extern its prototype and the compiler names the omission for you:

```
function call 'fn_8013F484()' does not match 'fn_8013F484(int)'
```

Three functions in that unit went byte-exact from this plus one wrong
parameter: `fn_8_C4BBC` read `arg1` while the target reads r4, meaning the
function takes two parameters and uses the second. 84.32% to 84.65%, and the
unit's remaining 32 are now all length.

Swept tree-wide, this is smaller than it looks. Of the 322 ellipsis externs,
only 14 sit in a file where the tree agrees on an arity *and* every call site
has fewer arguments than that — the shape where a dropped argument is the
explanation. Filling those from the enclosing function's own parameters, in
order, holds in two units and breaks in eight, which is the right ratio to
expect: the register the call reads is not always the enclosing function's
parameter, and where it is not, the fill has to come from the target. The two
that held are `rel/e_capture` (`fn_800A5A54`, `fn_8014FF2C`; +124 bytes of
matched code) and `rel/e_turtle_stage11` (`fn_80017800`; +124 bytes).

**An inline string literal is a named object in retail.** m2c writes the
literal at the use site, so mwcc emits an anonymous `@107`, and the register
function reads `lis r3, @107@ha` where retail reads
`lis r3, captureCollisionDisplayName@ha`. Declare the object with the name the
target gives it — objdiff pairs data by symbol name, so the literal has to
become a named `static const char[]` before either side can match.

**A constant that retail ORs, we add.** `captureCollisionRegister` sets a flag
word to `0x20000`, then `| 8` on one path and `& ~8` on the other. With
propagation on, mwcc knows bit 3 is clear and folds both: `addi r0, r5, 0x8`
for the first and nothing at all for the second, so the whole else-branch
disappears. `-opt nopropagation` on the unit restores `ori` and `rlwinm`, and
the function becomes structurally exact — every instruction in the right place,
differing only in whether the entry pointer lives in r5 or r6.

That register swap is the reason this unit's `left` **rose** from 51 to 63 while
its objdiff percentage went from 93.85% to 94.00%. Twenty-one register
differences are now visible in a function that previously had the wrong
instructions to compare. It is the same effect the column warning above
describes.

**The object record recipe does not generalise past the flag hoist.** The
literal-to-named-object half of it changes where the unit's strings live, and
that moves the whole data section. Applied to the seven units whose register
function tests an inline literal, it helped `rel/e_wall_stage11` (+0.09) and
`rel/e_mask_stage11` (+0.05) and *hurt* `rel/e_capture` (-0.07),
`rel/e_grass_stage11` (-0.11) and `rel/e_rinoliner_collision_stage11` (-0.11).
Measure each one; the name is right in every case, but the layout it implies is
not yet right in most.

**The object record is a recipe, and it repeats per unit.** Every stage object
has a `<name>ObjectRegister` that fills one record and ends with a flag test.
m2c gets the same three things wrong in each of them, so the second unit costs
a fraction of the first:

1. *Inline literals instead of named objects.* `"CAPTURE COLLISION"` at the use
   site becomes an anonymous `@107`; retail has `captureCollisionDisplayName`.
   objdiff pairs data by symbol name, so the literal has to become a named
   `static const char[]`.
2. *Folded flag arithmetic.* The record's flag word is `0x20000`, then `| 8` or
   `& ~8`. With propagation on, mwcc knows bit 3 is clear, turns the first into
   `addi` and deletes the second branch entirely. Hoist the constant into a
   local and put `-opt nopropagation` on the unit.
3. *A folded-away test.* m2c writes `if (0U != 0U)` when the tested pointer was
   a constant it could see; that removes the whole branch. Give the value a
   local and the test comes back. Its **type** decides the compare: retail's
   `cmplwi` is unsigned, so `u32`, not `s32`.

`rel/e_fan_stage11` also had two more lost arguments of the #478 kind:
`fn_8015BBF8` takes `(scene, mesh)` and m2c passed only the scene, and
`fn_80150958()` was called with nothing where the value was already in r3.
Both are named by the compiler once the extern loses its `(...)`.

That took the unit from 94.51% to 95.90% and `left` from 54 to 47, with
`fn_8_C37E8` and `s12fanObjectUnload` byte-exact. What is left in
`s12fanObjectRegister` is a single instruction: retail stores the byte field at
0x21 from the same register that holds the zero variable, and mwcc always
materialises a fresh `li r0, 0x0` for the byte store no matter how the field or
the variable is typed.

**`bool` is a byte in C++ and an int in retail.** A float comparison returned
as `s32` costs one extra instruction, because mwcc normalises the `bool` before
widening it:

```
  xori r3, r0, 0x1      |  xori   r0, r0, 0x1
                        |  clrlwi r3, r0, 24
```

`-bool off` makes `bool` an `int` and the mask disappears. Swept across the
open units it improves eleven and regresses none; two units, `rel/propeller_stage11`
and `rel/light_collision_stage11`, do not compile with it and keep their flags.
Unlike `-use_lmw_stmw` this one is safe to try everywhere, because a unit that
does not return a comparison is simply unaffected.

**`-opt nopropagation` is per-unit, not a sweep.** It is the right fix wherever
retail keeps a constant in a register that this build folds — the record flag
word, the `mullw` in `game/rw_gcn_render` — but applied to every unit that
lacked it, five improve and nine regress, `game/cri/axrna` by -4.69 and
`game/cri/rnares` by -1.32. The CRI units in particular want propagation on.
Read the folded instruction first, then add the flag to that unit.

So far two flags sweep cleanly and two do not:

| flag | improves | regresses | decidable without building? |
| --- | ---: | ---: | --- |
| `-pool off` | 19 | 2 | yes — anchor symbol `...bss.0` |
| `-bool off` | 11 | 0 | yes — a `clrlwi rX, rY, 24` on a returned comparison |
| `-opt nopropagation` | 5 | 9 | only from the folded instruction |
| `-use_lmw_stmw on` | 3 | 17 | no |

**`-use_lmw_stmw on` is not a general answer, unlike `-pool off`.** Swept
across all 43 open units it improves three — `rel/spboss_throw_object` (+1.05),
`rel/light_collision_stage11` (+0.07), `rel/e_wall_stage11` (+0.05) — and
regresses seventeen, `rel/e_grass2_stage11` by -2.21 and `game/rw_gcn_core` by
-2.08. Worth trying per unit, never worth adopting broadly. The contrast with
`-pool off` below is the useful part: pooling announces itself in our object
with an anchor symbol, so it can be decided from evidence, while multiple-word
moves have no such tell and only the report can settle them.

**Data pooling is on where retail had it off.** mwcc's `-pool` collects a
translation unit's static data behind one anchor and addresses every object as
`base + offset`; retail emits a `lis`/`addi` pair per symbol. Our object gives
itself away with a symbol named `...bss.0` or `...data.0`, and the register
function reads

```
  lis  r3, treeObjectDisplayName@ha    |  <missing>
  addi r0, r3, treeObjectDisplayName@l |  addi r0, r6, 0x48
```

Twenty units carry a pool anchor. `-pool off` improves nineteen of them, from
+0.55 to +5.27, and the two it does not are the CRI units `game/cri/svm`
(-6.02) and `game/cri/axrna` (-0.63), which really were pooled. Check for the
anchor symbol before assuming either way.

This is also the clearest case of the `left` column misleading: `rel/e_tree_stage11`
went 84.65% to 87.48% with every register and content difference gone, and its
`left` **rose** from 32 to 37 because only length gaps remain to be charged.

## Where to start

The six closest by objdiff percentage:

- `game/cri/axrna` 97.44% (48 left; 20 registers, 11 other, 17 length)
- `rel/e_fan_stage11` 95.90% (47; 14 registers, 18 other, 15 length)
- `rel/e_mask_stage11` 94.36% (145, now mostly content)
- `game/cri/svm` 94.24% (50; 24 other, 26 length)
- `rel/e_capture_collision_stage11` 94.00% (63; 21 registers, 20 other, 22 length)
- `rel/o_s12_celestial_sphere` 92.72% (154; 24 registers, 106 other, 24 length)

`game/cri/rnares` has three functions and no wrong instruction at all — every
one of its 55 is a length gap. It is also the clearest read of the `axrna`
wall below: `fn_80224D14` scans a 32-entry table and retail unrolls that scan
eight times behind `mtctr 4`, where this build keeps it rolled against an index
compare. Same shape, same library, same unresolved question — so a flag that
cracks one cracks both.

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
