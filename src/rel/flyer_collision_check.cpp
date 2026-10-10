// TObjFlyerCollision's KillMyself, HitFlyer, HitPlayer, the six CheckCollision
// steps and CheckCollision itself (the PS2 build's names), in the original's
// order. CheckCollision runs the step the volume's kind names (0 Begin to 5
// Pawn), which the compiler inlines, as it inlines the two hit tests into the
// steps; each step that finds its hit sends the flyers of the placement's
// communication number a command 5 of its own type (1 to 6), the last three
// with the volume's extent. The copies of the small functions have no caller
// and are kept with force_active; Exec (rel/flyer_collision_exec.cpp) inlines
// its own KillMyself. The class is in game/obj_flyer_collision.h.

#include "game/obj_flyer_collision.h"
#include "game/enemy/e_communication.h"

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

struct FlyerColHit {
	u8 pad00[0x4];
	void* hitter; // 0x04
};

struct FlyerColCommand : public sEnemyCommand {
	s32 type;  // 0x04
	RwV3d pos; // 0x08
	s32 unk14; // 0x14

	FlyerColCommand()
	{
		command = 0;
		cid     = 0;
		command = 5;
		type    = 0;
		pos.x = pos.y = pos.z = flyerColZero[0];
		unk14                 = 0;
	}
};

extern "C" FlyerColTaskLists* lbl_8042C298;
extern "C" u8 lbl_8042C1A4[];
extern "C" void fn_80021824(void* world);
extern "C" FlyerColHit* fn_800211A8(C_COLLI& colli);

s32 TObjFlyerCollision::KillMyself()
{
	FlyerColTask* task;

	if (CheckMustKill()) {
		return 1;
	}
	FlyerColTask* head = lbl_8042C298->lists[ObjParam->setData.communicateId];
	task               = head;
	if (head == NULL) {
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

s32 TObjFlyerCollision::HitFlyer()
{
	if (C_COLLI::flag & 1) {
		for (int i = 0; i < nbHit; i++) {
			if (hit_info[i].hit_ccl != NULL && hit_info[i].hit_ccl->info->kind == 0x18) {
				return 1;
			}
		}
	}
	return 0;
}

s32 TObjFlyerCollision::HitPlayer()
{
	if (C_COLLI::flag & 1) {
		fn_80021824(lbl_8042C1A4);
		FlyerColHit* hit = fn_800211A8(*this);
		if ((hit != NULL ? hit->hitter : NULL) != NULL) {
			return 1;
		}
	}
	return 0;
}

s32 TObjFlyerCollision::CheckCollisionPawn()
{
	s32 hit = HitFlyer();
	if (hit && ObjParam != NULL) {
		FlyerColCommand command;
		command.unk14 = unkD4;
		command.cid   = ObjParam->setData.communicateId;
		command.type  = 6;
		command.Send();
	}
	return hit;
}

s32 TObjFlyerCollision::CheckCollisionMgun()
{
	s32 hit = HitFlyer();
	if (hit && ObjParam != NULL) {
		FlyerColCommand command;
		command.unk14 = unkD4;
		command.cid   = ObjParam->setData.communicateId;
		command.type  = 5;
		command.pos   = extent;
		command.Send();
	}
	return hit;
}

s32 TObjFlyerCollision::CheckCollisionMissile()
{
	s32 hit = HitFlyer();
	if (hit && ObjParam != NULL) {
		FlyerColCommand command;
		command.cid   = ObjParam->setData.communicateId;
		command.unk14 = unkD4;
		command.type  = 4;
		command.pos   = extent;
		command.Send();
	}
	return hit;
}

s32 TObjFlyerCollision::CheckCollisionBomb()
{
	s32 hit = HitFlyer();
	if (hit && ObjParam != NULL) {
		FlyerColCommand command;
		command.cid   = ObjParam->setData.communicateId;
		command.unk14 = unkD4;
		command.type  = 3;
		command.pos   = extent;
		command.Send();
	}
	return hit;
}

s32 TObjFlyerCollision::CheckCollisionEnd()
{
	s32 hit = HitPlayer();
	if (hit && ObjParam != NULL) {
		FlyerColCommand command;
		command.cid   = ObjParam->setData.communicateId;
		command.unk14 = unkD4;
		command.type  = 2;
		command.Send();
	}
	return hit;
}

s32 TObjFlyerCollision::CheckCollisionBegin()
{
	s32 hit = HitPlayer();
	if (hit && ObjParam != NULL) {
		FlyerColCommand command;
		command.cid   = ObjParam->setData.communicateId;
		command.unk14 = unkD4;
		command.type  = 1;
		command.Send();
	}
	return hit;
}

s32 TObjFlyerCollision::CheckCollision()
{
	switch ((s8)kind) {
		case 0:
			return CheckCollisionBegin();
		case 1:
			return CheckCollisionEnd();
		case 2:
			return CheckCollisionBomb();
		case 3:
			return CheckCollisionMissile();
		case 4:
			return CheckCollisionMgun();
		case 5:
			return CheckCollisionPawn();
	}
	return 0;
}
