// EventManager::releaseSceneExtObjs (the PS2 build's name): for the entries
// that hold a clump (they are filled from the start), it takes the clump out
// of its world, frees it and destroys its animation interpolator, then clears
// all sixteen entries.

#include "src/rel/event_manager_class.inc"

extern "C" void fn_80150958(struct RpClump* clump);
extern "C" void fn_8020C2D8(void* interpolator);

void EventManager::releaseSceneExtObjs()
{
	for (int i = 0; i < 16; i++) {
		if (entries[i].clump == NULL) {
			break;
		}
		removeClump(entries[i].clump);
		fn_80150958(entries[i].clump);
		if (entries[i].interpolator != NULL) {
			fn_8020C2D8(entries[i].interpolator);
		}
	}
	memset(entries, 0, sizeof(entries));
}
