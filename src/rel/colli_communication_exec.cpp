// TObjColliCommunication::Exec: the volume ends itself when it must be killed
// or when no Rinoliner (class 0x1590) is left in the task list its placement's
// communication number names (KillMyself, inline here, as in
// rel/flyer_collision_exec.cpp). While the game is paused or being edited
// (the state bytes at 0x1F to 0x21) it only clears its collision; otherwise it
// ends its set object when CheckCollision says it was hit, or its collision
// keeps its last position, takes the placement's again and enters. The class
// is in game/obj_colli_communication.h.

#define COLLI_COMM_DTOR_FIRST
#include "game/obj_colli_communication.h"

struct RinoColTask {
	u8 pad00[0x28];
	u16 classId; // 0x28
	u8 pad2A[0xE];
	RinoColTask* next; // 0x38
};

struct RinoColTaskLists {
	u8 pad00[0x30];
	RinoColTask* lists[1]; // 0x30
};

extern "C" RinoColTaskLists* lbl_8042C298;

struct RinoColGameState {
	u8 pad00[0x1F];
	s8 paused;   // 0x1F
	s8 editMode; // 0x20
	s8 unk21;    // 0x21
};

extern "C" RinoColGameState* lbl_8042C180;

static inline s32 rinoColRunning()
{
	if (lbl_8042C180->paused) {
		return 0;
	}
	if (lbl_8042C180->editMode) {
		return 0;
	}
	if (lbl_8042C180->unk21) {
		return 0;
	}
	return 1;
}

static inline s32 rinoColKillMyself(TObjColliCommunication* self)
{
	RinoColTask* task;

	if (self->CheckMustKill()) {
		return 1;
	}
	task = lbl_8042C298->lists[self->ObjParam->setData.communicateId];
	if (task == NULL) {
		return 1;
	}
	while (task != NULL) {
		if (task->classId == 0x1590) {
			return 0;
		}
		task = task->next;
	}
	return 1;
}

void TObjColliCommunication::Exec()
{
	if (rinoColKillMyself(this)) {
		Signal |= 1;
		return;
	}
	if (!rinoColRunning()) {
		ClearInfo();
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
