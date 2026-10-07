# Complete enemy icon-manager translation unit evidence

Positive C++ symbolic metadata identifies enemy/e_iconman.cpp, TEnemyIconMan,
fifteen methods and its class storage. Fourteen methods survive in GameCube;
the constructor is inlined into Create. No PS2 instructions were inspected.

Three adjacent GameCube-only TMissionFailure methods are included in the same
unit. Both manager On overloads inline its singleton creation path and share
its class string, vtable and singleton. This supports whole-unit ownership,
but the association is inferred from GameCube rather than asserted as a
cross-platform source marker. Exec and destructor names follow vtable slots;
the singleton creator retains its address-based name because its original
name is unknown.

| Function | GameCube address | Bytes |
| --- | --- | ---: |
| TMissionFailure::Exec (vtable-backed name) | 0x8010ADA4 | 288 |
| TMissionFailure::~TMissionFailure | 0x8010AEC4 | 116 |
| fn_8010AF38 (provisional mission-failure singleton creator) | 0x8010AF38 | 120 |
| IsOn | 0x8010AFB0 | 52 |
| Close | 0x8010AFE4 | 20 |
| Change | 0x8010AFF8 | 124 |
| Off | 0x8010B074 | 56 |
| On(float,float,int) | 0x8010B0AC | 348 |
| On(float,float) | 0x8010B208 | 328 |
| SetPos | 0x8010B350 | 84 |
| Disp | 0x8010B3A4 | 212 |
| Exec | 0x8010B478 | 56 |
| ~TEnemyIconMan | 0x8010B4B0 | 156 |
| CreateIconInstance | 0x8010B54C | 444 |
| Create | 0x8010B708 | 148 |
| Finalize | 0x8010B79C | 84 |
| Initialize | 0x8010B7F0 | 92 |

The complete text occupies 0x8010ADA4–0x8010B84C (2,728 bytes). The preceding
function initializes unrelated ring data; the following function creates
thunder-damage collision objects with separate vtables and private data.
Owned exception records occupy 0x8000A104–0x8000A298 (404 bytes), with fourteen
index rows at 0x800103E4–0x8001048C (168 bytes). Data at
0x8025AEB8–0x8025AF68 (176 bytes) contains both class strings and vtables,
the eleven-entry compiler switch table and resource filename. Two class-name
pointers occupy 0x8042B7A8–0x8042B7B0. The mission singleton at 0x8042C5B8
is four bytes followed by four bytes of linker alignment; the zero float at
0x8042E810 likewise has four trailing alignment bytes. Neither padding range
is modeled as an extra source object.

TEnemyIconMan is 0x30 bytes, with its icon pointer at 0x28 and enum at 0x2C.
The GameCube icon switch has eleven values, compared with ten in older
metadata; the extra value remains provisional. Concrete icon construction
uses real new expressions and their exception cleanup. GameCube's HP icon
allocates 0x98 bytes and passes an integer to its constructor, unlike the
older 0x94-byte, no-argument metadata version; that added contract is inferred
from GameCube. External icon implementations remain outside this unit. Their
nine virtual slots are independently verified against metadata and GameCube, including
signed-integer FrustumTest and both On overloads. Database Add/Delete contracts
agree with the independently reconstructed database unit.

Independent source review checks the mission state machine, its voice-idle
condition and six input clears; the HP icon's strictly positive gate; the
ungated GameCube-only variant; and mission creation only for the Search icon
in the two observed mission modes. SetPos preserves the optional offset and
flag update, while rendering requires FrustumTest to return exactly one.
Thirteen existing source consumers and three existing symbol fixers receive
only canonical same-address renames and formatting. Verified whole-unit
relocations total 177, including both vtables and the compiler switch table.

The mission constructor installs the singleton itself, so allocation failure
leaves the singleton unchanged. Its voice-idle conjunction is materialized in a local signed integer before branching, matching the
observed GameCube evaluation and established consumers of the same predicate.
SetPos uses the metadata-backed inline icon member to retain its receiver across
vector assignments. Disp returns for its two excluded action modes and tests a
local signed-integer display predicate before rendering. These source forms
reproduce the observed bodies without changing their behavior or instructions.

Ordinary automatic inlining reproduces every corrected function body but emits
the mission vtable after the icon-manager vtable, rather than before the switch
table and resource string. Reversing header class declarations or placing the
class definitions adjacent to their method groups does not change that result.
Whole-unit auto,deferred with reversed ordinary method definitions reproduces
the observed function and exception order together with the interleaved mission
vtable, switch table, resource string and manager vtable. The independently
verified trial matches all seventeen bodies, owned sections and 177 relocations.
This is a compiler-emission reconstruction supported by the complete object
layout, not proof of historical compiler flags or source line order. No object
normalizer, address-taking anchor or instruction adjustment is introduced.
The ordinary redundant TObject delete and its exception records are accounted
separately for normal linker resolution.

The configured production object independently passes all seventeen bodies,
owned sections and 177 effective relocations. The complete supported G9SE8P
matrix passes: main DOL and all seventeen REL hashes are identical. All 62
automated tests, language policy and 54 existing post-processor checks pass.
Independent final-link review verifies every function and named storage address,
all fourteen exception-index records and their cleanup targets. The linker
selects the existing strong Task delete and discards this unit's weak duplicate
and associated exception records. Linked constant-section flags match the
baseline convention. Runtime and physical-hardware validation were not performed.
