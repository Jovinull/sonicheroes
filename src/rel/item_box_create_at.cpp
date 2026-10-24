#include "types.h"

// CreateItembox (the PS2 build's name, by its place in the PS2 order): an item
// box of the given kind is made at the position, as a set object of its own;
// the box made, if any.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct ItemBoxParams {
	s8 kind; // 0x0
} ItemBoxParams;

typedef struct ItemBoxTask {
	u8 unk00[0x2C];
	ItemBoxParams* params; // 0x2C
} ItemBoxTask;

extern "C" void* lbl_8042C298;
extern "C" char itemBoxEntry[];

extern "C" ItemBoxTask* fn_80058FDC(void* tasks, char* entry, RwV3d* pos, s32 a, s32 b);

ItemBoxTask* CreateItembox(RwV3d* pos, signed char kind)
{
	ItemBoxTask* task = fn_80058FDC(lbl_8042C298, itemBoxEntry, pos, 0, 1);

	if (task != NULL) {
		task->params->kind = kind;
	}
	return task;
}
