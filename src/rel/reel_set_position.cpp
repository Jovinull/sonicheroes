#include "types.h"

// TObjReel::SetPosition (the PS2 build's name, by its place in the PS2 order;
// reelSetPosition here): the reel's frame is turned to its heading and moved
// to its position; the rope (the grandchild frame) is stretched to the reel's
// length (a minimum height when the length is zero) and the hook below it
// moved down by the length, undoing the stretch.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

struct RwFrame {
	u8 unk00[0x10];
	RwMatrixTag modelling; // 0x10
};

typedef struct RpClump {
	u8 unk0[0x4];
	RwFrame* frame; // 0x04
} RpClump;

typedef struct Reel {
	u8 unk00[0xC4];
	f32 length;     // 0xC4
	u8 unkC8[0x14]; // 0xC8
	RwV3d pos;      // 0xDC
	s32 angX;       // 0xE8
	s32 angY;       // 0xEC
	s32 angZ;       // 0xF0
	RpClump* model; // 0xF4
} Reel;

extern "C" const RwV3d AxisY;
extern "C" const f32 reelOne[1];
extern "C" const f32 reelZero[1];
extern "C" const f32 reelHeightScale[1];
extern "C" const f32 reelMinHeight[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019EC30(RwFrame* frame, RwV3d* scale, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);
RwFrame* objRwFrameGetChildFrame(RwFrame* frame, RwFrame* after);

extern "C" void reelSetPosition(Reel* object)
{
	RwFrame* frame = object->model->frame;
	RwV3d scale;
	RwV3d offset;

	fn_80195790(&frame->modelling, &AxisY, reelOne[0] - fn_800D7AE4(object->angY),
	    fn_800D7B00(object->angY), 0);
	fn_8019EB94(frame, &object->pos, 2);
	frame   = objRwFrameGetChildFrame(objRwFrameGetChildFrame(frame, NULL), NULL);
	scale.x = scale.z = reelOne[0];
	if (reelZero[0] != object->length) {
		scale.y = reelHeightScale[0] * object->length;
	} else {
		scale.y = reelMinHeight[0];
	}
	fn_8019EC30(frame, &scale, 0);
	frame    = objRwFrameGetChildFrame(frame, NULL);
	offset.x = offset.z = reelZero[0];
	offset.y            = -object->length;
	fn_8019EB94(frame, &offset, 0);
	scale.y = reelOne[0] / scale.y;
	fn_8019EC30(frame, &scale, 2);
}
