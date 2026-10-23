#include "game/effect/eff_bomb.h"

// TObjFormGateSub::CheckLeaderPlayerInGate (the PS2 build's name): the first
// player touching the gate part that is a leader (or whose formation check
// passes) and is not in states 0x3B or 0x3C; -1 for none. Exec inlines it
// (rel/formgate_sub_class.inc); this is the out-of-line copy.

#define FORMGATE_SUB_CHECK_INLINE
#include "src/rel/formgate_sub_class.inc"
