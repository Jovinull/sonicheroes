#include "types.h"

// The springblkAir family's Unload hook (springblkAirUnload here): each entry's model is released.

// one entry of the family's table: what the Unload releases is at 0xC
typedef struct SpringblkAirEntry {
	u8 unk00[0xC];
	void* object;    // 0xC
} SpringblkAirEntry; // 0x10

extern "C" SpringblkAirEntry springblkAirTable[7];

extern "C" void fn_80150958(void* clump);

extern "C" void springblkAirUnload(void)
{
	SpringblkAirEntry* table = springblkAirTable;

	for (int i = 0; i < 7; i++) {
		if (table[i].object != NULL) {
			fn_80150958(table[i].object);
			table[i].object = NULL;
		}
	}
}
