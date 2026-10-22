#include "types.h"

// The propeller's unload hook (propellerUnload here): it releases the three
// models the load read, frees the ten entries the load built with
// fn_8014D308 (fn_8014D8A4 frees one) and marks the resources as not loaded.

typedef struct PropellerEntry {
	void* data;   // 0x00
	u8 unk4[0x8]; // 0x04
} PropellerEntry;

extern "C" void* propellerResources[3];
extern "C" PropellerEntry propellerPathEntries[10];
extern "C" s32 propellerLoaded;

extern "C" void fn_80150958(void* clump);
extern "C" void fn_8014D8A4(void* entry);

extern "C" void propellerUnload(void)
{
	int i;

	for (i = 0; i < 3; i++) {
		if (propellerResources[i] != NULL) {
			fn_80150958(propellerResources[i]);
			propellerResources[i] = NULL;
		}
	}
	for (i = 0; i < 10; i++) {
		if (propellerPathEntries[i].data != NULL) {
			fn_8014D8A4(propellerPathEntries[i].data);
			propellerPathEntries[i].data = NULL;
		}
	}
	propellerLoaded = 0;
}
