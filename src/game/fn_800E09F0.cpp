#include "types.h"

// Puts player slot idx into action 7 moving along a direction at a given speed, unless it is
// already in action 0x3F with the action flag 0x1000 set: the action state (lbl_802AD090) faces the
// direction (its yaw from atan2, set as fn_800E01E4 does with zero pitch and roll), the direction
// scaled by the speed becomes the slot's velocity (lbl_802AD0B0) and, filtered by fn_8003EB18, the
// record's +0x60 (lbl_802AD0D0). HYPOTHESIS: a forced launch; the field names are UNKNOWN.

struct Vec800E09F0 {
	f32 x;
	f32 y;
	f32 z;
};

struct Action800E09F0 {
	u8 pad0[0x4];
	s16 action; // 0x4
	s16 flags;  // 0x6
	u8 pad8[0xC - 0x8];
	s32 angleX; // 0xC
	s32 angleY; // 0x10
	s32 angleZ; // 0x14
};

struct Position800E09F0 {
	Vec800E09F0 velocity; // 0x0
	u8 padC[0x1C - 0xC];
	s32 yaw; // 0x1C
};

struct Record800E09F0 {
	u8 pad0[0x60];
	Vec800E09F0 velocity; // 0x60
};

extern "C" {
extern Action800E09F0* lbl_802AD090[];
extern Position800E09F0* lbl_802AD0B0[];
extern Record800E09F0* lbl_802AD0D0[];
extern const f32 lbl_8042E210; // radians to 16-bit angle units
double atan2(double y, double x);
void fn_8003EB18(Action800E09F0* action, Vec800E09F0* velocity);
}

// As fn_800E01E4, but taking the yaw in radians (the conversion follows the table loads).
static inline void SetAngle(s32 idx, s32 x, f32 y, s32 z)
{
	Action800E09F0* action     = lbl_802AD090[idx];
	Position800E09F0* position = lbl_802AD0B0[idx];
	action->angleX             = x;
	action->angleY             = 0x4000 - (s32)(lbl_8042E210 * y);
	position->yaw              = action->angleY;
	action->angleZ             = z;
}

extern "C" void fn_800E09F0(s32 idx, f32 speed, const Vec800E09F0* direction)
{
	Action800E09F0* action     = lbl_802AD090[idx];
	Position800E09F0* position = lbl_802AD0B0[idx];
	Record800E09F0* record     = lbl_802AD0D0[idx];

	if ((action->flags & 0x1000) && action->action == 0x3F) {
		return;
	}
	action->flags |= 0x1000;
	action->action = 7;
	SetAngle(idx, 0, atan2(direction->x, direction->z), 0);

	Vec800E09F0 velocity;
	velocity.x = direction->x;
	velocity.y = direction->y;
	velocity.z = direction->z;
	velocity.x *= speed;
	velocity.y *= speed;
	velocity.z *= speed;
	position->velocity.x = velocity.x;
	position->velocity.y = velocity.y;
	position->velocity.z = velocity.z;
	fn_8003EB18(action, &velocity);
	record->velocity.x = velocity.x;
	record->velocity.y = velocity.y;
	record->velocity.z = velocity.z;
}
