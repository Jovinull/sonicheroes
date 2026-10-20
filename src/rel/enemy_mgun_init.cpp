#include "types.h"

// ENEMY_MGUN::Init (the PS2 build's name): the out-of-line copy of the one in
// rel/enemy_mgun.inc, which SetEnemyMGun inlines; nothing calls this copy
// (force_active).

#define ENEMY_MGUN_INIT_INLINE
#include "src/rel/enemy_mgun.inc"
