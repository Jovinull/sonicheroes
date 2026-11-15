// Per-frame update of a spinning menu decoration (HYPOTHESIS; names inferred): kills itself (flag
// 0x1 at 0x4) unless the player it follows (lbl_80303DC8[0x29]) is in state 9. Otherwise advances
// its timer (0x2A), bobs the value at 0x50 around 0x400 (sine of timer << 9 scaled by
// lbl_8042EC94), adds the step at 0x5C to 0x54 and, when it has a model (0x64), rotates the
// model's frame about X and Y by the angles at 0x44 and 0x48 and moves it by the vector at 0x2C.
#include "game/matrix.h"

#define RW_COMBINE_REPLACE    0
#define RW_COMBINE_POSTCONCAT 2

struct Player80122658 {
	u8 pad0[0x154];
	s32 state; // 0x154
};

struct Frame80122658 {
	u8 pad0[0x10];
	RwMatrixTag modelling; // 0x10
};

struct Model80122658 {
	u8 pad0[0x4];
	Frame80122658* frame; // 0x4
};

struct Spinner80122658 {
	u8 pad0[0x4];
	u16 flags; // 0x4
	u8 pad6[0x29 - 0x6];
	s8 player;  // 0x29
	s16 timer;  // 0x2A
	RwV3d move; // 0x2C
	u8 pad38[0x44 - 0x38];
	s32 angleX; // 0x44
	s32 angleY; // 0x48
	u8 pad4C[0x50 - 0x4C];
	s32 bob;   // 0x50
	s32 value; // 0x54
	u8 pad58[0x5C - 0x58];
	s32 step; // 0x5C
	u8 pad60[0x64 - 0x60];
	Model80122658* model; // 0x64
};

extern "C" {
extern Player80122658* lbl_80303DC8[];
extern f32 lbl_8042EC90; // 1.0f
extern f32 lbl_8042EC94;
// HYPOTHESIS: integer-angle sine and cosine, RwMatrixRotateOneMinusCosineSine and RwFrameTranslate.
f32 fn_800D7B00(s32 angle);
f32 fn_800D7AE4(s32 angle);
void fn_80195790(RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sine, s32 combine);
void fn_8019EB94(Frame80122658* frame, RwV3d* translation, s32 combine);

void fn_80122658(Spinner80122658* spinner)
{
	Player80122658* player = lbl_80303DC8[spinner->player];

	if (player == 0 || player->state != 9) {
		spinner->flags |= 0x1;
		return;
	}
	spinner->timer++;
	spinner->bob = (s32)(lbl_8042EC94 * fn_800D7B00(spinner->timer << 9)) + 0x400;
	spinner->value += spinner->step;
	if (spinner->model != 0) {
		Frame80122658* frame = spinner->model->frame;
		f32 sine;

		sine = fn_800D7B00(spinner->angleX);
		fn_80195790(&frame->modelling, &AxisX, lbl_8042EC90 - fn_800D7AE4(spinner->angleX), sine,
		    RW_COMBINE_REPLACE);
		sine = fn_800D7B00(spinner->angleY);
		fn_80195790(&frame->modelling, &AxisY, lbl_8042EC90 - fn_800D7AE4(spinner->angleY), sine,
		    RW_COMBINE_POSTCONCAT);
		fn_8019EB94(frame, &spinner->move, RW_COMBINE_POSTCONCAT);
	}
}
}
