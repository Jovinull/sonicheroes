#include "types.h"

// Runs one frame of the attract mode: dispatch on which of the thirteen states
// it is in, then advance the animation it holds.
//
// The translation unit runs from fn_1_C450 at 0xC450 to the end of fn_1_C48C
// at 0xC54C, and owns .data 0x3D60 to 0x3D94. That block is not written here:
// it is the jump table the compiler builds for the switch, and nothing else
// reads it.
//
// The order the cases are written in is read off that table rather than
// guessed. The table maps state minus five to an offset inside the function,
// and the offsets say the bodies come out in the order 5, 6, 7, 8, 10, 11, 12,
// 13, 14, 16, 17, 15 - so state 15 is written last, after 16 and 17, and state
// 9 is absent and falls through to doing nothing.

typedef struct Attract {
	u8 unk0[0x28];   // 0x000
	s32 state;       // 0x028
	u8 unk2C[0x3D4]; // 0x02C
	void* anim;      // 0x400
	f32 value;       // 0x404
} Attract;

extern "C" void fn_800A8264(Attract* attract);
extern "C" void fn_8012CC20(void* anim);
extern "C" void fn_8012CEF0(void* anim, f32 value);

extern "C" void fn_1_B1B4(Attract* attract);
extern "C" void fn_1_B400(Attract* attract);
extern "C" void fn_1_B518(Attract* attract);
extern "C" void fn_1_B5DC(Attract* attract);
extern "C" void fn_1_B674(Attract* attract);
extern "C" void fn_1_B734(Attract* attract);
extern "C" void fn_1_B828(Attract* attract);
extern "C" void fn_1_B9E8(Attract* attract);
extern "C" void fn_1_BC98(Attract* attract);
extern "C" void fn_1_BE0C(Attract* attract);
extern "C" void fn_1_BF80(Attract* attract);
extern "C" void fn_1_C1CC(Attract* attract);

extern "C" void fn_1_C450(Attract* attract)
{
	fn_800A8264(attract);
	if (attract->anim != NULL) {
		fn_8012CC20(attract->anim);
	}
}

extern "C" void fn_1_C48C(Attract* attract)
{
	switch (attract->state) {
		case 5:
			fn_1_C1CC(attract);
			break;
		case 6:
			fn_1_BF80(attract);
			break;
		case 7:
			fn_1_BE0C(attract);
			break;
		case 8:
			fn_1_BC98(attract);
			break;
		case 10:
			fn_1_B9E8(attract);
			break;
		case 11:
			fn_1_B828(attract);
			break;
		case 12:
			fn_1_B734(attract);
			break;
		case 13:
			fn_1_B674(attract);
			break;
		case 14:
			fn_1_B1B4(attract);
			break;
		case 16:
			fn_1_B518(attract);
			break;
		case 17:
			fn_1_B400(attract);
			break;
		case 15:
			fn_1_B5DC(attract);
			break;
	}

	if (attract->anim != NULL) {
		fn_8012CEF0(attract->anim, attract->value);
	}
}
