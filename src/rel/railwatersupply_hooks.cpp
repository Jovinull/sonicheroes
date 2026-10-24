#include "types.h"

// The railwatersupply family's Reset and Unload hooks (railwatersupplyReset and
// railwatersupplyUnload here): nothing to reset; the model files' models are
// released. Its Load does more than load the files and is not here.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" ModelFile railWaterSupplyModelFiles[2];

extern "C" void fn_80150958(void* clump);

extern "C" void railwatersupplyReset(void) { }

extern "C" void railwatersupplyUnload(void)
{
	ModelFile* files = railWaterSupplyModelFiles;

	for (int i = 0; i < 2; i++) {
		if (files[i].model != NULL) {
			fn_80150958(files[i].model);
			files[i].model = NULL;
		}
	}
}
