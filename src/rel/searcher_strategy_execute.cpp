#include "types.h"

// TEnemyStrategy<TObjEnemySearcher>::Execute (the PS2 build's name), the
// searcher strategy's template instance (rel/enemy_strategy_execute.inc),
// emitted after ExecStrategyMode. Explicit instantiation of the class emits
// only Execute (the inline members are unused; the pure ones only warn).

#include "src/rel/enemy_strategy.inc"
#include "src/rel/enemy_strategy_execute.inc"

class TObjEnemySearcher;

template class TEnemyStrategy<TObjEnemySearcher>;
