#include "types.h"

// The rainmush family's Unload hook (rainmushUnload here): each entry's resource is released.

// one entry of the family's table: what the Unload releases is at 0x0
typedef struct RainmushEntry {
	void* object; // 0x0
} RainmushEntry;  // 0x4

extern "C" RainmushEntry rainmushTable[2];

extern "C" void fn_8013BD74(void* object);

extern "C" void rainmushUnload(void)
{
	RainmushEntry* table = rainmushTable;

	for (int i = 0; i < 2; i++) {
		fn_8013BD74(table[i].object);
	}
}
