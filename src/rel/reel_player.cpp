#include "types.h"

// TObjReel::ReelPlayer (the PS2 build's name, by its place in the PS2 order;
// reelPlayer here). With a player hanging the reel moves (ReelUpAndDown) and,
// while the player still holds on (state 0x1F), keeps it under the hook facing
// the reel; otherwise the player is launched along the reel's direction at
// the reel's launch speed, the reel winds the other way (state 4 for kind 0,
// 2 for kind 1) and lets go. With nobody hanging it moves and looks for one
// (CheckHangedPlayer).

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct ReelPlayerState {
	s16 state; // 0x0
} ReelPlayerState;

typedef struct Reel {
	u8 unk00[0xB8];
	union {         // 0xB8
		u8 replace; // the OBJ_ReplacePlayer part, which has no fields
		s32 state;
	};
	s8 kind;       // 0xBC
	s8 holder;     // 0xBD
	u8 unkBE[0x2]; // 0xBE
	f32 current;   // 0xC0
	u8 unkC4[0xC]; // 0xC4
	s32 pitch;     // 0xD0
	f32 launch;    // 0xD4
	s8 wait;       // 0xD8
	u8 unkD9[0x3]; // 0xD9
	RwV3d pos;     // 0xDC
	sAngle ang;    // 0xE8
} Reel;

extern "C" ReelPlayerState* lbl_802AD090[];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const f32 reelZero[1];
extern "C" const f32 reelOne[1];
extern "C" const f32 reelHookDepth[1];
extern "C" const f32 reelHangDepth[1];
extern "C" const f32 reelLaunchBoost[1];

extern "C" void reelUpAndDown(Reel* object);
extern "C" void reelCheckHangedPlayer(Reel* object);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019947C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);
extern "C" void fn_800E01E4(s32 player, s32 a, s32 angle, s32 b);
extern "C" void fn_800E10B8(s32 player, f32 x, f32 y, f32 z);
extern "C" void objSetPlayerHandlingPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
    void* replace, s32 player, u8 flags, RwV3d* pos, sAngle* ang);

extern "C" void reelPlayer(Reel* object)
{
	RwMatrixTag matrix;

	if (object->holder != -1) {
		reelUpAndDown(object);
		if (lbl_802AD090[object->holder] == NULL) {
			object->holder = -1;
			return;
		}
		if (lbl_802AD090[object->holder]->state == 0x1F) {
			RwV3d pos  = object->pos;
			sAngle ang = object->ang;

			ang.y = 0x4000 - ang.y;
			pos.y = pos.y - (reelHookDepth[0] + (reelHangDepth[0] + object->current));
			objSetPlayerHandlingPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
			    &object->replace, object->holder, 0, &pos, &ang);
			return;
		}
		RwV3d velocity;

		velocity.z = reelLaunchBoost[0] + object->launch;
		velocity.x = velocity.y = reelZero[0];
		fn_80195790(&matrix, &AxisX, reelOne[0] - fn_800D7AE4(object->pitch),
		    fn_800D7B00(object->pitch), 0);
		fn_80195790(&matrix, &AxisY, reelOne[0] - fn_800D7AE4(object->ang.y),
		    fn_800D7B00(object->ang.y), 2);
		fn_8019947C(&velocity, &velocity, 1, &matrix);
		fn_800E01E4(object->holder, 0, object->ang.y, 0);
		fn_800E10B8(object->holder, velocity.x, velocity.y, velocity.z);
		switch (object->kind) {
			case 0:
				object->state = 4;
				break;
			case 1:
				object->state = 2;
				break;
		}
		object->holder = -1;
		object->wait   = 4;
		return;
	}
	reelUpAndDown(object);
	reelCheckHangedPlayer(object);
}
