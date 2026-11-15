// Moves an object's animation time (+0x2C) toward its start (+0x3C, direction +0x4C = 1) or its end
// (+0x40) by lbl_8042DE80 per call (AdjustFloat) while it plays (+0x44); in play mode 1, and while
// lbl_8042C410 is set, it drives the interpolator lbl_8042C428 like fn_800C0B04 does (fn_80204144
// with fn_800C480C), stopping a one-shot animation (+0x48 = 1) that runs back before the first step
// (its id leaves the table lbl_803042C8), and updates it. HYPOTHESIS: RtAnim helpers.
#include "types.h"

struct Anim800C0384 {
	u8 pad0[0x2C];
	f32 time; // 0x2C
	u8 pad30[0x3C - 0x30];
	f32 start;   // 0x3C
	f32 end;     // 0x40
	s32 play;    // 0x44
	s32 once;    // 0x48
	s32 toStart; // 0x4C
};

extern "C" {
extern f32 lbl_8042DE80; // 1/300
extern f32 lbl_8042DE54; // 0.0f
extern void* lbl_8042C410;
extern void* lbl_8042C428;
extern void* lbl_803042C8[0x40];
void* fn_800C480C(void* result, void* anim, void* data, f32* time);
void fn_80204144(void* anim, void* callback, f32* time);
void fn_802041EC(void* anim);
void fn_802033F4(void* anim);
}

f32 AdjustFloat(f32 value, f32 target, f32 step);

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

extern "C" void fn_800C0384(Anim800C0384* a)
{
	if (a->play == 0) {
		return;
	}
	if (a->toStart == 1) {
		a->time = AdjustFloat(a->time, a->start, lbl_8042DE80);
	} else {
		a->time = AdjustFloat(a->time, a->end, lbl_8042DE80);
	}
	if (lbl_8042C410 != NULL && a->play == 1) {
		f32 time = a->time;

		fn_80204144(lbl_8042C428, (void*)fn_800C480C, &time);
		a->time = time;
		if (a->once == 1 && a->time < lbl_8042DE80) {
			Unregister(lbl_8042C428);
			a->time = lbl_8042DE54;
			a->once = 0;
			a->play = 0;
		}
		fn_802041EC(lbl_8042C428);
		fn_802033F4(lbl_8042C428);
	}
}
