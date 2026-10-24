#include "types.h"

// TObjHintRing::SetPosition (the PS2 build's name, by its place in the PS2
// order): both models are turned to the ring's heading; the ring goes to the
// ring's position, the inside model a little forward of it and raised by the
// room its scale leaves, and is scaled by that scale.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwFrame RwFrame;

typedef struct RpClump {
	u8 unk0[0x4];
	RwFrame* frame; // 0x04
} RpClump;

typedef struct HintRing {
	u8 unk00[0x30];
	RwV3d pos;       // 0x30
	u8 unk3C[0x4];   // 0x3C
	f32 angle;       // 0x40
	u8 unk44[0x18];  // 0x44
	RpClump* ring;   // 0x5C
	u8 unk60[0x8];   // 0x60
	RpClump* inside; // 0x68
} HintRing;

extern "C" const RwV3d AxisY;
extern "C" const f32 hintBallOne[1];
extern "C" const f32 hintringInsideLift[1];
extern "C" const f32 hintringInsideForward[1];
extern "C" f32 hintringInsideScale;

extern "C" void fn_8019ED68(RwFrame* frame, const RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);
extern "C" void fn_8019EC30(RwFrame* frame, RwV3d* scale, s32 combine);

extern "C" void SetPosition__12TObjHintRingFv(HintRing* ring)
{
	RwFrame* frame = ring->ring->frame;

	fn_8019ED68(frame, &AxisY, ring->angle, 0);
	fn_8019EB94(frame, &ring->pos, 2);
	frame = ring->inside->frame;
	fn_8019ED68(frame, &AxisY, ring->angle, 0);
	RwV3d pos = ring->pos;
	pos.y     = pos.y + hintringInsideLift[0] * (hintBallOne[0] - hintringInsideScale);
	pos.z     = pos.z + hintringInsideForward[0];
	fn_8019EB94(frame, &pos, 2);
	RwV3d scale;
	scale.x = scale.y = scale.z = hintringInsideScale;
	fn_8019EC30(frame, &scale, 1);
}
