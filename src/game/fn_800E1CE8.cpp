#include "game/rw_types.h"

// Re-aligns a player's action frame with the gravity plane (HYPOTHESIS: run after a gravity
// change; see fn_800E1F28 for lbl_8042C4A0/lbl_8042C4A4): only for actions without the low flag
// bits (+0x6 & 3), and not while the player moves faster than +0xFC unless it is in a busy stage
// (fn_80018EA8) in team mode 2 (+0x258 then +0x140) past frame 0x1E (+0x12), or has flag 0x8000
// (+0x20), or the action is 0x43. The action's X and Z angles (+0xC, +0x14) turn towards the
// plane angles by at most 0x800 (copied to the motion's +0x18 and +0x20), the speed (+0x60) is
// taken out of the old frame (fn_8003E9B4) and into the new one (fn_8003EB18), and the position
// (+0x18) keeps the point lbl_8042E230 times the height +0x13C above it in place (fn_8003E9B4
// before and after). Roles UNKNOWN.

struct Angle800E1CE8 {
	s32 x;
	s32 y;
	s32 z;
};

struct Action800E1CE8 {
	s16 mode; // 0x0
	u8 pad2[0x6 - 0x2];
	s16 flags; // 0x6
	u8 pad8[0xC - 0x8];
	Angle800E1CE8 angle; // 0xC
	RwV3d position;      // 0x18
};

struct Motion800E1CE8 {
	u8 pad0[0x18];
	s32 angleX; // 0x18
	u8 pad1C[0x20 - 0x1C];
	s32 angleZ; // 0x20
};

struct Team800E1CE8 {
	u8 pad0[0x140];
	s32 mode; // 0x140
};

struct Record800E1CE8 {
	u8 pad0[0x12];
	s16 frame; // 0x12
	u8 pad14[0x20 - 0x14];
	s32 flags; // 0x20
	u8 pad24[0x60 - 0x24];
	RwV3d speed; // 0x60
	u8 pad6C[0xFC - 0x6C];
	f32 speedLimit; // 0xFC
	u8 pad100[0x13C - 0x100];
	f32 height; // 0x13C
	u8 pad140[0x258 - 0x140];
	Team800E1CE8* team; // 0x258
};

extern "C" {
extern u8 lbl_8029C310[];
extern s32 lbl_8042C4A0;
extern s32 lbl_8042C4A4;
extern const f32 lbl_8042E1F0; // 0.0f
extern const f32 lbl_8042E230;
s32 fn_80018EA8(void* stage);
void fn_8003E9B4(Action800E1CE8* action, RwV3d* vector);
void fn_8003EB18(Action800E1CE8* action, RwV3d* vector);
}

// game/misc.h declares AdjustAngle returning u16; the callers use the full register.
s32 AdjustAngle(s32 first, s32 second, s32 limit);

extern "C" void fn_800E1CE8(Action800E1CE8* action, Motion800E1CE8* motion, Record800E1CE8* record)
{
	if ((action->flags & 3) != 0) {
		return;
	}
	RwV3d speed;
	speed.x = record->speed.x;
	speed.y = record->speed.y;
	speed.z = record->speed.z;
	if (fn_80018EA8(lbl_8029C310) != 0 && record->team->mode == 2) {
		if (record->frame <= 0x1E
		    && speed.z * speed.z + (speed.x * speed.x + speed.y * speed.y)
		        > record->speedLimit * record->speedLimit) {
			return;
		}
	} else if (!(record->flags & 0x8000) && action->mode != 0x43
	    && speed.z * speed.z + (speed.x * speed.x + speed.y * speed.y)
	        > record->speedLimit * record->speedLimit) {
		return;
	}
	fn_8003E9B4(action, &speed);
	RwV3d up;
	up.z = lbl_8042E1F0;
	up.x = lbl_8042E1F0;
	up.y = lbl_8042E230 * record->height;
	fn_8003E9B4(action, &up);
	up.x           = up.x + action->position.x;
	up.y           = up.y + action->position.y;
	up.z           = up.z + action->position.z;
	motion->angleX = action->angle.x = AdjustAngle(action->angle.x, lbl_8042C4A0, 0x800);
	motion->angleZ = action->angle.z = AdjustAngle(action->angle.z, lbl_8042C4A4, 0x800);
	fn_8003EB18(action, &speed);
	record->speed.x    = speed.x;
	record->speed.y    = speed.y;
	record->speed.z    = speed.z;
	action->position.x = up.x;
	action->position.y = up.y;
	action->position.z = up.z;
	up.z               = lbl_8042E1F0;
	up.x               = lbl_8042E1F0;
	up.y               = lbl_8042E230 * record->height;
	fn_8003E9B4(action, &up);
	action->position.x -= up.x;
	action->position.y -= up.y;
	action->position.z -= up.z;
}
