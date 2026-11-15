// Advances an object's animation while it plays (+0x44): the time (+0x2C) moves by lbl_8042DE80
// and, for a looping animation (+0x48 = 0), wraps from the end (+0x40) back to the start (+0x3C).
// In play mode 1 the shared interpolator lbl_8042C420 is driven (fn_80204144 with the callback
// fn_800C480C); a one-shot animation (+0x48 = 1) that runs back before the first step is
// stopped: its interpolator id is removed from the 64-entry id table lbl_803042C8 and the state
// cleared. The interpolator is then updated (fn_802041EC, fn_802033F4). HYPOTHESIS: RtAnim helpers.
#include "types.h"

struct Anim800C0B04 {
	u8 pad0[0x2C];
	f32 time; // 0x2C
	u8 pad30[0x3C - 0x30];
	f32 start; // 0x3C
	f32 end;   // 0x40
	s32 play;  // 0x44
	s32 once;  // 0x48
};

extern "C" {
extern f32 lbl_8042DE80; // 1/300
extern f32 lbl_8042DE54; // 0.0f
extern void* lbl_8042C420;
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

extern "C" void fn_800C0B04(Anim800C0B04* a)
{
	if (a->play == 0) {
		return;
	}
	a->time += lbl_8042DE80;
	if (a->once == 0 && a->time >= a->end) {
		a->time = a->start;
	}
	if (lbl_8042C420 != NULL && a->play == 1) {
		f32 time = a->time;

		fn_80204144(lbl_8042C420, (void*)fn_800C480C, &time);
		a->time = time;
		if (a->once == 1 && a->time < lbl_8042DE80) {
			Unregister(lbl_8042C420);
			a->time = lbl_8042DE54;
			a->once = 0;
			a->play = 0;
		}
		fn_802041EC(lbl_8042C420);
		fn_802033F4(lbl_8042C420);
	}
}
