#include "types.h"

// TEnemyStrategy<TObjEnemyCapture>::Execute (the PS2 build's name), the
// template instance (rel/enemy_strategy_execute.inc) that the enemy's unit
// emitted. Explicit instantiation of the class emits only Execute (the inline
// members are unused; the pure ones only warn).

#include "src/rel/enemy_strategy.inc"
#include "src/rel/enemy_strategy_execute.inc"

class TObjEnemyCapture;

template class TEnemyStrategy<TObjEnemyCapture>;
