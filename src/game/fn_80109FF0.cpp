// Releases the record held in lbl_8042C5A8 (UNKNOWN role; called first by the enemy shutdown
// fn_800A7338): sets bit 0x1 of its flags at 0x4 and clears the pointer. Does nothing when no
// record is held. Built with the game-unit flags (-opt noschedule,nopeephole).
#include "types.h"

struct Record80109FF0 {
	u8 pad0[0x4];
	u16 flags; // 0x4
};

extern "C" {
extern Record80109FF0* lbl_8042C5A8;

void fn_80109FF0(void)
{
	if (lbl_8042C5A8 != 0) {
		lbl_8042C5A8->flags |= 0x1;
		lbl_8042C5A8 = 0;
	}
}
}
