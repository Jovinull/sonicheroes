#include "types.h"

// Drops the five models an object can be holding, unregistering each from the
// world it was added to before letting go of it.
//
// The claim is .text 0x6E78 to 0x6EFC and nothing else. Everything it touches
// is a DOL symbol, so there is no data to take and nothing to rename per
// module.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out.

typedef struct World {
	u8 unk0[0x725C]; // 0x0000
	void* scene;     // 0x725C
} World;

typedef struct Object {
	u8 unk0[0xE0];   // 0x00
	void* models[5]; // 0xE0
} Object;

extern "C" World* lbl_8042C1D0;

extern "C" void fn_80150958(void* model);
extern "C" void fn_8015BBF8(void* scene, void* model);

extern "C" void objReleaseModels(Object* object)
{
	s32 i;

	for (i = 0; i < 5; i++) {
		if (object->models[i] != NULL) {
			fn_8015BBF8(lbl_8042C1D0->scene, object->models[i]);
			fn_80150958(object->models[i]);
			object->models[i] = NULL;
		}
	}
}
