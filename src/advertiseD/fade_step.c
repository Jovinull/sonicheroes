#include "types.h"

// Three one-line steps over the same fading object, plus the empty one that
// sits between two of them.
//
// The translation unit runs from fn_1_EC18 at 0xEC18 to the end of fn_1_EC74
// at 0xECAC, and owns .rodata 0x19A0 to 0x19A4. That single float is the
// amount both steppers add, and nothing outside these four functions reads it,
// which is what makes them a unit.
//
// fn_1_EC2C and fn_1_EC74 are the same step with different endings: one moves
// the object to state 1 unless it is already at 4, the other moves it to 2
// unconditionally. Both reread the counter after writing it, which is what the
// comparison against the limit does in the original.
//
// The step has to be written as += rather than spelled out. Written out, the
// compiler materialises the constant before reading the counter; the compound
// form reads the counter first, which is the order the original has.

typedef struct Fade {
	u8 unk0[0x4];  // 0x00
	u16 flags;     // 0x04
	u8 unk6[0x26]; // 0x06
	f32 elapsed;   // 0x2C
	f32 limit;     // 0x30
	u8 unk34[0x8]; // 0x34
	s32 state;     // 0x3C
} Fade;

extern "C" void fn_1_EC18(Fade* fade)
{
	fade->flags &= ~0x10;
}

extern "C" void fn_1_EC2C(Fade* fade)
{
	fade->elapsed += 1.0f;
	if (fade->limit <= fade->elapsed) {
		if (fade->state != 4) {
			fade->state = 1;
		}
	}
}

extern "C" void fn_1_EC70(void) { }

extern "C" void fn_1_EC74(Fade* fade)
{
	fade->elapsed += 1.0f;
	if (fade->limit <= fade->elapsed) {
		fade->state = 2;
	}
}
