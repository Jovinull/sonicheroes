# Enemy voice controller unit evidence

The reconstructed GameCube unit contains two queue-entry helpers and the update,
destruction and creation routines for three controllers. Its eleven surviving
bodies occupy `0x80139738–0x80139FC4` (2,188 bytes). The three native constructor
expressions inline into their factories; no extra bodies survive. Existing
address-based function names remain provisional.

The GameCube runtime strings identify `TEnemyVoiceCtrl`, `TEnemyVoiceCtrlEx`
and `TEnemySELimit`. Their constructor stores and three vtables establish the
class groups independently of the reconstructed source names. The old source
swapped the latter two native type names; this correction preserves the string
contents, field behavior, layout and generated instructions.

## Boundary evidence and limits

This is a GameCube-inferred controller-family boundary. Neither the filename
`enemy_voice.cpp` nor its historical source order is established by retained
PS2 metadata: the inspected symbolic records contain no corresponding file or
class names. The original translation-unit boundary remains a hypothesis,
as required by the language policy. The claim here is complete native matching
of the project's reconstructed unit and its identified owned storage, not
recovery of the original file or compiler flags.

The code cluster contains all three vtable-referenced update/destruction pairs
and their creation routines. The following configured camera-slot update unit
begins at `0x80139FC4`; there is no instruction gap or overlap. The data cluster
contains the three class strings and three vtables. Cross-object relocation
inspection finds that the three class-name pointer objects are referenced only
by this unit's constructors. They belong with this unit, although the previous
split omitted them.

| Owned section | Address range | Bytes |
| --- | --- | ---: |
| Code | `0x80139738–0x80139FC4` | 2,188 |
| Exception records | `0x8000B9CC–0x8000BA80` | 180 |
| Exception index | `0x80011A34–0x80011AA0` | 108 |
| Class strings and vtables | `0x8028CFB0–0x8028D068` | 184 |
| Class-name pointers | `0x8042BCB0–0x8042BCBC` | 12 |

The pointer values bind, in order, to `TEnemyVoiceCtrl`, `TEnemyVoiceCtrlEx`
and `TEnemySELimit`. The final pointer is four bytes, correcting the old
provisional eight-byte symbol size. The four zero bytes before the next
small-data object at `0x8042BCC0` remain alignment padding, not an invented
fourth variable. No zero-initialized storage is newly claimed.

## Native generation

Reversing the eleven ordinary definitions and enabling per-unit
`-inline auto,deferred` gives the required code order directly from CodeWarrior.
The function bodies are unchanged. The former object postprocessor that moved
two entry helpers to the front is removed, including its build rule and stamp
dependency. No replacement object editing is required.

Independent raw-object comparison verifies all eleven bodies, all five allocated
sections and all 113 effective relocations. Relocations are compared by source
section, offset and type, and by the destination section/offset or external
symbol; anonymous exception labels are resolved by location rather than spelling.
The newly owned small-data pointers add three relocations and bind three former
external references within this object.

## Integration verification

Both the all-source target and the complete G9SE8P release matrix pass. A fresh
main ELF/DOL link and all seventeen REL outputs match the eighteen expected
artifact hashes. All 204 automated tests, language policy, 64 postprocessor
checks, source formatting and whitespace checks pass.

An independent final-ELF comparison against the original DOL verifies all five
owned ranges (2,672 bytes total), eleven global function addresses and sizes,
all 113 resolved relocation sites, the three four-byte pointer symbols and the
four adjacent zero padding bytes. This is linked native-source verification,
not a check of an original-object fallback. Compilation and byte comparison do
not establish runtime or hardware testing.
