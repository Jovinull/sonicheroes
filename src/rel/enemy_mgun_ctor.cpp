#include "types.h"

// ENEMY_MGUN's constructor (the PS2 build's ENEMY_MGUN::__ct): the
// out-of-line copy of the one in rel/enemy_mgun.inc, which SetEnemyMGun
// inlines; nothing calls this copy (force_active).

#define ENEMY_MGUN_CTOR_INLINE
#include "src/rel/enemy_mgun.inc"
