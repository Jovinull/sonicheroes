// EventManager::releaseSceneAll (the PS2 build's name): it releases every
// scene, frees the clumps of the event's objects and destroys the event's
// texture dictionary, answering what releaseScene answered. No unit calls it
// out of line; it is kept with force_active.

#include "src/rel/event_manager_class.inc"

extern "C" void fn_800D075C(void* clump);
extern "C" void fn_801A46D0(void* dictionary);

s32 EventManager::releaseSceneAll()
{
	s32 result = releaseScene(NULL);

	unk3C = 0;
	for (int i = 0; i < 16; i++) {
		if (objects[i].clump != NULL) {
			fn_800D075C(objects[i].clump);
			objects[i].clump = NULL;
		}
	}
	if (texDict != NULL) {
		fn_801A46D0(texDict);
	}
	return result;
}
