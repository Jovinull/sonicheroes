// Launches a player toward its target point (+0x5F0): keeps a copy of the target (+0x9CC), solves
// the jump with CalcV2_TimeGP (peak 10 above the higher of the player and the target, gravity
// +0x8A0) into the motion velocity (+0x720) and the speed (+0x7C0) with the jump time (+0x9C8),
// keeps the velocity (+0x9D8), faces the player along it (the returned yaw turned by half a turn,
// SetPlayerYAngle) in both angle copies (+0x6FC and +0x738), and resets the two acceleration
// vectors (+0x72C and +0x7B4) to (0, -gravity, 0). HYPOTHESIS: a spring/launcher jump; the field
// names are UNKNOWN.
#include "game/miscs.h"

struct Angle8008A2D4 {
	s32 x;
	s32 y;
	s32 z;
};

struct Motion8008A2D4 {
	RwV3d velocity;      // 0x0 (player +0x720)
	RwV3d acceleration;  // 0xC
	Angle8008A2D4 angle; // 0x18
};

struct Player8008A2D4 {
	u8 pad0[0x5F0];
	RwV3d target; // 0x5F0
	u8 pad5FC[0x6FC - 0x5FC];
	Angle8008A2D4 angle; // 0x6FC
	RwV3d position;      // 0x708
	u8 pad714[0x720 - 0x714];
	Motion8008A2D4 motion; // 0x720
	u8 pad744[0x7B4 - 0x744];
	RwV3d acceleration; // 0x7B4
	RwV3d speed;        // 0x7C0
	u8 pad7CC[0x8A0 - 0x7CC];
	f32 gravity; // 0x8A0
	u8 pad8A4[0x9C8 - 0x8A4];
	s32 jumpTime;       // 0x9C8
	RwV3d jumpTarget;   // 0x9CC
	RwV3d jumpVelocity; // 0x9D8
};

extern "C" {
extern f32 lbl_8042D888; // 10.0f
extern f32 lbl_8042D878; // 0.0f

void fn_8008A2D4(Player8008A2D4* p)
{
	Motion8008A2D4* motion = &p->motion;
	RwV3d* target          = &p->target;
	f32 height;
	s32 yaw;
	s32 angle;

	p->jumpTarget = *target;
	height        = p->position.y > target->y ? p->position.y : target->y;
	height += lbl_8042D888;
	CalcV2_TimeGP(
	    &p->position, target, height, p->gravity, &motion->velocity, &p->speed, &yaw, &p->jumpTime);
	p->jumpVelocity = motion->velocity;
	angle           = SetPlayerYAngle(yaw ^ 0x8000);
	p->angle.y = motion->angle.y = angle;
	p->angle.z = motion->angle.z = 0;
	p->angle.x = motion->angle.x = 0;
	motion->acceleration.x = motion->acceleration.z = p->acceleration.x = p->acceleration.z
	    = lbl_8042D878;
	motion->acceleration.y = p->acceleration.y = -p->gravity;
}
}
