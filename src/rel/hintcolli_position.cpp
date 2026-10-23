#include "types.h"

// TObjHintColli's SetMaterial, SetPosition and HintCollisionParameter (the
// PS2 build's names, in its order). SetMaterial does nothing. SetPosition
// scales the area's model by its shape (0: a sphere of the first size; 1: a
// cylinder, its height doubled and turned by its angles; 2: a box of twice the
// sizes, turned by its angles; angles in 65536ths of a turn) and moves it to
// the area's position. HintCollisionParameter gives the collision the sizes.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwFrame RwFrame;

typedef struct RpClump {
	u8 unk0[0x4];
	RwFrame* frame; // 0x04
} RpClump;

typedef struct HintColliShape {
	u8 unk00[0x14];
	f32 a, b, c; // 0x14
} HintColliShape;

typedef struct HintColli {
	u8 unk000[0x30];
	u8 colli[0x10];       // 0x030 (C_COLLI)
	HintColliShape* info; // 0x040
	u8 unk044[0x74];      // 0x044
	RwV3d pos;            // 0x0B8
	f32 angX;             // 0x0C4
	f32 angY;             // 0x0C8
	f32 angZ;             // 0x0CC
	RwV3d size;           // 0x0D0
	u8 unk0DC[0x20];      // 0x0DC
	s32 shape;            // 0x0FC
	RpClump* model;       // 0x100
} HintColli;

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 hintcolliAngleToDegrees[1];
extern "C" const f32 hintcolliTwo[1];

extern "C" void fn_8019EC30(RwFrame* frame, RwV3d* scale, s32 combine);
extern "C" void fn_8019ED68(RwFrame* frame, const RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);
extern "C" void CalcRange__7C_COLLIFv(void* colli);

extern "C" void SetMaterial__13TObjHintColliFv(HintColli* object) { }

extern "C" void SetPosition__13TObjHintColliFv(HintColli* object)
{
	RwFrame* frame = object->model->frame;
	RwV3d scale;

	switch (object->shape) {
		case 0:
			scale.x = scale.y = scale.z = object->size.x;
			fn_8019EC30(frame, &scale, 0);
			break;
		case 1:
			scale.x = scale.z = object->size.x;
			scale.y           = hintcolliTwo[0] * object->size.y;
			fn_8019EC30(frame, &scale, 0);
			fn_8019ED68(frame, &AxisY, hintcolliAngleToDegrees[0] * object->angY, 2);
			fn_8019ED68(frame, &AxisX, hintcolliAngleToDegrees[0] * object->angX, 2);
			fn_8019ED68(frame, &AxisZ, hintcolliAngleToDegrees[0] * object->angZ, 2);
			break;
		case 2:
			scale.x = hintcolliTwo[0] * object->size.x;
			scale.y = hintcolliTwo[0] * object->size.y;
			scale.z = hintcolliTwo[0] * object->size.z;
			fn_8019EC30(frame, &scale, 0);
			fn_8019ED68(frame, &AxisY, hintcolliAngleToDegrees[0] * object->angY, 2);
			fn_8019ED68(frame, &AxisX, hintcolliAngleToDegrees[0] * object->angX, 2);
			fn_8019ED68(frame, &AxisZ, hintcolliAngleToDegrees[0] * object->angZ, 2);
			break;
	}
	fn_8019EB94(frame, &object->pos, 2);
}

extern "C" void HintCollisionParameter__13TObjHintColliFv(HintColli* object)
{
	if (object->info != NULL) {
		object->info->a = object->size.x;
		object->info->b = object->size.y;
		object->info->c = object->size.z;
		CalcRange__7C_COLLIFv(object->colli);
	}
}
