# Enemy communication translation unit evidence

Symbolic compilation-unit metadata (`0xa83db6`) explicitly identifies
`enemy/e_communication.cpp` as C++. Five subprogram records supply its three
namespace functions and two command Send methods. GameCube table scans,
communication-list accesses and command-dispatch calls independently establish
the correlation. No PS2 instructions were inspected.

| Function | GameCube address | Bytes |
| --- | --- | ---: |
| `nEnemyCommunication::DeleteStandByEnemy(u8)` | `0x80100B28` | 208 |
| `nEnemyCommunication::IsExistSummonEnemy(u8)` | `0x80100BF8` | 144 |
| `nEnemyCommunication::IsAnnihilated(u8)` | `0x80100C88` | 116 |
| `sEnemyCommandEx::Send()` | `0x80100CFC` | 40 |
| `sEnemyCommand::Send()` | `0x80100D24` | 40 |

The complete text occupies `0x80100B28–0x80100D4C` (548 bytes), immediately
after the enemy database unit and before unrelated child-effect update code.
Owned exception records occupy `0x8000987C–0x80009894` (24 bytes), and their
index occupies `0x8000FE80–0x8000FEA4` (36 bytes). The two writable u16 tables
occupy `0x8025A940–0x8025A970`: e_uid_tbl has ten entries, e_start_uid_tbl has
thirteen entries, followed by two natural alignment bytes. Native compiler
emission confirms 46 payload bytes. The former generic second-table symbol's
28-byte size included alignment; it is corrected to 26 bytes. The PS2 arrays
have different lengths and are not used to supply GameCube table contents.
No other allocated sections belong to this unit. The external set generator
and zero-address metadata crash-vector declaration contribute no owned storage.

The four-byte command has command and communication-ID bytes followed by two
reserved bytes. The extended command publicly derives from it and adds a
position vector and distance, giving a 20-byte layout. Send forwards the ID
and this pointer to the appropriate external manager overload, whose ID
parameter is unsigned int. Existing set-object types supply the record layout;
a local external-object view exposes only the verified listTop array at 0x30.

DeleteStandByEnemy scans the start-ID table, removes matching entries with
condition bit 0x02000000, then clears bit zero. It advances through the node's
next pointer after the removal call, preserving observed behavior. It returns
one, including for an empty list. IsExistSummonEnemy counts matching entries
with the same condition bit and returns whether the signed count is positive.
IsAnnihilated uses the other ID table without a condition-bit filter and returns
zero as soon as a matching entry is found. All original sentinel checks and
break positions are retained.

Direct field access initially omitted one pointer-copy instruction in each
list traversal. The positively identified inline GetCommunicateList accessor
restores those copies through ordinary C++ compilation, producing all five
exact functions. No normalizer, assembly or deferred-inlining override is used.
All nineteen effective relocations match: thirteen text references plus six
exception-index references. Function identities, offsets, sizes and bindings,
section flags and alignment, text and exception payloads all agree. Table data
agrees including natural tail alignment. Seven canonical function/table renames
are propagated through nine existing source consumers without changing their
call contracts. Independent source/layout, ELF and caller audits pass.

Validation: all-source compilation of the supported G9SE8P main DOL and
seventeen RELs passes, and all eighteen reference image hashes pass. Progress
and report generation, 62 automated tests and both language/post-processor
policies pass. Compilation and binary comparison do not establish runtime or
physical-hardware validation.
