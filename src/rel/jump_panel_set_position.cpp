#include "types.h"

// TObjJumppanel::SetPosition (the PS2 build's name, by its place in the PS2
// order; jumpPanelSetPosition here): the panel's frame is tilted about X,
// turned to the panel's heading, given half a turn about Y and moved to the
// panel's position.

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

typedef struct JumpPanel {
	u8 unk00[0xC8];
	RwV3d pos;      // 0xC8
	s32 angX;       // 0xD4
	s32 angY;       // 0xD8
	s32 angZ;       // 0xDC
	f32 tilt;       // 0xE0
	u8 unkE4[0x8];  // 0xE4
	RpClump* model; // 0xEC
} JumpPanel;

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const f32 jumpPanelOne[1];
extern "C" const f32 jumpPanelTwo[1];
extern "C" const f32 jumpPanelZero[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019ED68(RwFrame* frame, const RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);

extern "C" void jumpPanelSetPosition(JumpPanel* object)
{
	RwFrame* frame = object->model->frame;

	fn_8019ED68(frame, &AxisX, object->tilt, 0);
	fn_80195790(&frame->modelling, &AxisY, jumpPanelOne[0] - fn_800D7AE4(object->angY),
	    fn_800D7B00(object->angY), 2);
	fn_80195790(&frame->modelling, &AxisY, jumpPanelTwo[0], jumpPanelZero[0], 1);
	fn_8019EB94(frame, &object->pos, 2);
}
