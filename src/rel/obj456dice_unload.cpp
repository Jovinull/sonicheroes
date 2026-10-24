#include "types.h"

// The 456 dice's Unload hook (obj456diceUnload here): the model file's model,
// when loaded, has its material effect ended and is released.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" ModelFile obj456diceModelFile[1];

extern "C" void fn_800B8ADC(void* clump);
extern "C" void fn_80150958(void* clump);

extern "C" void obj456diceUnload(void)
{
	ModelFile* files = obj456diceModelFile;

	for (int i = 0; i < 1; i++) {
		if (files[i].model != NULL) {
			fn_800B8ADC(files[i].model);
			fn_80150958(files[i].model);
			files[i].model = NULL;
		}
	}
}
