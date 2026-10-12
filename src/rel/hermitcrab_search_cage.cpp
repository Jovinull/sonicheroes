#include "types.h"

// TObjHermitCrab::SearchCage (the PS2 build's name; hermitcrabSearchCage here):
// while the hermit crab's placement has no work block, it looks through the task
// list its communication number names for an object of class 0x24 closer than
// hermitcrabCageRange; for the first one it finds, it gives the placement a
// 0x14-byte work block, marked 0x12345678 and holding the hermit crab's
// position. The body is TObjChao::SearchCage's (rel/chao_methods.inc).

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct HermitcrabWork {
	u32 magic; // 0x00
	RwV3d pos; // 0x04
	u32 unk10; // 0x10
} HermitcrabWork;

typedef struct HermitcrabFrame {
	RwV3d pos;            // 0x00
	u8 unk0C[0x1E];       // 0x0C
	u8 communicateId;     // 0x2A
	u8 unk2B[0x5];        // 0x2B
	HermitcrabWork* work; // 0x30
} HermitcrabFrame;

typedef struct HermitcrabTask {
	u8 pad00[0x28];
	u16 classId; // 0x28
	u8 pad2A[0xE];
	struct HermitcrabTask* next; // 0x38
} HermitcrabTask;

typedef struct HermitcrabTaskLists {
	u8 pad00[0x30];
	HermitcrabTask* lists[1]; // 0x30
} HermitcrabTaskLists;

typedef struct Hermitcrab {
	u8 base[0x28];          // 0x00
	HermitcrabFrame* frame; // 0x28
} Hermitcrab;

extern "C" HermitcrabTaskLists* lbl_8042C298;
extern "C" const f32 hermitcrabCageRange[1];
extern "C" void* __nw__FUl(u32 size);

f32 Distance2P2P(const RwV3d* a, const RwV3d* b);

extern "C" void hermitcrabSearchCage(Hermitcrab* object)
{
	if (object->frame->work == NULL) {
		HermitcrabTask* task;
		for (task = lbl_8042C298->lists[object->frame->communicateId]; task != NULL;
		    task  = task->next) {
			if (task->classId == 0x24
			    && Distance2P2P(&object->frame->pos, (RwV3d*)task) < hermitcrabCageRange[0]) {
				object->frame->work        = (HermitcrabWork*)__nw__FUl(0x14);
				object->frame->work->magic = 0x12345678;
				object->frame->work->pos   = object->frame->pos;
				return;
			}
		}
	}
}
