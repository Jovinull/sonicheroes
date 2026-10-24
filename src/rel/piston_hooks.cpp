#include "types.h"

// The piston family's Reset and Unload hooks (pistonReset and pistonUnload
// here): nothing to reset; the model file's model is released, with its
// animation. Its Load does more than load the files and is not here.

// One of the module's animated model files: its name, the archive it is read
// from, the world slot its clones go into, the model and its animation once
// loaded.
struct AnimModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
	void* anim;       // 0x10
};

extern "C" AnimModelFile pistonModelFile[1];

extern "C" void fn_80150958(void* clump);
extern "C" void fn_8020C2D8(void* anim);

extern "C" void pistonReset(void) { }

extern "C" void pistonUnload(void)
{
	AnimModelFile* files = pistonModelFile;

	for (int i = 0; i < 1; i++) {
		fn_80150958(files[i].model);
		if (files[i].anim != NULL) {
			fn_8020C2D8(files[i].anim);
		}
	}
}
