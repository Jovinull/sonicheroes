#include "game/gparam.h"

// Advances the challenge counter animation of the HUD (HYPOTHESIS: the team-challenge counter):
// at rest (time +0x2C at lbl_8042DE54, 0) it starts when the first team's challenge count
// (PARAM_CHALLENGE::num[0]) changes: the count is kept (+0x34, shown clamped to 0..99 at
// +0x38), the time steps by lbl_8042DE5C, the wait counter +0x84 is cleared and, by the leading
// member's type (+0x9B4 of team lbl_80303DC8[0]), the time jumps by +0x60/+0x6C/+0x78 with the
// hold point +0x8C and end +0x88 of that part. A running animation waits up to 30 frames at the
// hold point, then steps on and stops at the end. A changed time drives the shared interpolator
// lbl_8042C3FC (fn_80204144 with the callback fn_800C480C, see fn_800C0B04); when it wraps
// back the time restarts at 0.

struct HudCounter800C1554 {
	u8 pad0[0x2C];
	f32 time; // 0x2C
	u8 pad30[0x34 - 0x30];
	s32 count; // 0x34
	s32 shown; // 0x38
	u8 pad3C[0x60 - 0x3C];
	f32 start0; // 0x60
	f32 hold0;  // 0x64
	f32 base1;  // 0x68
	f32 start1; // 0x6C
	f32 hold1;  // 0x70
	u8 pad74[0x78 - 0x74];
	f32 start2; // 0x78
	f32 hold2;  // 0x7C
	f32 end2;   // 0x80
	s32 wait;   // 0x84
	f32 end;    // 0x88
	f32 hold;   // 0x8C
};

struct Player800C1554 {
	u8 pad0[0x9B4];
	s32 type; // 0x9B4
};

struct Team800C1554 {
	u8 pad0[0x3B];
	s8 current; // 0x3B
	u8 pad3C[0x114 - 0x3C];
	Player800C1554* members[3]; // 0x114
};

extern "C" {
extern Team800C1554* lbl_80303DC8[];
extern const f32 lbl_8042DE54; // 0.0f
extern const f32 lbl_8042DE5C; // the time step
extern void* lbl_8042C3FC;
void* fn_800C480C(void* result, void* anim, void* data, f32* time);
void fn_80204144(void* anim, void* callback, f32* time);
void fn_802041EC(void* anim);
void fn_802033F4(void* anim);
}

extern "C" void fn_800C1554(HudCounter800C1554* counter)
{
	f32 old = counter->time;

	if (lbl_8042DE54 == counter->time) {
		s32 count = PARAM_CHALLENGE::num[0];
		if (count >= 0 && count != counter->count) {
			counter->count = count;
			counter->time += lbl_8042DE5C;
			counter->wait          = 0;
			Team800C1554* team     = lbl_80303DC8[0];
			Player800C1554* leader = team->members[team->current];
			switch (leader->type) {
				case 0:
					counter->time += counter->start0;
					counter->hold = counter->hold0;
					counter->end  = counter->start1;
					break;
				case 1:
					counter->time += counter->start1;
					counter->hold = counter->hold1;
					counter->end  = counter->start2;
					break;
				case 2:
					counter->time += counter->start2;
					counter->hold = counter->hold2;
					counter->end  = counter->end2 + counter->start1 - counter->base1;
					break;
			}
			if (counter->count > 99) {
				counter->shown = 99;
			} else if (counter->count < 0) {
				counter->shown = 0;
			} else {
				counter->shown = counter->count;
			}
		}
	} else if (old >= counter->hold && counter->wait < 30) {
		counter->wait++;
	} else {
		counter->time += lbl_8042DE5C;
		if (counter->time > counter->end - lbl_8042DE5C) {
			counter->time = lbl_8042DE54;
		}
	}
	f32 time = counter->time;
	if (time != old && lbl_8042C3FC != NULL) {
		f32 value = time;
		fn_80204144(lbl_8042C3FC, (void*)fn_800C480C, &value);
		counter->time = value;
		if (time > counter->time) {
			counter->time = lbl_8042DE54;
			f32 again     = counter->time;
			fn_80204144(lbl_8042C3FC, (void*)fn_800C480C, &again);
			counter->time = again;
		}
		fn_802041EC(lbl_8042C3FC);
		fn_802033F4(lbl_8042C3FC);
	}
}
