#include "types.h"

// The bush's Unload hook (bushUnload here): the model file's model is
// released.

typedef struct BushEntry {
	u8 unk00[0x8];
	void* model; // 0x08
} BushEntry;

extern "C" BushEntry bushModelFile[1];

extern "C" void fn_80150958(void* clump);

extern "C" void bushUnload(void)
{
	BushEntry* files = bushModelFile;

	for (int i = 0; i < 1; i++) {
		if (files[i].model != NULL) {
			fn_80150958(files[i].model);
			files[i].model = NULL;
		}
	}
}
