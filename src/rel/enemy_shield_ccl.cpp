// ENEMY_SHIELD::SetCCLParameter (the PS2 build's name), the same in the
// thirteen stage modules that share the engine core: when the shield's scale
// has changed, its collision volume takes it as its size and recomputes its
// range. The class is in enemy_shield.inc.

#include "game/effect/eff_bomb.h"
#include "game/object.h"
#include "src/rel/enemy_shield.inc"

void ENEMY_SHIELD::SetCCLParameter()
{
	if (info->a != scale) {
		info->a = scale;
		CalcRange();
	}
}
