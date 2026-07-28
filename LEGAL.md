# Legal

This is not legal advice and does not claim that decompilation is risk-free.
It is the operational policy used to keep copyrighted artifacts and leaked
material out of this repository. Contributors who need a legal conclusion
must obtain advice for their jurisdiction.

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
2. No GameCube or PS2 disc images, ROMs, executables, complete symbol dumps or
   download links. Not in the repository, issues or project chat. This also
   excludes links to prototypes, extracted executables and proprietary SDK
   archives. Public analysis tools and public documentation may be linked.
   Anyone asking where to get the game gets told to use their own legally
   obtained copy.
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
   source, nothing from any breach. A third-party header needs a verified public
   license, a pinned source and attribution; being downloadable does not make a
   proprietary SDK acceptable.
5. No compiler binaries in the repository. Contributors are responsible for
   using toolchains they are entitled to use.
6. No money. No donations, no Patreon, no ads, no paid builds, no sponsorships.
7. No official looking branding. No SEGA logos, no store pages, nothing that
   could be mistaken for a product.
8. This repository is not a port. If porting work ever happens it goes in a
   separate repository.

## Cross-platform symbols

A maintainer may inspect a corresponding build locally when they are legally
entitled to possess it. The repository records only the minimum symbolic fact
needed for a review: a name, source marker, class/type fact, the independent
GameCube correlation and the conclusion.

Do not publish the analyzed executable, tool dumps, complete symbol lists,
addresses without a necessary review purpose, extracted code, assembly or
pseudocode. Cross-platform metadata is a lead; the GameCube binary and objdiff
remain authoritative. See
[`docs/language-policy.md`](docs/language-policy.md#optional-ps2-symbol-workflow)
for the approved procedure.

## If SEGA gets in touch

Decided ahead of time, because deciding under pressure goes badly.

Do not argue in public and do not turn it into a spectacle. Comply with the
takedown right away and keep a private copy of the correspondence.

Do not file a DMCA counter notice on impulse. A counter notice is a sworn
statement and it includes agreeing to a court's jurisdiction. Only consider one
after talking to a lawyer, and only if the notice is clearly baseless.

Tell contributors what happened.

## Risk

No repository policy eliminates legal risk or guarantees how a rightsholder
will respond. A host may receive a takedown request, and other outcomes depend
on the facts and jurisdiction.

Distributing assets, playable builds, original code, leaked material or paid
access creates avoidable exposure. The rules above keep those materials out of
the project; they are risk controls, not a legal guarantee.

Keep offline backups. A takedown should cost you a host, not the work.
