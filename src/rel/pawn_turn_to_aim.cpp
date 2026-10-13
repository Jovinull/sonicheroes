#include "types.h"

// TObjEnemyPawn::TurnToAim (the PS2 build's name, by its member order): the
// out-of-line copy of the player search the seeking modes inline
// (rel/pawn_seek.inc, which this unit includes with PAWN_TURN_TO_AIM_INLINE
// empty).

#define PAWN_TURN_TO_AIM_INLINE
#include "src/rel/pawn_seek.inc"
