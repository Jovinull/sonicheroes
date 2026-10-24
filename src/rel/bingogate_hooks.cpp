#include "types.h"

// The bingogate family's Reset and Unload hooks (bingogateReset and
// bingogateUnload here): nothing to reset; the model files' models are
// released. Its Load does more than load the files and is not here.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" ModelFile bingogateModelFiles[19];

extern "C" void fn_80150958(void* clump);

extern "C" void bingogateReset(void) { }

extern "C" void bingogateUnload(void)
{
	ModelFile* files = bingogateModelFiles;

	for (int i = 0; i < 19; i++) {
		if (files[i].model != NULL) {
			fn_80150958(files[i].model);
			files[i].model = NULL;
		}
	}
}
