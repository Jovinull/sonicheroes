// Copies 10 bytes to +0x5A of the object and sets bit 5 of its flag word at +8.
// Does nothing when either the owner or the object pointer is null.

#include "types.h"

struct Unk8018FCB0 {
	u8 pad0[0x8];
	u32 flags; // 0x8
};

extern "C" {
void* memcpy(void*, const void*, unsigned);

void fn_8018FCB0(void* arg0, Unk8018FCB0* arg1, void* arg2)
{
	if (arg0 == 0 || arg1 == 0) {
		return;
	}
	memcpy((u8*)arg1 + 0x5a, arg2, 0xa);
	arg1->flags |= 0x20;
}
}
