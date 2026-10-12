// TObjFlyerCollision::Exec: the volume ends itself when it must be killed or
// when no flyer (class 0x1530) is left in the task list its placement's
// communication number names (KillMyself in the PS2 build, inline here); it
// also ends its set object when CheckCollision says it was hit. Otherwise its
// collision keeps its last position, takes the placement's again and enters.
// The class is in game/obj_flyer_collision.h.

#define FLYER_COL_DTOR_FIRST
#include "game/obj_flyer_collision.h"

struct FlyerColTask {
	u8 pad00[0x28];
	u16 classId; // 0x28
	u8 pad2A[0xE];
	FlyerColTask* next; // 0x38
};

struct FlyerColTaskLists {
	u8 pad00[0x30];
	FlyerColTask* lists[1]; // 0x30
};

extern "C" FlyerColTaskLists* lbl_8042C298;

static inline s32 flyerColKillMyself(TObjFlyerCollision* self)
{
	FlyerColTask* task;

	if (self->CheckMustKill()) {
		return 1;
	}
	task = lbl_8042C298->lists[self->ObjParam->setData.communicateId];
	if (task == NULL) {
		return 1;
	}
	while (task != NULL) {
		if (task->classId == 0x1530) {
			return 0;
		}
		task = task->next;
	}
	return 1;
}

void TObjFlyerCollision::Exec()
{
	if (flyerColKillMyself(this)) {
		Signal |= 1;
		return;
	}
	if (CheckCollision()) {
		SetEnd();
		Signal |= 1;
		return;
	}
	if (info != NULL) {
		pre_pos      = C_COLLI::pos;
		C_COLLI::pos = pos;
		C_COLLI::ang = ang;
		Entry();
	}
}
