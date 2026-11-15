#include "game/matrix.h"

// Places the hit-effect ball between a player and the objects it touches (HYPOTHESIS: the team
// blast or spin attack spark; see EffBall): not for a team hidden in mode switch 0x1F of
// lbl_8042C180, and only in action 0x3B or with flag 2 (+0x770). For every hit of kind `kind`
// (fn_800208CC on the collision block +0x28), the first one with a ball record (+0x8E0) builds a
// matrix at the frame position (+0x38, +0x8) turned by the angles between the players
// (SetEffBallAnglesByDifferenceOfPlayersPositions: Y then X, in degrees times lbl_8042D280) or
// else by the player's angles (Z, X, Y: +0x704, +0x6FC, +0x700) and passes it to fn_800F6D08;
// each hit then goes to fn_800F4880 with the hit object's position (+0x60).

struct sRealAngle3 {
	f32 x, y, z;
};

struct Frame8004852C {
	u8 pad0[0x8];
	RwV3d position; // 0x8
};

struct Object8004852C {
	u8 pad0[0x60];
	RwV3d position; // 0x60
};

struct Hit8004852C {
	u8 pad0[0x4];
	Object8004852C* object; // 0x4
};

struct Player8004852C {
	u8 pad0[0x28];
	u8 colli[0x38 - 0x28]; // 0x28
	Frame8004852C* frame;  // 0x38
	u8 pad3C[0x6F0 - 0x3C];
	s16 action; // 0x6F0
	u8 pad6F2[0x6FC - 0x6F2];
	s32 angleX; // 0x6FC
	s32 angleY; // 0x700
	s32 angleZ; // 0x704
	u8 pad708[0x760 - 0x708];
	s8 number; // 0x760
	u8 pad761[0x770 - 0x761];
	s16 flags; // 0x770
	u8 pad772[0x8E0 - 0x772];
	void* ball; // 0x8E0
	u8 pad8E4[0x9BC - 0x8E4];
	s8 team; // 0x9BC
};

struct ModeSwitch8004852C {
	u8 pad0[0x1F];
	s8 hidden; // 0x1F
};

extern "C" {
extern ModeSwitch8004852C* lbl_8042C180;
extern const f32 lbl_8042D208; // 1.0f
extern const f32 lbl_8042D280; // degrees to 16-bit angle units
f32 fn_800D7AE4(s32 angle);
f32 fn_800D7B00(s32 angle);
RwMatrixTag* fn_80195790(RwMatrixTag* matrix, const RwV3d* axis, f32 cosine, f32 sine, s32 mode);
RwMatrixTag* fn_80196050(RwMatrixTag* matrix, const RwV3d* position, s32 mode);
Hit8004852C* fn_800208CC(void* colli, s32 kind);
void fn_800F6D08(RwMatrixTag* matrix);
void fn_800F4880(RwV3d* from, RwV3d* to);
}

s32 SetEffBallAnglesByDifferenceOfPlayersPositions(s32, sRealAngle3*);

// Rotates about `axis` by `degrees` (read again for the sine and the cosine).
static inline void RotateDegrees(RwMatrixTag* matrix, const RwV3d* axis, const f32* degrees)
{
	f32 sine = fn_800D7B00(lbl_8042D280 * *degrees);
	fn_80195790(matrix, axis, lbl_8042D208 - fn_800D7AE4(lbl_8042D280 * *degrees), sine, 1);
}

static inline void RotateAngle(RwMatrixTag* matrix, const RwV3d* axis, const s32* angle)
{
	f32 sine = fn_800D7B00(*angle);
	fn_80195790(matrix, axis, lbl_8042D208 - fn_800D7AE4(*angle), sine, 1);
}

static inline Object8004852C* NextHit(Player8004852C* player, s32 kind)
{
	Hit8004852C* hit = fn_800208CC(player->colli, kind);

	return hit != NULL ? hit->object : NULL;
}

extern "C" void fn_8004852C(Player8004852C* player, s32 kind)
{
	// Unsigned mask, signed test: the retail nor/and pair and cmpwi (an s32 mask fuses to andc).
	u32 mask = ~(1 << player->team);
	if ((s32)(mask & lbl_8042C180->hidden) != 0) {
		return;
	}
	if (player->action != 0x3B && !(player->flags & 2)) {
		return;
	}
	void* ball = player->ball;
	Object8004852C* object;
	while ((object = NextHit(player, kind)) != NULL) {
		if (ball != NULL) {
			RwMatrixTag matrix;
			sRealAngle3 angle;
			fn_80196050(&matrix, &player->frame->position, 0);
			if (SetEffBallAnglesByDifferenceOfPlayersPositions(player->number, &angle)) {
				RotateDegrees(&matrix, &AxisY, &angle.y);
				RotateDegrees(&matrix, &AxisX, &angle.x);
			} else {
				RotateAngle(&matrix, &AxisZ, &player->angleZ);
				RotateAngle(&matrix, &AxisX, &player->angleX);
				RotateAngle(&matrix, &AxisY, &player->angleY);
			}
			fn_800F6D08(&matrix);
			ball = NULL;
		}
		fn_800F4880(&player->frame->position, &object->position);
	}
}
