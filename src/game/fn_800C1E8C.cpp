#include "types.h"

// Advances one of the looping stage animations (+0x28 picks the interpolator lbl_8042B408 and its
// owner lbl_80304408): with a direction (+0x4C) the time (+0x2C) eases toward the end (+0x48) by
// lbl_8042DE5C and wraps to the start (+0x44) there; without one a running time (above
// lbl_8042DE54) moves by lbl_8042DE5C and is held at the end, and a time at lbl_8042DE54 stops.
// The interpolator is then driven (fn_80204144 with fn_800C480C, as fn_800C0B04 does); when the
// time wraps below the start from past the end it restarts at lbl_8042DE54 and a one-shot owner
// (+0x4C = 1) is cleared and its interpolator id removed from lbl_803042C8. HYPOTHESIS: RtAnim
// helpers; the field names are UNKNOWN.

struct Anim800C1E8C {
	u8 pad0[0x28];
	s8 index; // 0x28
	u8 pad29[0x2C - 0x29];
	f32 time; // 0x2C
	u8 pad30[0x44 - 0x30];
	f32 start;     // 0x44
	f32 end;       // 0x48
	s32 direction; // 0x4C
};

struct Owner800C1E8C {
	u8 pad0[0x4C];
	s32 once; // 0x4C
};

extern "C" {
extern f32 lbl_8042DE54; // 0.0f
extern f32 lbl_8042DE5C;
extern void* lbl_8042B408[2];
extern Owner800C1E8C* lbl_80304408[];
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

extern "C" void fn_800C1E8C(Anim800C1E8C* a)
{
	if (a->direction != 0) {
		a->time = AdjustFloat(a->time, a->end, lbl_8042DE5C);
		if (a->time >= a->end) {
			a->time = a->start;
		}
	} else if (a->time > lbl_8042DE54) {
		a->time += lbl_8042DE5C;
		if (a->time < a->end) {
			a->time = a->end;
		}
	} else if (lbl_8042DE54 == a->time && a->direction == 0) {
		return;
	}
	void* anim = lbl_8042B408[a->index];
	if (anim == NULL) {
		return;
	}
	f32 previous = a->time;
	f32 time     = previous;
	fn_80204144(anim, (void*)fn_800C480C, &time);
	a->time = time;
	if (a->time < a->start && previous > a->end) {
		a->time              = lbl_8042DE54;
		s32 index            = a->index;
		Owner800C1E8C* owner = lbl_80304408[index];
		if (owner != NULL && owner->once == 1) {
			owner->once = 0;
			Unregister(lbl_8042B408[index]);
		}
	}
	fn_802041EC(lbl_8042B408[a->index]);
	fn_802033F4(lbl_8042B408[a->index]);
}
