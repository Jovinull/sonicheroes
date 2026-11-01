#include "types.h"

// TObjJumppanel::JumppanelPlayer (the PS2 build's name), the same in the
// thirteen stage modules that share the engine core. While the game runs, the
// panel's space is worked out once (its pitch about X, its yaw, its position;
// the inverse is kept). Each sled whose position falls in the panel's box takes
// the jump speed and the panel's jump time; each player not waiting whose
// position falls in it is launched with the panel's speed and angle and waits
// four frames. Both sound and rumble the pad.

typedef struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
} RwV3d;

typedef struct sAngle {
	s32 x;
	s32 y;
	s32 z;
} sAngle;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct JumppanelSled {
	u8 unk000[0x104];
	RwV3d pos; // 0x104
	u8 unk110[0x48];
	f32 speed; // 0x158
	u8 unk15C[0x40];
	s32 team; // 0x19C
	u8 unk1A0[0x160];
	s32 jumpTime; // 0x300
} JumppanelSled;

typedef struct JumppanelTeam {
	u8 unk000[0x14C];
	s8 pad; // 0x14C
} JumppanelTeam;

typedef struct JumppanelPlayerTask {
	u8 unk000[0x25E];
	s8 pad; // 0x25E
} JumppanelPlayerTask;

typedef struct Jumppanel {
	u8 unk00[0xBC];
	s8 wait[8];   // 0xBC
	s16 jumpTime; // 0xC4
	u8 unkC6[0x2];
	RwV3d pos;  // 0xC8
	sAngle ang; // 0xD4
	f32 pitch;  // 0xE0
	f32 speedH; // 0xE4
	f32 speedV; // 0xE8
	u8 unkEC[0x4];
	RwMatrixTag* inverse; // 0xF0
} Jumppanel;

extern "C" u8* lbl_8042C180;
extern "C" void* lbl_8042C388;
extern "C" JumppanelSled* lbl_80288E0C[4];
extern "C" JumppanelTeam* lbl_80303DC8[];
extern "C" JumppanelPlayerTask* lbl_802AD0D0[];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const f32 jumpPanelPitchOffset;
extern "C" const f32 jumpPanelOne[1];
extern "C" const f32 jumpPanelBound1[1];
extern "C" const f32 jumpPanelSledHalfHeight;
extern "C" const f32 jumpPanelFront;
extern "C" const f32 jumpPanelSledBack;
extern "C" const f32 jumpPanelBound0[1];
extern "C" const f32 jumpPanelPlayerHalfHeight;
extern "C" const f32 jumpPanelZero[1];
extern "C" f32 jumpPanelSledSpeed;

extern "C" void* __nw__FUl(u32 size);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195A74(RwMatrixTag* matrix, const RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, const RwV3d* translation, s32 combine);
extern "C" void fn_80195B5C(RwMatrixTag* out, const RwMatrixTag* in);
extern "C" void fn_8019941C(RwV3d* out, const RwV3d* in, s32 count, const RwMatrixTag* matrix);
extern "C" s32 fn_8003E2E4(s32 player, s32 kind, RwV3d* position, s32 arg3);
extern "C" void fn_800E04F4(s32 player, RwV3d* speed, sAngle* ang, s32 time);
extern "C" void fn_800B52E8(void* sound, s32 id, s32 a, s32 b);
extern "C" void fn_8001F674(s32 team, s32 kind, s32 time, s32 arg3);

extern "C" void JumppanelPlayer__13TObjJumppanelFv(Jumppanel* object)
{
	JumppanelSled* sled;
	s32 i;

	if ((s8)lbl_8042C180[0x22] != 0 || (s8)lbl_8042C180[0x20] != 0 || (s8)lbl_8042C180[0x21] != 0) {
		return;
	}
	if (object->inverse == NULL) {
		RwMatrixTag matrix;
		RwMatrixTag* inverse;

		object->inverse = (RwMatrixTag*)__nw__FUl(0x40);
		inverse         = object->inverse;
		fn_80195A74(&matrix, &AxisX, jumpPanelPitchOffset + object->pitch, 0);
		fn_80195790(&matrix, &AxisY, jumpPanelOne[0] - fn_800D7AE4(object->ang.y),
		    fn_800D7B00(object->ang.y), 2);
		fn_80196050(&matrix, &object->pos, 2);
		fn_80195B5C(inverse, &matrix);
	}
	for (i = 0; i < 4; i++) {
		sled = lbl_80288E0C[i];

		if (sled == NULL) {
			continue;
		}
		RwV3d sledPos = sled->pos;

		fn_8019941C(&sledPos, &sledPos, 1, object->inverse);
		if ((f32)__fabs(sledPos.x) > jumpPanelBound1[0]
		    || (f32)__fabs(sledPos.y) > jumpPanelSledHalfHeight || sledPos.z > jumpPanelFront
		    || sledPos.z < jumpPanelSledBack) {
			continue;
		}
		sled->speed    = jumpPanelSledSpeed;
		sled->jumpTime = object->jumpTime;
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x101D, 0, 0);
		}
		fn_8001F674(lbl_80303DC8[sled->team]->pad, 4, 0xF, 0);
	}
	for (i = 0; i < 8; i++) {
		RwV3d playerPos;

		if (object->wait[i] > 0) {
			continue;
		}
		if (fn_8003E2E4(i, 1, &playerPos, 0) == 0) {
			continue;
		}
		fn_8019941C(&playerPos, &playerPos, 1, object->inverse);
		if (playerPos.z > jumpPanelFront || playerPos.z < jumpPanelBound0[0]
		    || (f32)__fabs(playerPos.x) > jumpPanelBound1[0]
		    || (f32)__fabs(playerPos.y) > jumpPanelPlayerHalfHeight) {
			continue;
		}
		RwV3d speed;

		speed.x = object->speedH;
		speed.y = object->speedV;
		speed.z = jumpPanelZero[0];
		fn_800E04F4(i, &speed, &object->ang, object->jumpTime);
		object->wait[i] = 4;
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x101D, 0, 0);
		}
		fn_8001F674(lbl_802AD0D0[i]->pad, 4, 0xF, 0);
	}
}
