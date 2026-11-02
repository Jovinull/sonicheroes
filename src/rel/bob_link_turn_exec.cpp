#include "types.h"

// The exec step of the special stages' third sled link class
// (bobLinkTurnExec here; the class has no PS2 name), in stage01D and
// stage07D. As bobLinkAttachExec (asks to be killed outside the play mode,
// waits while paused unless flag 8 lets it run), but in mode 1 the object
// turns its angle and moves its reach toward their targets, the target
// following both, and the link ends once both are reached and the timer has
// run out: without flag 1 the object is let go of as bobLinkUnlinkKill does,
// and with it flag 2 takes its slot out before the object moves to mode 2.

#include "src/rel/bob_link_class.inc"

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct BobLinkTurn {
	BobLink link; // 0x00
	s8 mode;      // 0x34
	u8 pad35;
	s16 timer;     // 0x36
	sAngle ang;    // 0x38
	s32 angleStep; // 0x44
	s32 angleGoal; // 0x48
	u8 unk4C[0xC]; // 0x4C
	u32 flags;     // 0x58
	f32 reach;     // 0x5C
	f32 reachStep; // 0x60
	f32 reachGoal; // 0x64
} BobLinkTurn;

typedef struct BobLinkTarget {
	u8 unk00[0x1C];
	sAngle ang; // 0x1C
	u8 unk28[0x18];
	f32 reach; // 0x40
} BobLinkTarget;

extern "C" BobLinkTarget lbl_803EA4E8;

s32 AdjustAngle(s32 angle, s32 goal, s32 step);
f32 AdjustFloat(f32 value, f32 goal, f32 step);
s32 SubAngle(s32 a, s32 b);

typedef struct GameState {
	u8 unk00[0x18];
	s32 mode; // 0x18
} GameState;

extern "C" GameState lbl_8029C310;
extern "C" u8* lbl_8042C180;

extern "C" void bobLinkTurnExec(BobLinkTurn* object)
{
	if (lbl_8029C310.mode != 0) {
		object->link.base.signal |= 1;
		return;
	}
	if ((s8)lbl_8042C180[0x1F] != 0 && (object->flags & 8) == 0) {
		return;
	}

	switch (object->mode) {
		case 1:
			object->ang.y      = AdjustAngle(object->ang.y, object->angleGoal, object->angleStep);
			object->reach      = AdjustFloat(object->reach, object->reachGoal, object->reachStep);
			lbl_803EA4E8.ang.y = object->ang.y;
			lbl_803EA4E8.reach = object->reach;
			if (object->timer > 0) {
				object->timer--;
			}
			if (SubAngle(object->ang.y, object->angleGoal) == 0
			    && object->reach == object->reachGoal && object->timer <= 0) {
				if ((object->flags & 1) == 0) {
					bobLinkSlotOut(&object->link);
					if (&object->link == bobLinkCurrent) {
						bobLinkCurrent = NULL;
					}
					object->link.base.signal |= 1;
				} else {
					if (object->flags & 2) {
						bobLinkSlotOut(&object->link);
					}
					object->mode = 2;
				}
			}
			break;
		case 2:
			break;
	}
}
