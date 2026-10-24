#include "types.h"

// The froggreen family's Unload hook (froggreenUnload here): each animated model
// file's model and animation are released, when loaded.

// One of the module's animated model files: the model and its animation once
// loaded.
struct AnimModelFile {
	u8 unk00[0xC];
	void* model; // 0x0C
	void* anim;  // 0x10
	u8 unk14[0x10];
}; // 0x24

extern "C" AnimModelFile froggreenModelFiles[2];

extern "C" void fn_80150958(void* clump);
extern "C" void fn_8020C2D8(void* anim);

extern "C" void froggreenUnload(void)
{
	AnimModelFile* files = froggreenModelFiles;

	for (int i = 0; i < 2; i++) {
		if (files[i].model != NULL) {
			fn_80150958(files[i].model);
		}
		if (files[i].anim != NULL) {
			fn_8020C2D8(files[i].anim);
		}
	}
}
