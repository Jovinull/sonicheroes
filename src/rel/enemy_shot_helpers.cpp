#include "game/effect/eff_bomb.h"

// The out-of-line copies of the two TObject helpers that ENEMY_SHOT::KillTask
// inlines (enemyShotKill and enemyShotIsClass here): the original unit emits
// them at its end because the deepest inlined level of KillTask calls them.
// See rel/enemy_shot_kill.cpp.

extern "C" void enemyShotKill(TObject* object)
{
	object->Signal |= 1;
}

extern "C" s32 enemyShotIsClass(TObject* object, char* name)
{
	return object->ClassName == name;
}
