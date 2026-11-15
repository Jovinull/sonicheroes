// fn_800C0B04's variant for lbl_8042C410 with a loop countdown (+0x4C): while the object plays
// (+0x44) the time (+0x2C) moves by lbl_8042DE80; a looping animation (+0x48 = 0) that reaches
// lbl_8042DE5C before its end (+0x40) counts down by 5 (unless play-mode flag 33 of lbl_8042C180
// is set) and holds there, or, once the countdown is negative, clears it and becomes one-shot.
// The interpolator part is fn_800C0B04's. HYPOTHESIS: RtAnim helpers; the countdown role is
// UNKNOWN.
#include "types.h"

struct Anim800C0714 {
	u8 pad0[0x2C];
	f32 time; // 0x2C
	u8 pad30[0x3C - 0x30];
	f32 start; // 0x3C
	f32 end;   // 0x40
	s32 play;  // 0x44
	s32 once;  // 0x48
	s32 count; // 0x4C
};

extern "C" {
extern f32 lbl_8042DE80; // 1/300
extern f32 lbl_8042DE54; // 0.0f
extern void* lbl_8042C410;
extern f32 lbl_8042DE5C;
struct PlayMode800C0714 {
	s8 flags[44];
};
extern PlayMode800C0714* lbl_8042C180;
extern void* lbl_803042C8[0x40];
void* fn_800C480C(void* result, void* anim, void* data, f32* time);
void fn_80204144(void* anim, void* callback, f32* time);
void fn_802041EC(void* anim);
void fn_802033F4(void* anim);
}

// Clears `id` from the id table (the first matching entry; see dtor_800C3F0C).
static inline void Unregister(void* id)
{
	int i;

	for (i = 0; i < 0x40; i++) {
		void* entry = lbl_803042C8[i];

		if (entry == id) {
			lbl_803042C8[i] = NULL;
			break;
		}
	}
}

extern "C" void fn_800C0714(Anim800C0714* a)
{
	if (a->play == 0) {
		return;
	}
	a->time += lbl_8042DE80;
	if (a->once == 0 && a->time >= a->end - lbl_8042DE5C) {
		if (lbl_8042C180->flags[33] == 0) {
			a->count -= 5;
		}
		if (a->count < 0) {
			a->count = 0;
			a->once  = 1;
		} else {
			a->time = a->end - lbl_8042DE5C;
		}
	}
	if (lbl_8042C410 != NULL && a->play == 1) {
		f32 time = a->time;

		fn_80204144(lbl_8042C410, (void*)fn_800C480C, &time);
		a->time = time;
		if (a->once == 1 && a->time < lbl_8042DE80) {
			Unregister(lbl_8042C410);
			a->time = lbl_8042DE54;
			a->once = 0;
			a->play = 0;
		}
		fn_802041EC(lbl_8042C410);
		fn_802033F4(lbl_8042C410);
	}
}
