#include "types.h"

// The moving platform's Unload hook (s02MovingLandUnload here): each of its
// three pieces' models is released.

extern "C" void* s02MovingLandModels[3];

extern "C" void fn_80150958(void* clump);

extern "C" void s02MovingLandUnload(void)
{
	for (s8 i = 0; i < 3; i++) {
		if (s02MovingLandModels[i] != NULL) {
			fn_80150958(s02MovingLandModels[i]);
			s02MovingLandModels[i] = NULL;
		}
	}
}
