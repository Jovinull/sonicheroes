#include "types.h"

// TObjFlowerCommon::SetPosition_Stem() (the PS2 build's name, by its place in
// the PS2 order): the frame of the model the flower added to the world is
// turned to the flower's heading, scaled by its scale and moved to its
// position.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct RwFrame {
	u8 unk00[0x10];
	RwMatrixTag modelling; // 0x10
} RwFrame;

typedef struct RpClump {
	u8 unk0[0x4];
	RwFrame* frame; // 0x04
} RpClump;

typedef struct FlowerCommon {
	u8 unk000[0xC0];
	RwV3d pos;           // 0x0C0
	s32 angX;            // 0x0CC
	s32 angY;            // 0x0D0
	s32 angZ;            // 0x0D4
	f32 scale;           // 0x0D8
	u8 unk0DC[0x24];     // 0x0DC
	RpClump* worldModel; // 0x100
} FlowerCommon;

extern "C" const RwV3d AxisY;
extern "C" const f32 flowerCommonOne[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EC30(RwFrame* frame, RwV3d* scale, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);

extern "C" void SetPosition_Stem__16TObjFlowerCommonFv(FlowerCommon* flower)
{
	RwFrame* frame = flower->worldModel->frame;
	RwV3d scale;

	fn_80195790(&frame->modelling, &AxisY, flowerCommonOne[0] - fn_800D7AE4(flower->angY),
	    fn_800D7B00(flower->angY), 0);
	scale.x = scale.y = scale.z = flower->scale;
	fn_8019EC30(frame, &scale, 1);
	fn_8019EB94(frame, &flower->pos, 2);
}
