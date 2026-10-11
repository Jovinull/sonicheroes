// EventManager::setAnimation (the PS2 build's name): it sets a skinned
// hierarchy's animation time and updates its matrices. No unit calls it out of
// line; it is kept with force_active.

#include "src/rel/event_manager_class.inc"
#include "game/object.h"

extern "C" void fn_8020D02C(void* interpolator, f32 time);
extern "C" void fn_8013FC30(RpHAnimHierarchy* hierarchy);

void EventManager::setAnimation(RpHAnimHierarchy* hierarchy, f32 time)
{
	fn_8020D02C(hierarchy->currentAnim, time);
	fn_8013FC30(hierarchy);
}
