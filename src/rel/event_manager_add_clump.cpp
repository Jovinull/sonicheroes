// EventManager::addClump (the PS2 build's name): it adds a clump that is in no
// world to the stage's world.

#include "src/rel/event_manager_class.inc"

extern "C" u8* lbl_8042C1D0;
extern "C" void* fn_8015BD78(struct RpClump* clump);
extern "C" void fn_8015BB08(void* world, struct RpClump* clump);

void EventManager::addClump(struct RpClump* clump)
{
	if (clump != NULL && fn_8015BD78(clump) == NULL) {
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7258), clump);
	}
}
