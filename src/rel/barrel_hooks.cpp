#include "types.h"

// The barrel family's Reset and Unload hooks (barrelReset and barrelUnload
// here): nothing to reset; the model files' models are released, with their
// animations. Its Load does more than load the files and is not here.

// One of the module's animated model files: its name, the archive it is read
// from, the world slot its clones go into, the model and its animation once
// loaded.
struct AnimModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
	void* anim;       // 0x10
	u8 unk14[0x10];   // 0x14
};

extern "C" AnimModelFile barrelModelFiles[2];

extern "C" void fn_80150958(void* clump);
extern "C" void fn_8020C2D8(void* anim);

extern "C" void barrelReset(void) { }

extern "C" void barrelUnload(void)
{
	AnimModelFile* files = barrelModelFiles;

	for (int i = 0; i < 2; i++) {
		fn_80150958(files[i].model);
		if (files[i].anim != NULL) {
			fn_8020C2D8(files[i].anim);
		}
	}
}
