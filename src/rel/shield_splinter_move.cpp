#include "types.h"

// The shield splinter's Disp and Exec (shieldSplinterDisp and
// shieldSplinterExec here; see rel/shield_splinter_dtor.cpp for the class).
// Disp draws one of the two splinter models (by kind) at the splinter's
// scale, spins and position. Exec ends the splinter after 26 frames; until
// then it spins it, lets it fall (its fall speed held at a floor) and moves it.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwFrame RwFrame;

typedef struct SplinterClump {
	u8 unk00[0x4];
	RwFrame* frame; // 0x04
} SplinterClump;

typedef struct Splinter {
	u8 unk00[0x4];
	u16 signal; // 0x04
	u8 unk06[0x22];
	s16 kind;    // 0x28
	s16 timer;   // 0x2A
	RwV3d pos;   // 0x2C
	RwV3d speed; // 0x38
	RwV3d scale; // 0x44
	f32 spinX;   // 0x50
	f32 spinY;   // 0x54
	f32 spinZ;   // 0x58
} Splinter;

extern "C" SplinterClump* shieldSplinterModels[5];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 shieldSplinterSpinX[1];
extern "C" const f32 shieldSplinterSpinY[1];
extern "C" const f32 shieldSplinterSpinZ[1];
extern "C" const f32 shieldSplinterGravity[1];
extern "C" const f32 shieldSplinterMaxFall[1];

extern "C" void fn_8014FF2C(SplinterClump* clump);
extern "C" void fn_8019EB94(RwFrame* frame, const RwV3d* translation, s32 combine);
extern "C" void fn_8019EC30(RwFrame* frame, const RwV3d* scale, s32 combine);
extern "C" void fn_8019ED68(RwFrame* frame, const RwV3d* axis, f32 angle, s32 combine);

extern "C" void shieldSplinterDisp(Splinter* object)
{
	SplinterClump* clump;
	RwFrame* frame;

	if (object->kind == 0) {
		clump = shieldSplinterModels[3];
	} else {
		clump = shieldSplinterModels[4];
	}
	frame = clump->frame;
	fn_8019EC30(frame, &object->scale, 0);
	fn_8019ED68(frame, &AxisX, object->spinX, 2);
	fn_8019ED68(frame, &AxisY, object->spinY, 2);
	fn_8019ED68(frame, &AxisZ, object->spinZ, 2);
	fn_8019EB94(frame, &object->pos, 2);
	fn_8014FF2C(clump);
}

extern "C" void shieldSplinterExec(Splinter* object)
{
	const f32* limit;

	if (object->timer++ > 0x19) {
		object->signal |= 1;
		return;
	}
	object->spinX += shieldSplinterSpinX[0];
	object->spinY -= shieldSplinterSpinY[0];
	object->spinZ += shieldSplinterSpinZ[0];
	object->speed.y += shieldSplinterGravity[0];
	if (object->speed.y < *(limit = shieldSplinterMaxFall)) {
		object->speed.y = *limit;
	}
	object->pos.x += object->speed.x;
	object->pos.y += object->speed.y;
	object->pos.z += object->speed.z;
}
