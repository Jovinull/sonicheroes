#include "types.h"

// TObjEnemyPawn::CheckDirectionOfPlayerRangeIn (the PS2 build's name, by its
// member order): the out-of-line copy of the direction check EnemyMD_MgunReady
// inlines (rel/pawn_check_direction.inc, which this unit includes with
// PAWN_CHECK_DIRECTION_INLINE empty).

#define PAWN_CHECK_DIRECTION_INLINE
#include "src/rel/pawn_check_direction.inc"
