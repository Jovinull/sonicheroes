#include "types.h"

// The kazariobj family's Unload hook (kazariobjUnload here): each entry's model is released.

// one entry of the family's table: what the Unload releases is at 0x4
typedef struct KazariobjEntry {
	u8 unk00[0x4];
	void* object; // 0x4
} KazariobjEntry; // 0x8

extern "C" KazariobjEntry kazariobjTable[3];

extern "C" void fn_80150958(void* clump);

extern "C" void kazariobjUnload(void)
{
	KazariobjEntry* table = kazariobjTable;

	for (int i = 0; i < 3; i++) {
		if (table[i].object != NULL) {
			fn_80150958(table[i].object);
			table[i].object = NULL;
		}
	}
}
