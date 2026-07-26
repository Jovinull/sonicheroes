#include "types.h"

// The pair of two-way choice widgets on the attract mode panel: reset one,
// grey out the options it is not on, select the one it is, and rebuild the
// three emitters that mark it.
//
// The translation unit runs from fn_1_F06C at 0xF06C to the end of fn_1_F38C
// at 0xF454, and owns .data 0x7838 to 0x7880. That block is the only private
// data the run touches, and nothing outside the run reads it, which is what
// makes these five functions a unit. The run before and the run after both
// reach lbl_1_data_3060, so this is an island between them rather than a cut
// out of either.
//
// The object is read from the code alone. The panel keeps two of everything
// side by side: a state at 0x234, a widget of 0x8C bytes at 0x23C, and two
// pointer slots at 0x354 and 0x368, all indexed the same way.
//
// fn_1_F118 leaves its side index uninitialised when the argument it switches
// on is neither 0 nor 1. That is what the original does, and writing it any
// other way costs the two bare compares it opens with.

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct Widget {
	u8 padding[0x8C];
} Widget;

typedef struct Emitter {
	s32 frame;   // 0x00
	Vec3 offset; // 0x04
	s32 count;   // 0x10
} Emitter;

typedef struct Panel {
	u8 unk0[0x234];   // 0x000
	s32 state[2];     // 0x234
	Widget choice[2]; // 0x23C
	void* marker[2];  // 0x354
	u8 unk35C[0xC];   // 0x35C
	void* counter[2]; // 0x368
} Panel;

extern "C" void fn_8001867C(void* object);
extern "C" void fn_1_5994(Vec3* dst, const Vec3* src);
extern "C" void fn_1_63A8(void* marker, Emitter* emitter);
extern "C" void fn_1_6ABC(Emitter* emitter);
extern "C" void fn_1_ECC0(void* counter, s32 value);
extern "C" void fn_1_119E0(Widget* widget, s32 option);
extern "C" void fn_1_120B4(Widget* widget);
extern "C" void fn_1_120C4(Widget* widget, s32 option);

extern "C" void fn_1_F358(Panel* panel, s32 index);
extern "C" void fn_1_F38C(Panel* panel, s32 index);

#pragma dont_inline on

static Vec3 lbl_1_data_7838[2][3]
    = { { { 0.0f, 2.9f, 6.0f }, { 0.0f, 2.9f, 6.0f }, { 0.0f, 2.9f, 6.0f } },
	      { { 0.0f, -13.0f, 6.0f }, { 0.0f, -13.0f, 6.0f }, { 0.0f, -13.0f, 6.0f } } };

extern "C" void fn_1_F06C(Panel* panel, s32 index)
{
	Widget* widget;
	s32 side;

	side = 0;
	if (index == 0) {
		side = 1;
	}
	if (index == 1) {
		side = 0;
	}

	widget = &panel->choice[side];
	fn_1_120B4(widget);
	fn_1_120C4(widget, 0);
	fn_1_120C4(widget, 1);
	fn_1_120C4(widget, 2);
	fn_1_120C4(widget, 3);
	fn_1_119E0(widget, panel->state[side]);
}

extern "C" void fn_1_F118(Panel* panel, s32 index)
{
	Widget* widget;
	s32 side;
	s32 state;
	s32 enabled[4];

	if (index == 0) {
		side = 1;
	}
	if (index == 1) {
		side = 0;
	}

	state  = panel->state[index];
	widget = &panel->choice[side];
	fn_1_120B4(widget);

	if (state != 0) {
		fn_1_120C4(widget, 0);
		enabled[0] = 1;
	} else {
		enabled[0] = 0;
	}
	if (state != 1) {
		fn_1_120C4(widget, 1);
		enabled[1] = 1;
	} else {
		enabled[1] = 0;
	}
	if (state != 2) {
		fn_1_120C4(widget, 2);
		enabled[2] = 1;
	} else {
		enabled[2] = 0;
	}
	if (state != 3) {
		fn_1_120C4(widget, 3);
		enabled[3] = 1;
	} else {
		enabled[3] = 0;
	}

	if (panel->state[index] != panel->state[side] && enabled[panel->state[side]] != 0) {
		fn_1_119E0(widget, panel->state[side]);
	} else {
		if (state == 0) {
			fn_1_119E0(widget, 1);
			panel->state[side] = 1;
		} else {
			fn_1_119E0(widget, 0);
			panel->state[side] = 0;
		}
		fn_1_F38C(panel, side);
	}
}

extern "C" void fn_1_F298(Panel* panel)
{
	s32 state = panel->state[0];

	fn_1_120B4(&panel->choice[1]);
	if (state != 0) {
		fn_1_120C4(&panel->choice[1], 0);
	}
	if (state != 1) {
		fn_1_120C4(&panel->choice[1], 1);
	}
	if (state != 2) {
		fn_1_120C4(&panel->choice[1], 2);
	}
	if (state != 3) {
		fn_1_120C4(&panel->choice[1], 3);
	}

	if (state == 0) {
		fn_1_119E0(&panel->choice[1], 1);
		panel->state[1] = 1;
	} else {
		fn_1_119E0(&panel->choice[1], 0);
		panel->state[1] = 0;
	}
}

extern "C" void fn_1_F358(Panel* panel, s32 index)
{
	if (panel->marker[index] != NULL) {
		fn_8001867C(panel->marker[index]);
	}
}

extern "C" void fn_1_F38C(Panel* panel, s32 index)
{
	Emitter emitter;
	s32 i;

	fn_1_F358(panel, index);

	if (panel->marker[index] != NULL) {
		for (i = 0; i != 3; i++) {
			fn_1_6ABC(&emitter);
			emitter.frame = i + panel->state[index] * 3;
			fn_1_5994(&emitter.offset, &lbl_1_data_7838[index][i]);
			emitter.count = 3;
			fn_1_63A8(panel->marker[index], &emitter);
		}
	}

	if (panel->counter[index] != NULL) {
		fn_1_ECC0(panel->counter[index], panel->state[index] + 1);
	}
}
