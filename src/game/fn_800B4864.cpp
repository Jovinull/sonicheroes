// For each of the 43 records (0x38 bytes from +8) whose halfword at 0x18 equals the key, clears its halfword at 0x12, sets bit 2 and clears bit 14 of its flags word at 0xC. Sibling of fn_800B4814, which keys on the word at 0x1C.

#include "types.h"

typedef struct {
	u8 pad0[6];
	s8 f6;
	u8 pad7[5];
	u32 fC;
	u8 pad10[2];
	s16 f12;
	u8 pad14[4];
	u16 f18;
	u8 pad1A[0x1A];
	s32 f34;
} Slot800B4864;

extern "C" {
void fn_800B4864(void* arg0, u16 arg1)
{
	s8 i;
	Slot800B4864* p;

	p = (Slot800B4864*)((u8*)arg0 + 8);
	for (i = 0; i < 0x2B; i++) {
		if (p->f18 == arg1) {
			p->f12 = 0;
			p->fC |= 4;
			p->fC &= 0xFFFFBFFF;
		}
		p++;
	}
}
}
