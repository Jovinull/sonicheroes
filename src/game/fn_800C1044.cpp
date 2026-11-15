// fn_800C0B04's variant for lbl_8042C418: on stages 0x1A..0x1C (lbl_8029C310 +0x2C) it first runs
// fn_8017348C on the interpolator's fn_802043AC; while the object plays (+0x44) the time (+0x2C)
// moves by lbl_8042DE80 and, for a looping animation (+0x48 = 0), stops lbl_8042DE5C short of the
// end (+0x40) instead of wrapping. The interpolator part is fn_800C0B04's. HYPOTHESIS: RtAnim
// helpers; the stage roles are UNKNOWN.
#include "types.h"

struct Anim800C1044 {
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
extern void* lbl_8042C418;
extern f32 lbl_8042DE5C;
struct Action800C1044 {
	u8 pad0[0x2C];
	s32 stage; // 0x2C
};
extern Action800C1044 lbl_8029C310;
extern void* lbl_803042C8[0x40];
void* fn_800C480C(void* result, void* anim, void* data, f32* time);
void fn_80204144(void* anim, void* callback, f32* time);
void fn_802041EC(void* anim);
void fn_802033F4(void* anim);
void* fn_802043AC(void* anim);
void fn_8017348C(void* p);
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

extern "C" void fn_800C1044(Anim800C1044* a)
{
	if (lbl_8029C310.stage == 0x1A || lbl_8029C310.stage == 0x1B || lbl_8029C310.stage == 0x1C) {
		fn_8017348C(fn_802043AC(lbl_8042C418));
	}
	if (a->play == 0) {
		return;
	}
	a->time += lbl_8042DE80;
	if (a->once == 0 && a->time > a->end - lbl_8042DE5C) {
		a->time = a->end - lbl_8042DE5C;
	}
	if (lbl_8042C418 != NULL && a->play == 1) {
		f32 time = a->time;

		fn_80204144(lbl_8042C418, (void*)fn_800C480C, &time);
		a->time = time;
		if (a->once == 1 && a->time < lbl_8042DE80) {
			Unregister(lbl_8042C418);
			a->time = lbl_8042DE54;
			a->once = 0;
			a->play = 0;
		}
		fn_802041EC(lbl_8042C418);
		fn_802033F4(lbl_8042C418);
	}
}
