// EventManager::setDAnimation (the PS2 build's name): it sets a morph
// animation on an atomic and advances it to the given time. No unit calls it
// out of line; it is kept with force_active.

#include "src/rel/event_manager_class.inc"

extern "C" void fn_8013D344(struct RpAtomic* atomic, struct RpDMorphAnimation* animation);
extern "C" void fn_8013D5C8(struct RpAtomic* atomic, f32 time);

void EventManager::setDAnimation(
    struct RpDMorphAnimation* animation, struct RpAtomic* atomic, f32 time)
{
	fn_8013D344(atomic, animation);
	fn_8013D5C8(atomic, time);
}
