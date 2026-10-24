#include "types.h"

// The rainfruit family's Unload hook (rainfruitUnload here): each entry's resource is released.

// one entry of the family's table: what the Unload releases is at 0x20
typedef struct RainfruitEntry {
	u8 unk00[0x20];
	void* object; // 0x20
	u8 unk24[0x18];
} RainfruitEntry; // 0x3C

extern "C" RainfruitEntry rainfruitTable[5];

extern "C" void fn_8013BD74(void* object);

extern "C" void rainfruitUnload(void)
{
	RainfruitEntry* table = rainfruitTable;

	for (int i = 0; i < 5; i++) {
		fn_8013BD74(table[i].object);
	}
}
