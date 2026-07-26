#include "types.h"

// A countdown that fires once when it reaches zero, and the empty callback the
// animation is given so it stops on its own.
//
// The translation unit runs from fn_1_550C at 0x550C to the end of fn_1_5544
// at 0x55A4. The table at .rodata 0x6A8 is left to the module and only
// referenced here, so this unit emits no data of its own.
//
// The counter goes one below zero on the turn it fires, which is what keeps it
// from firing again: the branch that fires is only taken when the value read
// is exactly zero.

typedef struct Trigger {
	u8 unk0[0x190]; // 0x000
	s32 index;      // 0x190
	u8 unk194[0x4]; // 0x194
	s32 counter;    // 0x198
} Trigger;

extern "C" void* lbl_1_rodata_6A8[];

extern "C" void fn_800CB368(void* effect, s32 arg1, s32 arg2);
extern "C" void fn_8014FFBC(void* anim, void* callback, f32* step);

extern "C" void fn_1_550C(void) { }

extern "C" void fn_1_5510(void* anim)
{
	if (anim != NULL) {
		fn_8014FFBC(anim, (void*)fn_1_550C, NULL);
	}
}

extern "C" void fn_1_5544(Trigger* trigger)
{
	s32 remaining = trigger->counter;

	if (remaining > 0) {
		trigger->counter = remaining - 1;
	} else if (remaining == 0) {
		trigger->counter = remaining - 1;
		fn_800CB368(lbl_1_rodata_6A8[trigger->index], -1, -1);
	}
}
