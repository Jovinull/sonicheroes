#include "types.h"

// TObjEnemyPawn::ExecMachineGun (the PS2 build's name): the out-of-line copy of
// the gun update EnemyMD_MgunFire inlines (rel/pawn_machine_gun.inc, which this
// unit includes with PAWN_EXEC_MACHINE_GUN_INLINE empty).

#define PAWN_EXEC_MACHINE_GUN_INLINE
#include "src/rel/pawn_machine_gun.inc"
