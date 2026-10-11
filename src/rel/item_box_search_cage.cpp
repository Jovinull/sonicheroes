#include "types.h"

// TObjItembox::SearchCage (the PS2 build's name; itemBoxSearchCage here):
// while the item box's placement has no work block, it looks through the task
// list its communication number names for an object of class 0x24 closer than
// itemBoxRange; for the first one it finds, it gives the placement a
// 0x14-byte work block, marked 0x12345678 and holding the item box's
// position. The body is TObjChao::SearchCage's (rel/chao_methods.inc).

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct ItemBoxWork {
	u32 magic; // 0x00
	RwV3d pos; // 0x04
	u32 unk10; // 0x10
} ItemBoxWork;

typedef struct ItemBoxFrame {
	RwV3d pos;         // 0x00
	u8 unk0C[0x1E];    // 0x0C
	u8 communicateId;  // 0x2A
	u8 unk2B[0x5];     // 0x2B
	ItemBoxWork* work; // 0x30
} ItemBoxFrame;

typedef struct ItemBoxTask {
	u8 pad00[0x28];
	u16 classId; // 0x28
	u8 pad2A[0xE];
	struct ItemBoxTask* next; // 0x38
} ItemBoxTask;

typedef struct ItemBoxTaskLists {
	u8 pad00[0x30];
	ItemBoxTask* lists[1]; // 0x30
} ItemBoxTaskLists;

typedef struct ItemBox {
	u8 base[0x28];       // 0x00
	ItemBoxFrame* frame; // 0x28
} ItemBox;

extern "C" ItemBoxTaskLists* lbl_8042C298;
extern "C" const f32 itemBoxRange[1];
extern "C" void* __nw__FUl(u32 size);

f32 Distance2P2P(const RwV3d* a, const RwV3d* b);

extern "C" void itemBoxSearchCage(ItemBox* object)
{
	if (object->frame->work == NULL) {
		ItemBoxTask* task;
		for (task = lbl_8042C298->lists[object->frame->communicateId]; task != NULL;
		    task  = task->next) {
			if (task->classId == 0x24
			    && Distance2P2P(&object->frame->pos, (RwV3d*)task) < itemBoxRange[0]) {
				object->frame->work        = (ItemBoxWork*)__nw__FUl(0x14);
				object->frame->work->magic = 0x12345678;
				object->frame->work->pos   = object->frame->pos;
				return;
			}
		}
	}
}
