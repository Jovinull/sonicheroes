#include "game/matrix.h"

// fn_800F7FE4 with a faster spin (0xE38 a frame) and the offset lbl_8023A72C: animates a
// short-lived effect for twelve frames (+0x2A; it then ends with flag 0x1, +0x4): its
// height scale (+0x2C) eases toward lbl_8042E560 by lbl_8042E55C for six frames and then toward
// lbl_8042E57C by lbl_8042E580, its alpha (+0x29) rises by 0x40 until frame 7 and then falls by
// 0x30, and it spins (+0x30). Its clump frame (+0x34, +0x4) is placed at +0x44,
// offset by lbl_8023A72C, rotated by Z (+0x40), X (+0x38) and Y (+0x30) and scaled to
// (1, scale, 1). HYPOTHESIS: RwFrameTranslate/RwFrameScale (fn_8019EB94/fn_8019EC30); the effect
// is UNKNOWN.

struct Frame800F83D4 {
	u8 pad0[0x10];
	RwMatrixTag matrix; // 0x10
};

struct Clump800F83D4 {
	u8 pad0[0x4];
	Frame800F83D4* frame; // 0x4
};

struct Effect800F83D4 {
	u8 pad0[0x4];
	u16 flags; // 0x4
	u8 pad6[0x29 - 0x6];
	u8 alpha;             // 0x29
	s16 frame;            // 0x2A
	f32 scale;            // 0x2C
	s32 yaw;              // 0x30
	Clump800F83D4* clump; // 0x34
	s32 pitch;            // 0x38
	u8 pad3C[0x40 - 0x3C];
	s32 roll;       // 0x40
	RwV3d position; // 0x44
};

extern "C" {
extern const RwV3d lbl_8023A72C;
extern const f32 lbl_8042E55C;
extern const f32 lbl_8042E560; // 1.0f
extern const f32 lbl_8042E57C;
extern const f32 lbl_8042E580;
f32 fn_800D7AE4(s32 angle);
f32 fn_800D7B00(s32 angle);
RwMatrixTag* fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
void fn_8019EB94(Frame800F83D4* frame, const RwV3d* translation, s32 combine);
void fn_8019EC30(Frame800F83D4* frame, const RwV3d* scale, s32 combine);
}

f32 AdjustFloat(f32 value, f32 target, f32 step);

extern "C" void fn_800F83D4(Effect800F83D4* effect)
{
	effect->frame++;
	if (effect->frame >= 12) {
		effect->flags |= 1;
		return;
	}
	if (effect->frame > 5) {
		effect->scale = AdjustFloat(effect->scale, lbl_8042E57C, lbl_8042E580);
	} else {
		effect->scale = AdjustFloat(effect->scale, lbl_8042E560, lbl_8042E55C);
	}
	if (effect->frame > 7) {
		s32 alpha = effect->alpha;
		alpha -= 0x30;
		if (alpha < 0) {
			alpha = 0;
		}
		effect->alpha = alpha;
	} else {
		s32 alpha = effect->alpha;
		alpha += 0x40;
		if (alpha > 0xFF) {
			alpha = 0xFF;
		}
		effect->alpha = alpha;
	}
	effect->yaw += 0xE38;
	Frame800F83D4* frame = effect->clump->frame;
	fn_8019EB94(frame, &effect->position, 0);
	RwV3d offset = lbl_8023A72C;
	fn_8019EB94(frame, &offset, 1);
	fn_80195790(&frame->matrix, &AxisZ, lbl_8042E560 - fn_800D7AE4(effect->roll),
	    fn_800D7B00(effect->roll), 1);
	fn_80195790(&frame->matrix, &AxisX, lbl_8042E560 - fn_800D7AE4(effect->pitch),
	    fn_800D7B00(effect->pitch), 1);
	fn_80195790(&frame->matrix, &AxisY, lbl_8042E560 - fn_800D7AE4(effect->yaw),
	    fn_800D7B00(effect->yaw), 1);
	RwV3d scale;
	scale.x = lbl_8042E560;
	scale.y = effect->scale;
	scale.z = lbl_8042E560;
	fn_8019EC30(frame, &scale, 1);
}
