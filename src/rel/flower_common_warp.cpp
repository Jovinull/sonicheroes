#include "types.h"

// TObjFlowerCommon::SearchWarpExit (the PS2 build's name, by its place in the
// PS2 order): among the placements of the flower's group (the list the
// placement's group byte picks), the first other one of type 0x32 is kept as
// the warp exit.

typedef struct FlowerParam {
	u8 unk00[0x28];
	u16 type;                 // 0x28
	u8 group;                 // 0x2A
	u8 unk2B[0xD];            // 0x2B
	struct FlowerParam* next; // 0x38
} FlowerParam;

typedef struct FlowerLists {
	u8 unk00[0x30];
	FlowerParam* groups[1]; // 0x30
} FlowerLists;

typedef struct FlowerCommon {
	u8 unk000[0x28];
	FlowerParam* param;    // 0x028
	u8 unk02C[0x164];      // 0x02C
	FlowerParam* warpExit; // 0x190
} FlowerCommon;

extern "C" FlowerLists* lbl_8042C298;

// the first placement of the group's list; through an inline the head comes
// back in r0 and is copied into the walker, as in the retail
static inline FlowerParam* flowerGroupTop(FlowerParam* param)
{
	return lbl_8042C298->groups[param->group];
}

extern "C" void SearchWarpExit__16TObjFlowerCommonFv(FlowerCommon* flower)
{
	FlowerParam* p;

	for (p = flowerGroupTop(flower->param); p != NULL; p = p->next) {
		if (p->type == 0x32 && p != flower->param) {
			flower->warpExit = p;
			return;
		}
	}
}
