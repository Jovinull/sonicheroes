#include "types.h"

// The pond's Unload hook (pondUnload here): for each of its three entries
// with a model, the model and its second model are released.

typedef struct PondEntry {
	u8 unk00[0x14];
	void* model;  // 0x14
	void* model2; // 0x18
} PondEntry;      // 0x1C

extern "C" PondEntry pondTable[3];

extern "C" void fn_80150958(void* clump);

extern "C" void pondUnload(void)
{
	PondEntry* table = pondTable;

	for (int i = 0; i < 3; i++) {
		if (table[i].model != NULL) {
			fn_80150958(table[i].model);
			fn_80150958(table[i].model2);
			table[i].model = NULL;
		}
	}
}
