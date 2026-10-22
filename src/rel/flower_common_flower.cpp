#include "types.h"

// TObjFlowerCommon::SetPosition_Flower (the PS2 build's name, by its place in
// the PS2 order): the flower model's frame is turned to the flower's heading,
// raised by its height, scaled by its scale, moved by the head offset kept in
// the module's data and then to the flower's position. A flower of kind 2 does
// the same for its second model, which also follows the position of the node
// frame the flower keeps (its modelling matrix copied).

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	RwV3d right; // 0x00
	u32 flags;   // 0x0C
	RwV3d up;    // 0x10
	u32 pad1;    // 0x1C
	RwV3d at;    // 0x20
	u32 pad2;    // 0x2C
	RwV3d pos;   // 0x30
	u32 pad3;    // 0x3C
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
	u8 unk000[0xB8];
	s32 kind;           // 0x0B8
	u8 unk0BC[0x4];     // 0x0BC
	RwV3d pos;          // 0x0C0
	s32 angX;           // 0x0CC
	s32 angY;           // 0x0D0
	s32 angZ;           // 0x0D4
	f32 scale;          // 0x0D8
	u8 unk0DC[0x4];     // 0x0DC
	f32 height;         // 0x0E0
	u8 unk0E4[0x18];    // 0x0E4
	RpClump* model;     // 0x0FC
	u8 unk100[0xC];     // 0x100
	RpClump* model2;    // 0x10C
	u8 unk110[0xC];     // 0x110
	RwFrame* nodeFrame; // 0x11C
} FlowerCommon;

extern "C" const RwV3d AxisY;
extern "C" const f32 flowerCommonOne[1];
extern "C" const f32 flowerBound2[1];
extern "C" RwMatrixTag* pCurrentMatrix;
// the offset of the flower's head
extern "C" f32 flowerHeadX;
extern "C" f32 flowerHeadY;
extern "C" f32 flowerHeadZ;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EC30(RwFrame* frame, RwV3d* scale, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);

extern "C" void SetPosition_Flower__16TObjFlowerCommonFv(FlowerCommon* flower)
{
	RwFrame* frame = flower->model->frame;
	RwV3d up;
	RwV3d head;
	RwV3d scale;
	RwV3d node;

	fn_80195790(&frame->modelling, &AxisY, flowerCommonOne[0] - fn_800D7AE4(flower->angY),
	    fn_800D7B00(flower->angY), 0);
	up.x = up.z = flowerBound2[0];
	up.y        = flower->height;
	fn_8019EB94(frame, &up, 1);
	scale.x = scale.y = scale.z = flower->scale;
	fn_8019EC30(frame, &scale, 1);
	head.x = flowerHeadX;
	head.y = flowerHeadY;
	head.z = flowerHeadZ;
	fn_8019EB94(frame, &head, 1);
	fn_8019EB94(frame, &flower->pos, 2);
	if (flower->kind == 2) {
		RwMatrixTag matrix = flower->nodeFrame->modelling;

		node  = *(&matrix == NULL ? &pCurrentMatrix->pos : &matrix.pos);
		frame = flower->model2->frame;
		fn_80195790(&frame->modelling, &AxisY, flowerCommonOne[0] - fn_800D7AE4(flower->angY),
		    fn_800D7B00(flower->angY), 0);
		fn_8019EB94(frame, &up, 1);
		fn_8019EC30(frame, &scale, 1);
		fn_8019EB94(frame, &head, 1);
		fn_8019EB94(frame, &node, 1);
		fn_8019EB94(frame, &flower->pos, 2);
	}
}
