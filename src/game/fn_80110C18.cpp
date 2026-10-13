#include "types.h"

// Flags the object in lbl_8042C610 (bit 1 of its volatile flags at 0x4) and
// forgets it.

struct Fn80110C18Object {
	u8 unk0[0x4];
	volatile u16 flags; // 0x4
};

extern "C" Fn80110C18Object* lbl_8042C610;

extern "C" void fn_80110C18(void)
{
	Fn80110C18Object* object = lbl_8042C610;
	u32 flags                = object->flags | 1;
	object->flags            = (u16)flags;
	lbl_8042C610             = 0;
}
