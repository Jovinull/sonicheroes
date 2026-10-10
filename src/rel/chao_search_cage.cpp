// TObjChao::SearchCage (the PS2 build's name): while the chao's placement has
// no work block, the chao looks through the task list its communication number
// names for an object of class 0x24 within 100 of its position; for the first
// one it finds, it gives the placement a 0x14-byte work block, marked
// 0x12345678 and holding the chao's position. Exec inlines it; this copy has no
// caller and is kept with force_active. The class is in chao_class.inc.

#include "src/rel/chao_class.inc"

struct ChaoTask {
	u8 pad00[0x28];
	u16 classId; // 0x28
	u8 pad2A[0xE];
	ChaoTask* next; // 0x38
};

struct ChaoTaskLists {
	u8 pad00[0x30];
	ChaoTask* lists[1]; // 0x30
};

struct ChaoWork {
	u32 magic; // 0x00
	RwV3d pos; // 0x04
	u32 unk10; // 0x10
};

extern "C" ChaoTaskLists* lbl_8042C298;
extern "C" const f32 chaoCageReach[1];

f32 Distance2P2P(const RwV3d* a, const RwV3d* b);

void TObjChao::SearchCage()
{
	if (ObjParam->originalWork == NULL) {
		ChaoTask* task;
		for (task = lbl_8042C298->lists[ObjParam->setData.communicateId]; task != NULL;
		    task  = task->next) {
			if (task->classId == 0x24
			    && Distance2P2P(&ObjParam->setData.pos, (RwV3d*)task) < chaoCageReach[0]) {
				ObjParam->originalWork                     = new ChaoWork;
				((ChaoWork*)ObjParam->originalWork)->magic = 0x12345678;
				((ChaoWork*)ObjParam->originalWork)->pos   = ObjParam->setData.pos;
				return;
			}
		}
	}
}
