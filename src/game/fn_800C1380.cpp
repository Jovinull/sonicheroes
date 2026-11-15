#include "types.h"

// Plays the character-intro animation (while fn_80018C7C allows it): when its time (+0x2C) is at
// lbl_8042DE54 it starts by lbl_8042DE5C, clears +0x84 and, for the first team's leader
// (lbl_80303DC8[0], members +0x114 by +0x3B; character +0x9B4), adds that character's start
// (+0x60/+0x6C/+0x78), takes its end (+0x64/+0x70/+0x7C) into +0x8C and its length into +0x88
// (+0x6C, +0x78, or +0x80 + +0x6C - +0x68), and copies +0x34 clamped to 0..99 into +0x38. The time
// then becomes +0x8C and drives the interpolator lbl_8042C3FC (fn_80204144 with fn_800C480C),
// restarting from lbl_8042DE54 once it wraps. HYPOTHESIS: RtAnim helpers; the roles are UNKNOWN.

struct Anim800C1380 {
	u8 pad0[0x2C];
	f32 time; // 0x2C
	u8 pad30[0x34 - 0x30];
	s32 value;   // 0x34
	s32 clamped; // 0x38
	u8 pad3C[0x60 - 0x3C];
	f32 times[9];  // 0x60
	s32 unknown84; // 0x84
	f32 length;    // 0x88
	f32 target;    // 0x8C
};

struct Player800C1380 {
	u8 pad0[0x9B4];
	s32 character; // 0x9B4
};

struct Team800C1380 {
	u8 pad0[0x3B];
	s8 current; // 0x3B
	u8 pad3C[0x114 - 0x3C];
	Player800C1380* members[3]; // 0x114
};

extern "C" {
extern f32 lbl_8042DE54; // 0.0f
extern f32 lbl_8042DE5C;
extern Team800C1380* lbl_80303DC8[4];
extern void* lbl_8042C3FC;
s32 fn_80018C7C(void);
void* fn_800C480C(void* result, void* anim, void* data, f32* time);
void fn_80204144(void* anim, void* callback, f32* time);
void fn_802041EC(void* anim);
void fn_802033F4(void* anim);
}

extern "C" void fn_800C1380(Anim800C1380* a)
{
	if (fn_80018C7C() == 0) {
		return;
	}
	if (lbl_8042DE54 == a->time) {
		a->time += lbl_8042DE5C;
		a->unknown84       = 0;
		Team800C1380* team = lbl_80303DC8[0];
		switch (team->members[team->current]->character) {
			case 0:
				a->time += a->times[0];
				a->target = a->times[1];
				a->length = a->times[3];
				break;
			case 1:
				a->time += a->times[3];
				a->target = a->times[4];
				a->length = a->times[6];
				break;
			case 2:
				a->time += a->times[6];
				a->target = a->times[7];
				a->length = (a->times[8] + a->times[3]) - a->times[2];
				break;
		}
		if (a->value > 99) {
			a->clamped = 99;
		} else if (a->value < 0) {
			a->clamped = 0;
		} else {
			a->clamped = a->value;
		}
	}
	a->time = a->target;
	if (lbl_8042C3FC == NULL) {
		return;
	}
	f32 previous = a->time;
	f32 time     = previous;
	fn_80204144(lbl_8042C3FC, (void*)fn_800C480C, &time);
	a->time = time;
	if (previous > a->time) {
		a->time   = lbl_8042DE54;
		f32 again = a->time;
		fn_80204144(lbl_8042C3FC, (void*)fn_800C480C, &again);
		a->time = again;
	}
	fn_802041EC(lbl_8042C3FC);
	fn_802033F4(lbl_8042C3FC);
}
