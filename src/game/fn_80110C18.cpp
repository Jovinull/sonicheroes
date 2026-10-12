#include "types.h"

struct Fn80110C18Data {
	u8 pad[4];
	volatile u16 flags;
};

extern "C" Fn80110C18Data* lbl_8042C610;

extern "C" void fn_80110C18(void)
{
	Fn80110C18Data* state = lbl_8042C610;
	u32 flags             = state->flags | 1;
	state->flags          = (u16)flags;
	lbl_8042C610          = 0;
}
