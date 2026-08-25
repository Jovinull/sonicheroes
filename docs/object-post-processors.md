# Object post-processors

Some translation units carry a `tools/fix_<unit>_object.py` step that edits the
compiled object before it is linked. This page says what those steps are for,
what they may and may not do, and what a new one has to ship with.

There are 38 of them today.

## What they are for

dtk builds the *target* object from `splits.txt` and `symbols.txt`. MWCC builds
ours from source. The two agree on instructions long before they agree on
everything else, because an object file carries a lot that no C statement
controls: the order of compiler-generated atoms, `.ctors` slot placement,
section alignment fields, ABI metadata in the comment section, common-BSS
inflation. When our reconstruction is right and the object still differs in one
of those, a post-processor is the honest way to say so.

That is the whole purpose. A post-processor describes a **known, measured gap
between our build and retail's**. It is a bookmark, not a conclusion.

## What they do today, measured

Diffing each unit's freshly compiled object against the same object after its
step runs puts every one of the 38 into one of three shapes. All three are
legitimate; knowing which one you are looking at is what keeps a review honest,
because two of them touch `.text` and that is not by itself a problem.

**Metadata and symbols.** The majority. Atom order, `.ctors` slots, section
alignment fields, ABI bytes in `.comment`, symbol names and scopes, string
sub-sections. `.text` untouched.

**Split-translation-unit slicing.** Several units are one source compiled more
than once. `src/game/action_cont1.cpp` is thirty-one bytes — `#include
"src/game/action.cpp"` — and so are `_cont2` through `_cont4`. All five objects
compile the same 77 KB source, and each step keeps the slice that belongs to its
object and drops the rest. That shows up as `.text` shrinking by around 19 KB,
which looks alarming in a diff and is only extraction. The same pattern covers
`game/movie.o`, `rel/o_invoke_colli.o` and others.

**Permutation of our own compiler's output.** `fix_wide_format_core_object.py`
is the one that does this: register fields renumbered, basic blocks reordered,
branch offsets recomputed from where the blocks landed. Nothing is copied in
from retail; the bytes all came from MWCC.

The fourth shape — writing bytes taken from the retail object — is the one that
is out, and today nothing in `tools/` does it. `fix_wide_format_core_object.py`
uses a retail literal in exactly one place, an assertion, which is the opposite
of carrying one.

**Telling slicing from injection.** Slicing only removes; the bytes that remain
are still at the offsets MWCC put them, or shifted whole. Injection introduces a
value the compiler never produced at that offset. In review, look at what the
script's tables hold: instruction indices, symbol names and section names are
descriptions of our own output, while a hex literal being written rather than
compared is retail content.

## The standard

`tools/fix_wide_format_core_object.py` set it, and it is worth quoting because
every new step is measured against it:

> Nothing here carries retail instruction content. Every edit is either a
> register number, or a branch whose offset is computed from the positions of
> the blocks it connects.
>
> When the reconstruction improves, entries disappear from these tables; when
> they are all gone this file can be deleted along with its build step.
>
> Current remainder: 4 block-layout edits and 186 register-field substitutions
> across 134 of the function's 1069 instructions.
>
> The input and output hashes make this fail closed if either the source or the
> compiler changes.

Four properties come out of that, and a new post-processor needs all four.

**1. No retail content.** The script may permute what our compiler produced — a
register number, an atom's position, a branch offset recomputed from the blocks
it connects. It may not contain bytes copied out of the retail object. A
hardcoded instruction word, or a hardcoded table of exception-table bytes, is
the answer written into the tool. Assertions are fine: comparing against a
literal to fail loudly is the opposite of carrying it.

**2. A published remainder.** Say in the docstring how large the gap is, in the
units a reader can check — how many instructions, how many fields, out of how
many. A step with no number attached cannot be seen to shrink.

**3. Fail closed.** Hash the input and the output text. If the source improves
or the compiler changes, the step must break rather than silently paper over
something new. Every edit should also assert the byte it expects before writing.

**4. A path out.** The file header of the unit says what was tried in source and
what is still unexplained, so the next person starts where this one stopped.

## Why the line is at instruction content

Artifact matching is not the goal. It is the *evidence* that the reconstruction
is right, and `build.sha1` is a test of the source. A step that injects retail
instruction bytes makes the gate test source-plus-patch instead, and a patch
that carries the answer can never fail in a way that teaches anything.

The cost is concrete. `fn_8005EA04` in `game/fn_8005E8EC.cpp` differed from
retail by six register fields, and patching those six fields would have closed
it. The actual cause was that retail's source wrote two conditions as one
short-circuit `&&`, which emits a `bne`/`b` pair where a single `if` folds to
one `beq`. Writing it that way made the function byte-exact from source, and the
rule generalises to every folded branch pair in the tree. Had the six fields
been patched first, the unit would have read `Matching` and nobody would have
gone looking.

`NonMatching` with the finding written down is worth more than `Matching` with
the answer hidden in a `.py`. The first is an open problem someone solves; the
second looks finished and never gets opened again.

## Before reaching for one

Two things that have each closed a wall recently, both cheaper than a patch:

- **A folded branch pair** (`bne .L_next; b .L_out` in retail, one `beq` here)
  usually means a short-circuit `&&` or `||` in the source. No pragma or
  compiler flag restores it — that has been swept exhaustively.
- **A `__dl__FPv` cleanup in `extab`** means the source used a real
  new-expression. The hand-written `alloc(); if (p) ctor(p, ...)` idiom emits
  identical instructions and no exception table, so the unit links short while
  every function reads 100%.

## Reviewing one

- Does it carry any retail byte it writes, rather than asserts?
- Does the docstring state the remainder as a count?
- Does it hash input and output?
- Does the unit's file header say what was tried in source?
- Does the build still produce `18 files OK`?
