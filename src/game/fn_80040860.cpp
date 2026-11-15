#include "game/rw_types.h"

// Turns a player away from the object it touches (HYPOTHESIS: a push-back on contact): after
// refreshing its collision block (+0x28, fn_80021824) it takes the object of the first hit
// (fn_80020FD8) when that object's +0x6 is positive or the block has a key-0x14 entry
// (fn_8001F9F8), otherwise the object of the first hit with type 1 (fn_80020BD8). The horizontal
// offset from the player (+0x708) to the object's position (+0x60), when longer than
// lbl_8042D17C, is normalized and scaled by minus the speed (+0x7C0, fn_801991B4); the result
// becomes the push vector (+0x720) and the velocity, the yaw (+0x700, +0x73C) follows it
// (atan2) and the velocity is turned into the action frame (fn_8003EB18). Roles UNKNOWN.

struct Object80040860 {
	u8 pad0[0x6];
	s16 unknown6; // 0x6
	u8 pad8[0x60 - 0x8];
	RwV3d position; // 0x60
};

struct Hit80040860 {
	u8 pad0[0x4];
	Object80040860* object; // 0x4
};

struct Colli80040860 {
	u8 unknown[0x88];
};

struct Action80040860 {
	u8 pad0[0xC];
	s32 angle[3]; // 0xC (angle[1] is the yaw)
};

struct Player80040860 {
	u8 pad0[0x28];
	Colli80040860 colli; // 0x28
	u8 padB0[0x6F0 - 0xB0];
	Action80040860 action; // 0x6F0
	RwV3d position;        // 0x708
	u8 pad714[0x720 - 0x714];
	RwV3d push; // 0x720
	u8 pad72C[0x73C - 0x72C];
	s32 yaw; // 0x73C
	u8 pad740[0x7C0 - 0x740];
	RwV3d velocity; // 0x7C0
};

extern "C" {
extern const f32 lbl_8042D174; // radians to 16-bit angle units
extern const f32 lbl_8042D178;
extern const f32 lbl_8042D17C;
double atan2(double y, double x);
void fn_80021824(Colli80040860* colli);
Hit80040860* fn_80020FD8(Colli80040860* colli);
Hit80040860* fn_80020BD8(Colli80040860* colli, s32 type);
void* fn_8001F9F8(Colli80040860* colli, u8 key);
f32 fn_801991B4(RwV3d* v);
void fn_801990E0(RwV3d* dst, RwV3d* src);
void fn_8003EB18(Action80040860* action, RwV3d* v);
}

extern "C" void fn_80040860(Player80040860* player)
{
	Object80040860* object;

	fn_80021824(&player->colli);
	Hit80040860* hit = fn_80020FD8(&player->colli);
	object           = hit != NULL ? hit->object : NULL;
	if (object == NULL || (object->unknown6 <= 0 && fn_8001F9F8(&player->colli, 0x14) == NULL)) {
		hit    = fn_80020BD8(&player->colli, 1);
		object = hit != NULL ? hit->object : NULL;
		if (object == NULL) {
			return;
		}
	}
	Action80040860* action = &player->action;
	RwV3d target           = object->position;
	RwV3d offset;
	offset.x = target.x - player->position.x;
	offset.y = target.y - player->position.y;
	offset.z = target.z - player->position.z;
	offset.y = lbl_8042D178;
	if (fn_801991B4(&offset) > lbl_8042D17C) {
		fn_801990E0(&offset, &offset);
		offset.x *= -fn_801991B4(&player->velocity);
		offset.y *= -fn_801991B4(&player->velocity);
		offset.z *= -fn_801991B4(&player->velocity);
		player->push.x     = offset.x;
		player->push.y     = offset.y;
		player->push.z     = offset.z;
		s32 yaw            = lbl_8042D174 * (f32)atan2(-offset.z, -offset.x);
		action->angle[1]   = yaw;
		player->yaw        = yaw;
		player->velocity.x = offset.x;
		player->velocity.y = offset.y;
		player->velocity.z = offset.z;
		fn_8003EB18(action, &player->velocity);
	}
}
