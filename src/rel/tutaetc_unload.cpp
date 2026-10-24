#include "types.h"

// The tutaetc family's Unload hook (tutaetcUnload here): for each of its four
// entries the model, the path and the animation are released, when loaded.

typedef struct TutaetcEntry {
	u8 unk00[0x10];
	void* model; // 0x10
	void* anim;  // 0x14
	void* path;  // 0x18
	u8 unk1C[0x30];
} TutaetcEntry; // 0x4C

extern "C" TutaetcEntry tutaetcTable[4];

extern "C" void fn_80150958(void* clump);
extern "C" void fn_8014D8A4(void* path);
extern "C" void fn_8020C2D8(void* anim);

extern "C" void tutaetcUnload(void)
{
	TutaetcEntry* table = tutaetcTable;

	for (int i = 0; i < 4; i++) {
		if (table[i].model != NULL) {
			fn_80150958(table[i].model);
		}
		if (table[i].path != NULL) {
			fn_8014D8A4(table[i].path);
		}
		if (table[i].anim != NULL) {
			fn_8020C2D8(table[i].anim);
		}
	}
}
