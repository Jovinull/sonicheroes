#include "types.h"

// Advances a two-part stage animation: with a direction (+0x48) the time (+0x2C) eases toward the
// end (+0x44) by lbl_8042DE80, wraps to the start (+0x40) past it and, with play-mode flag 38
// (lbl_8042C180), stops (direction cleared, second time +0x4C reset to lbl_8042DE54); without one
// a running time runs back by lbl_8042DE80 to its minimum (+0x3C), where the interpolator
// lbl_8042C404 is removed from the id table lbl_803042C8, and a time at lbl_8042DE54 stops. The
// interpolator lbl_8042C404 is then driven (as fn_800C0B04 does); a running second time drives
// lbl_8042C408 forward by lbl_8042DE80 and becomes lbl_8042DE88 once it wraps. HYPOTHESIS: RtAnim
// helpers; the field names are UNKNOWN.

struct Anim800C19EC {
	u8 pad0[0x2C];
	f32 time; // 0x2C
	u8 pad30[0x3C - 0x30];
	f32 minimum;   // 0x3C
	f32 start;     // 0x40
	f32 end;       // 0x44
	s32 direction; // 0x48
	f32 time2;     // 0x4C
};

struct PlayMode800C19EC {
	s8 flags[44];
};

extern "C" {
extern f32 lbl_8042DE54; // 0.0f
extern f32 lbl_8042DE80;
extern f32 lbl_8042DE88;
extern PlayMode800C19EC* lbl_8042C180;
extern void* lbl_8042C404;
extern void* lbl_8042C408;
extern void* lbl_803042C8[0x40];
void* fn_800C480C(void* result, void* anim, void* data, f32* time);
void fn_80204144(void* anim, void* callback, f32* time);
void fn_802041EC(void* anim);
void fn_802033F4(void* anim);
}

f32 AdjustFloat(f32 value, f32 target, f32 step);

// Clears `id` from the id table (the first matching entry; see fn_800C0B04).
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

extern "C" void fn_800C19EC(Anim800C19EC* a)
{
	if (a->direction != 0) {
		a->time = AdjustFloat(a->time, a->end, lbl_8042DE80);
		if (a->time > a->end) {
			a->time = a->start;
		}
		if (lbl_8042C180->flags[38] != 0) {
			a->direction = 0;
			a->time2     = lbl_8042DE54;
		}
	} else if (a->time > lbl_8042DE54) {
		a->time -= lbl_8042DE80;
		if (a->time < a->minimum) {
			a->time = a->minimum;
			Unregister(lbl_8042C404);
		}
	} else if (lbl_8042DE54 == a->time && a->direction == 0) {
		return;
	}
	if (lbl_8042C404 != NULL) {
		f32 time = a->time;
		fn_80204144(lbl_8042C404, (void*)fn_800C480C, &time);
		a->time = time;
		fn_802041EC(lbl_8042C404);
		fn_802033F4(lbl_8042C404);
	}
	f32 previous = a->time2;
	if (previous >= lbl_8042DE54) {
		a->time2  = previous + lbl_8042DE80;
		f32 time2 = a->time2;
		fn_80204144(lbl_8042C408, (void*)fn_800C480C, &time2);
		a->time2 = time2;
		if (a->time2 < previous) {
			a->time2 = lbl_8042DE88;
		} else {
			fn_802041EC(lbl_8042C408);
			fn_802033F4(lbl_8042C408);
		}
	}
}
