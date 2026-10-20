#include "types.h"

// TObjItembox::SetPosition (the PS2 build's name; itemBoxSetPosition here):
// the box takes the position its set work carries (when stamped 0x12345678),
// scales its frame (height along y, width along x and z), turns it by its
// angles (spinning about y with the stage timer) and moves it to its position.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwMatrixTag {
	u8 data[0x40];
} RwMatrixTag;

typedef struct RwFrame {
	u8 unk00[0x10];
	RwMatrixTag matrix; // 0x10
} RwFrame;

typedef struct RpClump {
	u8 unk00[0x4];
	RwFrame* frame; // 0x04
} RpClump;

typedef struct ItemBoxWork {
	u32 magic; // 0x00
	RwV3d pos; // 0x04
} ItemBoxWork;

typedef struct ItemBoxFrame {
	u8 unk00[0x30];
	ItemBoxWork* work; // 0x30
} ItemBoxFrame;

typedef struct ItemBox {
	u8 unk00[0x28];
	ItemBoxFrame* frame; // 0x28
	u8 unk2C[0x94];
	RwV3d pos; // 0xC0
	s32 angX;  // 0xCC
	s32 angY;  // 0xD0
	s32 angZ;  // 0xD4
	u8 unkD8[0x8];
	f32 height;     // 0xE0
	f32 width;      // 0xE4
	RpClump* clump; // 0xE8
} ItemBox;

typedef struct GameFrame {
	u8 unk00[0x30];
	s32 frame; // 0x30
} GameFrame;

extern "C" GameFrame* lbl_8042C180;
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 itemBoxOne;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_8019EC30(RwFrame* frame, const RwV3d* scale, s32 combine);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, const RwV3d* translation, s32 combine);

extern "C" void itemBoxSetPosition(ItemBox* object)
{
	ItemBoxWork* work = object->frame->work;

	if (work != NULL && work->magic == 0x12345678) {
		object->pos.x = work->pos.x;
		object->pos.y = work->pos.y;
		object->pos.z = work->pos.z;
	}
	RwFrame* frame = object->clump->frame;
	RwV3d scale;

	RwV3d part;

	scale.x = AxisY.x * object->height;
	scale.y = AxisY.y * object->height;
	scale.z = AxisY.z * object->height;
	part.x  = AxisX.x * object->width;
	part.y  = AxisX.y * object->width;
	part.z  = AxisX.z * object->width;
	scale.x += part.x;
	scale.y += part.y;
	scale.z += part.z;
	part.x = AxisZ.x * object->width;
	part.y = AxisZ.y * object->width;
	part.z = AxisZ.z * object->width;
	scale.x += part.x;
	scale.y += part.y;
	scale.z += part.z;
	fn_8019EC30(frame, &scale, 0);
	s32 spin = lbl_8042C180->frame << 8;

	fn_80195790(&frame->matrix, &AxisY, itemBoxOne - fn_800D7AE4(object->angY + spin),
	    fn_800D7B00(object->angY + spin), 2);
	fn_80195790(&frame->matrix, &AxisX, itemBoxOne - fn_800D7AE4(object->angX),
	    fn_800D7B00(object->angX), 2);
	fn_80195790(&frame->matrix, &AxisZ, itemBoxOne - fn_800D7AE4(object->angZ),
	    fn_800D7B00(object->angZ), 2);
	fn_8019EB94(frame, &object->pos, 2);
}
