#include "types.h"

// The reafredgreen family's Unload hook (reafredgreenUnload here): each entry's resource is released.

// one entry of the family's table: what the Unload releases is at 0xC
typedef struct ReafredgreenEntry {
	u8 unk00[0xC];
	void* object; // 0xC
	u8 unk10[0x14];
} ReafredgreenEntry; // 0x24

extern "C" ReafredgreenEntry reafredgreenTable[2];

extern "C" void fn_8013BD74(void* object);

extern "C" void reafredgreenUnload(void)
{
	ReafredgreenEntry* table = reafredgreenTable;

	for (int i = 0; i < 2; i++) {
		fn_8013BD74(table[i].object);
	}
}
