// EventManager::removeClump (the PS2 build's name): it takes a clump out of
// the world it is in, if any.

#include "src/rel/event_manager_class.inc"

extern "C" void* fn_8015BD78(struct RpClump* clump);
extern "C" void fn_8015BBF8(void* world, struct RpClump* clump);

void EventManager::removeClump(struct RpClump* clump)
{
	if (clump != NULL) {
		void* world = fn_8015BD78(clump);
		if (world != NULL) {
			fn_8015BBF8(world, clump);
		}
	}
}
