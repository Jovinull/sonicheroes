#include "types.h"

// The x sign's Unload hook (xSignUnload here): the model file's model is
// released.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" ModelFile xSignModelFile;

extern "C" void fn_80150958(void* clump);

extern "C" void xSignUnload(void)
{
	ModelFile* file = &xSignModelFile;

	for (int i = 0; i < 1; i++) {
		if (file[i].model != NULL) {
			fn_80150958(file[i].model);
			file[i].model = NULL;
		}
	}
}
