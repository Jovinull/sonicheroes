#include "types.h"

// The crossing family's Reset and Unload hooks (crossingReset and
// crossingUnload here): nothing to reset; the model files' models are released.
// Its Load does more than load the files and is not here.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" ModelFile crossingModelFiles[13];

extern "C" void fn_80150958(void* clump);

extern "C" void crossingReset(void) { }

extern "C" void crossingUnload(void)
{
	ModelFile* files = crossingModelFiles;

	for (int i = 0; i < 13; i++) {
		if (files[i].model != NULL) {
			fn_80150958(files[i].model);
			files[i].model = NULL;
		}
	}
}
