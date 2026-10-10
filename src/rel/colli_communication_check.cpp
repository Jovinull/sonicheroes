// TObjColliCommunication's KillMyself, HitRinoLiner, HitPlayer, the seven
// CheckCollision steps and CheckCollision itself (the PS2 build's names), in
// the original's order, as rel/flyer_collision_check.cpp has the flyer's.
// CheckCollision runs the step the volume's kind names, which the compiler
// inlines with the hit tests; each step that finds its hit sends the Rinoliners
// of the placement's communication number a command 4 of its own type (1 to
// 7), the two "set" steps with the volume's extent and the speed step with the
// parameter block's second byte. The copies of the small functions have no
// caller and are kept with force_active. The class is in
// game/obj_colli_communication.h.

#include "game/obj_colli_communication.h"
#include "game/enemy/e_communication.h"

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

struct RinoColHit {
	u8 pad00[0x4];
	void* hitter; // 0x04
};

extern "C" const f32 rinoColZero[1];

struct RinoColCommand : public sEnemyCommand {
	s32 type;  // 0x04
	RwV3d pos; // 0x08
	s32 unk14; // 0x14

	RinoColCommand()
	{
		command = 0;
		cid     = 0;
		command = 4;
		type    = 0;
		pos.x = pos.y = pos.z = rinoColZero[0];
		unk14                 = 0;
	}
};

extern "C" RinoColTaskLists* lbl_8042C298;
extern "C" u8 lbl_8042C1A4[];
extern "C" void fn_80021824(void* world);
extern "C" RinoColHit* fn_800211A8(C_COLLI& colli);

s32 TObjColliCommunication::KillMyself()
{
	RinoColTask* task;

	if (CheckMustKill()) {
		return 1;
	}
	RinoColTask* head = lbl_8042C298->lists[ObjParam->setData.communicateId];
	task              = head;
	if (head == NULL) {
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

s32 TObjColliCommunication::HitRinoLiner()
{
	if (C_COLLI::flag & 1) {
		for (int i = 0; i < nbHit; i++) {
			if (hit_info[i].hit_ccl != NULL && hit_info[i].hit_ccl->info->kind == 0x16) {
				return 1;
			}
		}
	}
	return 0;
}

s32 TObjColliCommunication::HitPlayer()
{
	if (C_COLLI::flag & 1) {
		fn_80021824(lbl_8042C1A4);
		RinoColHit* hit = fn_800211A8(*this);
		if ((hit != NULL ? hit->hitter : NULL) != NULL) {
			return 1;
		}
	}
	return 0;
}

s32 TObjColliCommunication::CheckCollisionSpeedCtrl()
{
	s32 hit = HitRinoLiner();
	if (hit && ObjParam != NULL) {
		ColliCommunicationParam* param = (ColliCommunicationParam*)ObjParam->setData.setBuffer;
		RinoColCommand command;
		command.cid   = ObjParam->setData.communicateId;
		command.type  = 7;
		command.unk14 = (s8)param->action;
		command.Send();
	}
	return hit;
}

s32 TObjColliCommunication::CheckCollisionChangePathSet()
{
	s32 hit = HitRinoLiner();
	if (hit && ObjParam != NULL) {
		RinoColCommand command;
		command.cid  = ObjParam->setData.communicateId;
		command.type = 6;
		command.pos  = extent;
		command.Send();
	}
	return hit;
}

s32 TObjColliCommunication::CheckCollisionChangePath()
{
	s32 hit = HitRinoLiner();
	if (hit && ObjParam != NULL) {
		RinoColCommand command;
		command.cid  = ObjParam->setData.communicateId;
		command.type = 5;
		command.Send();
	}
	return hit;
}

s32 TObjColliCommunication::CheckCollisionAttackSet()
{
	s32 hit = HitRinoLiner();
	if (hit && ObjParam != NULL) {
		RinoColCommand command;
		command.cid  = ObjParam->setData.communicateId;
		command.type = 4;
		command.pos  = extent;
		command.Send();
	}
	return hit;
}

s32 TObjColliCommunication::CheckCollisionAttack()
{
	s32 hit = HitRinoLiner();
	if (hit && ObjParam != NULL) {
		RinoColCommand command;
		command.cid  = ObjParam->setData.communicateId;
		command.type = 3;
		command.Send();
	}
	return hit;
}

s32 TObjColliCommunication::CheckCollisionEnd()
{
	s32 hit = HitPlayer();
	if (hit && ObjParam != NULL) {
		RinoColCommand command;
		command.cid  = ObjParam->setData.communicateId;
		command.type = 2;
		command.Send();
	}
	return hit;
}

s32 TObjColliCommunication::CheckCollisionBegin()
{
	s32 hit = HitPlayer();
	if (hit && ObjParam != NULL) {
		RinoColCommand command;
		command.cid  = ObjParam->setData.communicateId;
		command.type = 1;
		command.Send();
	}
	return hit;
}

s32 TObjColliCommunication::CheckCollision()
{
	switch ((s8)kind) {
		case 0:
			return CheckCollisionBegin();
		case 1:
			return CheckCollisionEnd();
		case 2:
			return CheckCollisionChangePath();
		case 4:
			return CheckCollisionAttack();
		case 3:
			return CheckCollisionChangePathSet();
		case 5:
			return CheckCollisionAttackSet();
		case 6:
			return CheckCollisionSpeedCtrl();
	}
	return 0;
}
