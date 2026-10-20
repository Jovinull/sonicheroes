#include "types.h"

// TEnemyStrategy<TObjEnemyPawn>::Execute (the PS2 build's name), the pawn
// strategy's template instance (rel/enemy_strategy_execute.inc), which the
// pawn's unit emitted. Explicit instantiation of the class emits only Execute
// (the inline members are unused; the pure ones only warn).

#include "src/rel/enemy_strategy.inc"
#include "src/rel/enemy_strategy_execute.inc"

class TObjEnemyPawn;

template class TEnemyStrategy<TObjEnemyPawn>;
