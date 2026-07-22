# Contributing

You do not need previous decompilation experience. You need patience and a
willingness to read PowerPC assembly. Most people start on one small function
and pick up the rest as they go.

Read [LEGAL.md](LEGAL.md) first. Those rules are not negotiable.

## Setup

Follow the dependencies and building sections in [README.md](README.md). You
need a working `ninja` build and objdiff before anything else is useful.

## How the work goes

Say what you are taking before you start, in `#decomp` on
[Discord](https://discord.gg/VGCHZMXUWN), so two people do not spend a weekend
on the same function. There is no formal claim system and there does not need to
be one at this size.

Pick from what is already carved. Every file under `src/` has a header comment
listing the functions still written as assembly, and each one names the
translation unit it covers and where its boundary came from. Anything marked
`NonMatching` in `configure.py` has work left in it.

Then open it in objdiff. Your compiled output is on one side, the original is on
the other. The job is to make them identical.

Write C that produces that assembly. Not C that behaves the same way, but C that
the 2003 CodeWarrior compiler turns into those exact instructions. Save, look at
the diff, adjust, repeat. Green means matching.

Open a pull request once the function matches. If it does not match yet, say so
and explain what is left.

## Conventions

Assembly goes inline, in a `.c` file, as an `asm` block. There are no `.s` files
in this repository and the pre-commit hook refuses them, because a `.s` in the
tree is far more likely to be disassembly copied out of `build/` than something
a person wrote, and a hook cannot tell those apart. Reach for it only where C
genuinely cannot express the instruction, such as a special purpose register or
a cache operation. If a function is asm because C failed to reproduce it rather
than because assembly was the right answer, say so in a comment above it.

Aim for a perfect match, not something close. A non matching function is fine as
a temporary step, but the pull request has to say that clearly.

Do not reorder struct fields, change types or tidy up logic in a way that
misrepresents the original code. If the original code is ugly, the decompiled
code stays ugly. Fidelity comes before taste.

Name things from evidence: strings in the binary, assert messages and SDK symbol
names. If a name is a guess, add a comment saying it is a guess.

For unknown struct fields keep the offsets explicit, for example
`u8 unk_0x14[0x4];`.

Shared types and prototypes belong in `include/`, not repeated per file.
`include/types.h` has the primitives, `BOOL`, `TRUE`, `FALSE` and `NULL`;
`include/dolphin/os.h` has `OSContext`, the handler typedefs and the OS calls
more than one unit needs; `include/dolphin/ppc.h` has every special purpose
register number. Anything genuinely private to one translation unit stays in
that file. This is not tidiness: `OSContext` once had three different shapes in
three files and nothing in the build noticed.

Run `clang-format -i` over anything you touch under `src/` and `include/`
before committing. The pre-commit hook checks it and will refuse the commit
otherwise. Assembly blocks sit between `// clang-format off` and
`// clang-format on` markers, which wrap the whole function including its
signature, because the assembler's column layout is meaningful. Leave those
markers where they are.

## Commits

Conventional Commits, in English, subject line only. Keep them short.

```
feat: match OSGetTime
fix: correct stage01D split bounds
chore: update dtk to 1.8.4
```

## Tools

* [objdiff](https://github.com/encounter/objdiff) for diffing
* [decomp.me](https://decomp.me) to share a function you are stuck on
* [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) to brute
  force small variations until something matches
* `tools/decompctx.py` flattens a source file and its headers into one file, for
  pasting into decomp.me
* [Ghidra](https://ghidra-sre.org/) to understand a function before matching it.
  Ghidra output is for reading, never for pasting.

## Pull requests

One logical unit per pull request. A function, a file, a struct. Not fifty
unrelated functions.

The build has to pass. CI checks the SHA-1 of the built artifacts.

Review is about correctness and matching, not personal style preferences.

Every function has to be verified in objdiff before it goes in. Progress numbers
are only worth something if they can be trusted.

## AI assistance

Using an LLM to help write a function is fine, and this project does it. Say so
in the pull request and verify the result byte for byte like anything else.

What is not fine is bulk output nobody checked. That is the thing that makes
progress numbers meaningless, not the tool used to produce the code.
