#include "types.h"

// Reads two volatile state bytes of the game state (0x1C, then 0x5) and does
// nothing with them: what is left of a check whose body was compiled out.

struct GameFlags {
	u8 unk00[0x5];
	volatile s8 flag05; // 0x05
	u8 unk06[0x16];
	volatile s8 flag1C; // 0x1C
};

extern GameFlags* lbl_8042C180;

extern "C" void fn_8004FC9C(void)
{
	GameFlags* flags = lbl_8042C180;
	if (flags->flag1C != 0 || flags->flag05 != 0) {
		return;
	}
}
