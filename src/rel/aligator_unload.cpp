#include "types.h"

// The alligator's Unload hook (aligatorUnload here): its path is released,
// then its animated model file's model and, when loaded, its animation.

struct AnimModelFile {
	u8 unk00[0xC];
	void* model; // 0x0C
	void* anim;  // 0x10
	u8 unk14[0x10];
}; // 0x24

extern "C" void* aligatorPath;
extern "C" AnimModelFile aligatorModelFile[1];

extern "C" void fn_8014D8A4(void* path);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8020C2D8(void* anim);

extern "C" void aligatorUnload(void)
{
	if (aligatorPath != NULL) {
		fn_8014D8A4(aligatorPath);
		aligatorPath = NULL;
	}
	AnimModelFile* files = aligatorModelFile;
	for (int i = 0; i < 1; i++) {
		fn_80150958(files[i].model);
		if (files[i].anim != NULL) {
			fn_8020C2D8(files[i].anim);
		}
	}
}
