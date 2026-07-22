# Legal

This is not legal advice. It is how this project operates, based on how the
long running decompilation projects have worked for years without trouble.

Sonic Heroes and all related trademarks are property of SEGA. This project is
not affiliated with or endorsed by SEGA. It is a non-commercial study and
preservation project.

## What this is

Hand written C and C++ source that, compiled with the original CodeWarrior
toolchain, produces a binary identical to the retail `main.dol`. A build is only
useful to somebody who already owns the game.

## Rules

A pull request that breaks any of these is rejected.

1. No game assets. No models, textures, audio, level data or text taken from the
   disc.
2. No disc images, no ROMs, no download links. Not in the repository, not in
   issues, not in Discord. Anyone asking where to get the game gets told to dump
   their own copy.
3. No original binary code, and no extracted assembly committed. Assembly dumped
   out of the disc lives in `build/`, which is ignored by git. A pre-commit hook
   in `.githooks` refuses any commit that stages game data or build output, so
   this does not rely on anyone remembering. Enable it with
   `git config core.hooksPath .githooks`.

   The line is between assembly a person wrote and assembly a disassembler
   produced, not between file extensions. Hand written assembly is source and is
   allowed, inline in a `.c` file or as a standalone `.s`. Much of the SDK is
   assembly in its own original source, because special purpose registers and
   cache instructions have no C form; writing those as C would be wrong, not
   better.

   What is refused is a dump out of `build/`. It is recognisable because a
   disassembler leaves the original address and the original bytes on every
   line, like `/* 00001348 0000137C  7C 08 02 A6 */ mflr r0`, and the hook looks
   for exactly that. Some decompilation projects do commit those files; this one
   does not, because they are the game's own code in another notation.

   Where a function is asm only because C failed to reproduce it, say so in a
   comment above it, so it can be revisited rather than quietly kept.
4. No leaked material. No leaked SEGA or Sonic Team source, no leaked SDK
   source, nothing from any breach.
5. No compiler binaries in the repository. The CodeWarrior compilers are
   downloaded at build time.
6. No money. No donations, no Patreon, no ads, no paid builds, no sponsorships.
   SEGA has said publicly that it tolerates fan work as long as no profit is
   involved.
7. No official looking branding. No SEGA logos, no store pages, nothing that
   could be mistaken for a product.
8. This repository is not a port. If porting work ever happens it goes in a
   separate repository.

## If SEGA gets in touch

Decided ahead of time, because deciding under pressure goes badly.

Do not argue in public and do not turn it into a spectacle. Comply with the
takedown right away and keep a private copy of the correspondence.

Do not file a DMCA counter notice on impulse. A counter notice is a sworn
statement and it includes agreeing to a court's jurisdiction. Only consider one
after talking to a lawyer, and only if the notice is clearly baseless.

Tell contributors what happened.

## Risk

The likely outcome if a rightsholder is unhappy is a DMCA takedown to GitHub.
The repository goes down and that is the end of it.

A damages lawsuit against a non-commercial decompilation with no assets and no
distributed build is rare enough that there is no well known example of one. The
cases that escalated involved distributing the game itself, distributing assets,
or selling something.

Risk goes up with distributing assets, distributing playable builds, using
leaked source, taking money, and being loud in public. The rules above exist to
keep all of that out of the project.

Keep offline backups. A takedown should cost you a host, not the work.
