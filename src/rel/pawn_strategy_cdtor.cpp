#include "types.h"

// TEnemyPawn_Strategy's destructor and constructor (the PS2 build's names); the
// strategy base's destructor and vtable come out of this unit as template
// instances, as in the retail.

#include "src/rel/pawn_strategy.inc"

TEnemyPawn_Strategy::~TEnemyPawn_Strategy() { }

TEnemyPawn_Strategy::TEnemyPawn_Strategy() { }
