// Initialises the six-direction table (HYPOTHESIS; names inferred): clears the eight words of
// lbl_803E7238, allocates six 12-byte entries (lbl_8042C5A0) and fills entry i with the sine and
// cosine (fn_800D7B00, fn_800D7AE4) of the angle i * 0x10000 / 5 and the constant lbl_8042E738.
#include "types.h"

struct Direction80104410 {
	f32 sine;   // 0x0
	f32 cosine; // 0x4
	f32 value;  // 0x8
};

void* operator new[](unsigned long size);

extern "C" {
extern s32 lbl_803E7238[8];
extern Direction80104410* lbl_8042C5A0;
extern const f32 lbl_8042E738;
// HYPOTHESIS: integer-angle sine and cosine.
f32 fn_800D7B00(s32 angle);
f32 fn_800D7AE4(s32 angle);

void fn_80104410(void)
{
	s32 i;
	Direction80104410* direction;

	lbl_803E7238[0] = 0;
	lbl_803E7238[1] = 0;
	lbl_803E7238[2] = 0;
	lbl_803E7238[3] = 0;
	lbl_803E7238[4] = 0;
	lbl_803E7238[5] = 0;
	lbl_803E7238[6] = 0;
	lbl_803E7238[7] = 0;
	direction = lbl_8042C5A0 = (Direction80104410*)operator new[](6 * sizeof(Direction80104410));
	for (i = 0; i < 6; i++) {
		s32 angle         = (i * 0x10000) / 5;
		direction->sine   = fn_800D7B00(angle);
		direction->cosine = fn_800D7AE4(angle);
		direction->value  = lbl_8042E738;
		direction++;
	}
}
}
