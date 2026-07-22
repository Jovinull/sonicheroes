# Sonic Heroes

[![Build Status]][actions] [![Code Progress]][progress] [![Data Progress]][progress] [![Discord]][discord]

[Build Status]: https://github.com/Jovinull/sonicheroes/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/Jovinull/sonicheroes/actions/workflows/build.yml
[Code Progress]: https://decomp.dev/Jovinull/sonicheroes.svg?mode=shield&measure=code&label=Code
[Data Progress]: https://decomp.dev/Jovinull/sonicheroes.svg?mode=shield&measure=data&label=Data
[progress]: https://jovinull.github.io/sonicheroes/
[Discord]: https://img.shields.io/discord/1529475492200059032?label=chat&logo=discord&logoColor=white&color=7289da
[discord]: https://discord.gg/VGCHZMXUWN

A work in progress decompilation of Sonic Heroes for the Nintendo GameCube.

This is a non-commercial study and preservation project. It is not affiliated
with SEGA.

This repository contains no game code, no game assets and no extracted
assembly. Some functions are written as inline assembly in the source, which is
explained under Status. You need your own legally obtained copy of the game to
build it. The project does not produce a playable game and is not a port.

Supported version:

* `G9SE8P`, GameCube, North America (NTSC-U), revision 0

Planned later: `G9SP8P` (PAL) and `G9SJ8P` (NTSC-J).

## Status

`main.dol` rebuilds byte for byte identical to the original disc. Work is under
way on the Dolphin SDK libraries linked into it. The progress badges above are
live and move on every commit, so they are the number to trust rather than
anything written here.

The disc ships no `.map` file, so symbols and translation unit boundaries have
to be worked out by hand.

A good share of what is written so far is inline assembly rather than C, and
that is not a shortcut. Most of it is code that is assembly in the original
source too: there is no C for reading a special purpose register, invalidating a
cache line, or saving the register file on the way into an exception, so
`PPCArch.c`, `OSCache.c` and the EABI runtime helpers are asm in the Dolphin SDK
as well. Writing those as C would be wrong, not better. A small number are
transcriptions where C should have reproduced the original and did not; each one
says so in a comment above it, so they are easy to find and worth revisiting.
The generated assembly for everything not yet written stays in `build/`, which
git ignores.

18 REL modules ship alongside `main.dol`. 17 of them are configured, and none of
them reproduce yet: the original has a zero sized placeholder section that the
rebuild does not emit, which shifts every later section index. So
`config/G9SE8P/build.sha1` carries the hash of `main.dol` only, and that is all
CI verifies. `stage00D` is excluded for now, see the note at the end of
`config/G9SE8P/config.yml`.

## AI assistance

I use LLMs to help write this decompilation. Nothing goes in unverified: every
function has to match the original byte for byte in objdiff, and CI checks the
SHA-1 of the built DOL on every push. A function either reproduces the original
binary exactly or it does not get marked as matching.

## Dependencies

You need Python and ninja on your `PATH`.

### Windows

Use native tooling. WSL and msys2 are not needed, and objdiff cannot watch files
for automatic rebuilds under WSL.

* [Python](https://www.python.org/downloads/)
* [ninja](https://github.com/ninja-build/ninja/releases), or `pip install ninja`

### macOS

```sh
brew install ninja
```

### Linux

Install ninja from your package manager.

On macOS and Linux, [wibo](https://github.com/decompals/wibo) is downloaded
automatically to run the original Windows compilers.

## Building

Clone the repository:

```sh
git clone https://github.com/Jovinull/sonicheroes.git
```

Turn on the repository hooks once, so a commit that stages game data or build
output is refused before it happens:

```sh
git config core.hooksPath .githooks
```

Put your copy of the game in `orig/G9SE8P/`. Either drop the disc image there
(ISO, RVZ, GCM, WBFS, CISO, GCZ, NFS or TGC), or extract the disc with Dolphin
into that folder. If you use a disc image, it can be deleted after the first
build.

Then:

```sh
python configure.py
ninja
```

The checksum step verifies `main.dol` only, for the reason given under Status.

## Diffing

After the first build there will be an `objdiff.json` in the project root.

Get [objdiff](https://github.com/encounter/objdiff), open project settings and
point `Project directory` at this repository. It picks up the config on its own.
Pick an object in the sidebar to start diffing. It rebuilds automatically when
you edit source, headers, `configure.py`, `splits.txt` or `symbols.txt`.

![objdiff showing dolphin/base/PPCArch fully matching](docs/objdiff.webp)

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md).

## Legal

See [LEGAL.md](LEGAL.md).
