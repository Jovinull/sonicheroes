# advertiseD REL — completed decompilation

`advertiseD` is the C++ attract-mode, title, file-select, and menu overlay
(REL module 1). The overlay is fully matched:

- 434/434 source functions match in objdiff.
- All 21 source objects, including the two data-only objects, are `Matching`.
- No assembly implementations are used.
- The linked REL is byte-identical to retail:
  `0b28051533603c5f330b1af7e1959be8e73856ea`.
- The linked DOL remains byte-identical:
  `9214426b8a3fb1d6fe3dcff09bcc1a959e1e04a8`.
- Final REL section sizes are `.text 0x1532C`, `.ctors 0x4`,
  `.dtors 0x4`, `.rodata 0x1D08`, `.data 0x8593`, and `.bss 0x84C`.

The September 2003 symboled prototype was used only as a reference for names,
class layouts, and behavior. The retail GameCube objects and linked REL remained
the sole byte-matching authority. No reference binaries or extracted game data
are committed.

## Source layout and compiler configuration

The implementation lives in `src/advertiseD/*.cpp`. The split and symbol maps
are in `config/G9SE8P/advertiseD/`, and `configure.py` records the per-object
compiler settings.

The overlay uses CodeWarrior GC/1.3.2, C++, and disabled SDA
(`-sdata 0 -sdata2 0`). Per-object flags are intentional and must not be
normalized: some objects require `-pool off`, while several require
`-inline noauto` or scoped optimization pragmas.

Four original input objects use four-byte `.data` alignment where the default
compiler output advertises eight-byte alignment. The
`data_section_alignment` object option invokes
`tools/set_elf_section_alignment.py` to correct both ELF `sh_addralign` and
CodeWarrior's authoritative section-symbol alignment entry in `.comment`.
The postprocessor changes no section contents or offsets; it lets MWLD reproduce
the retail input-section boundaries and therefore the exact linked `.data`
layout.

## Matching-sensitive source patterns

The final matches relied on ordinary C++ source shapes that steer CodeWarrior's
optimizer and register allocator:

- Struct-array indexing, pointer cursors, and addend regrouping reproduced the
  original induction variables and address-expression order.
- Scoped `opt_strength_reduction`, `opt_common_subs`, peephole, and optimization
  pragmas handled the few functions compiled with locally different behavior.
- Directly nesting `fn_8012ECA8` lookups in `fn_1_1F70` arguments restored
  CodeWarrior's right-to-left argument evaluation and solved the final
  `adv_title` register-color rotations.
- Splitting the `adv_player` row index from its loop counter produced the
  original row-pointer, destination-pointer, and counter update order in
  `fn_1_65BC`.
- Exact definition order, including the separate `adv_story_tail.cpp` object,
  preserved function placement and out-of-line call decisions.
- Scoped `#pragma force_active` retained otherwise unreferenced original
  constants. Correct symbol scope allowed compiler-generated duplicate constants
  to be discarded at the same points as retail.
- Jump-table ownership follows the actual indexed range. In particular,
  `adv_title` owns the complete 13-entry table ending at `.data:0x9A4`, where
  `adv_fileselect` begins.

These are source-level solutions; the overlay contains no hand-written assembly.

## Verification

Run a fresh configure and build, then verify the hashes:

```sh
python configure.py --version G9SE8P
ninja
sha1sum build/G9SE8P/advertiseD/advertiseD.rel build/G9SE8P/main.dol
```

Generate the detailed object report with:

```sh
build/tools/objdiff-cli report generate -p . -o build/G9SE8P/report.json
```

The completed gate requires every source object and owned section to report
100%, the REL and DOL hashes above, exact REL section sizes, and a clean
`git diff --check`.
