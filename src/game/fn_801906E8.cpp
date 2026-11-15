#include "types.h"

struct S801906E8 {
	u8 pad0[0x8];
	u32 flags; // 0x8
	u8 padC[0x44 - 0xC];
	u8 data[5]; // 0x44
};

extern "C" {
void* memcpy(void* destination, const void* source, u32 size);

void fn_801906E8(u32 arg0, S801906E8* arg1, void* arg2)
{
	if (arg0 == 0U || arg1 == NULL) {
		return;
	}
	memcpy(arg1->data, arg2, 5);
	arg1->flags = arg1->flags | 2;
}
}
