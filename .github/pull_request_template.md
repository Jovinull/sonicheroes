## What

Describe the one logical unit changed by this pull request.

## Evidence

- [ ] I identified the source language and linkage from evidence, not from the
      current file extension or a byte match alone.
- [ ] I recorded whether names/types came from GameCube, PS2, PC or a known
      library reference, and marked guesses as guesses.
- [ ] If I used PS2 metadata, I kept the executable and tool output local and
      included only the minimum symbolic fact and independent GameCube
      correlation.
- [ ] If I changed inline flags, I documented the source/emission order and
      compared each candidate in objdiff.
- [ ] I did not add game binaries, assets, extracted assembly, leaked source or
      links to those materials.

Evidence and references:

<!-- Give symbol names, strings, vtable relationships, public references or
     compiler experiments. Do not attach proprietary artifacts. -->

## Verification

<!-- Full artifact CI for a fork runs only after a maintainer reviews the
     commits and tests them from a repository-owned integration branch. -->

- [ ] `python tools/check_language_policy.py`
- [ ] `python -m unittest tools.test_check_language_policy`
- [ ] `clang-format -i` on changed files under `src/` and `include/`
- [ ] objdiff result recorded below
- [ ] `ninja` passes and the artifact SHA-1 checks remain valid

Objdiff before/after:
