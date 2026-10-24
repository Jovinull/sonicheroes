#include "types.h"

// The butterfly family's Unload hook (butterflyUnload here): each entry's model is released.

// one entry of the family's table: what the Unload releases is at 0x4
typedef struct ButterflyEntry {
	u8 unk00[0x4];
	void* object; // 0x4
} ButterflyEntry; // 0x8

extern "C" ButterflyEntry butterflyTable[16];

extern "C" void fn_80150958(void* clump);

extern "C" void butterflyUnload(void)
{
	ButterflyEntry* table = butterflyTable;

	for (int i = 0; i < 16; i++) {
		if (table[i].object != NULL) {
			fn_80150958(table[i].object);
			table[i].object = NULL;
		}
	}
}
