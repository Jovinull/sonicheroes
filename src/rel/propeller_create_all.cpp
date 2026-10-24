#include "types.h"

// CreatePropellers (the PS2 build's name, by its place in the PS2 order): once
// the propeller's resources are loaded, a propeller is made at the start of
// each loaded path, 40 below it, knowing its path (and hanging if that
// knowledge cannot be allocated); the two arguments are kept. Whether the
// propellers were made.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct PropellerEntry {
	void* data;   // 0x00
	u8 unk4[0x8]; // 0x04
} PropellerEntry;

typedef struct PropellerPathRef {
	s16 index; // 0x0
	s16 one;   // 0x2
	void* unk; // 0x4
} PropellerPathRef;

typedef struct PropellerTask {
	u8 unk00[0x30];
	PropellerPathRef* path; // 0x30
} PropellerTask;

extern "C" void* lbl_8042C298;
extern "C" s32 propellerLoaded;
extern "C" PropellerEntry propellerPathEntries[10];
extern "C" char propellerEntry[];
extern "C" s32 propellerCreateArgA;
extern "C" s32 propellerCreateArgB;
extern "C" const f32 propellerZeroSpin[1];
extern "C" const f32 propellerStartDrop[1];

extern "C" void fn_8014D308(void* path, s32 kind, f32 t, RwV3d* out, s32 arg);
extern "C" PropellerTask* fn_80058FDC(void* tasks, char* entry, RwV3d* pos, s32 a, s32 b);
extern "C" void* __nw__FUl(u32 size);

int CreatePropellers(int a, int b)
{
	if (propellerLoaded != 0) {
		for (s32 i = 0; i < 10; i++) {
			if (propellerPathEntries[i].data != NULL) {
				RwV3d pos;

				fn_8014D308(propellerPathEntries[i].data, 10, propellerZeroSpin[0], &pos, 0);
				pos.y -= propellerStartDrop[0];
				PropellerTask* task = fn_80058FDC(lbl_8042C298, propellerEntry, &pos, 0, 1);
				task->path          = (PropellerPathRef*)__nw__FUl(sizeof(PropellerPathRef));
				if (task->path == NULL) {
					for (;;) {
					}
				}
				task->path->index = i;
				task->path->one   = 1;
				task->path->unk   = NULL;
			}
		}
		propellerCreateArgA = a;
		propellerCreateArgB = b;
		return 1;
	}
	return 0;
}
