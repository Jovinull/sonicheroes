# Contributing

You do not need previous decompilation experience. You need patience and a
willingness to read PowerPC assembly. Most people start on one small function
and pick up the rest as they go.

Read [LEGAL.md](LEGAL.md) first. Those rules are not negotiable.

## Setup

Follow the dependencies and building sections in [README.md](README.md). You
need a working `ninja` build and objdiff before anything else is useful.

## How the work goes

Claim a function first, in the tracking issue for that file, so two people do not
spend a weekend on the same one.

Then open it in objdiff. Your compiled output is on one side, the original is on
the other. The job is to make them identical.

Write C that produces that assembly. Not C that behaves the same way, but C that
the 2003 CodeWarrior compiler turns into those exact instructions. Save, look at
the diff, adjust, repeat. Green means matching.

Open a pull request once the function matches. If it does not match yet, say so
and explain what is left.

## Conventions

Aim for a perfect match, not something close. A non matching function is fine as
a temporary step, but the pull request has to say that clearly.

Do not reorder struct fields, change types or tidy up logic in a way that
misrepresents the original code. If the original code is ugly, the decompiled
code stays ugly. Fidelity comes before taste.

Name things from evidence: strings in the binary, assert messages and SDK symbol
names. If a name is a guess, add a comment saying it is a guess.

For unknown struct fields keep the offsets explicit, for example
`u8 unk_0x14[0x4];`.

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
