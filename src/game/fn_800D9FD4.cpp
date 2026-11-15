// While the linked record (+0x9B8) is in mode 2, nudges a player's value at +0x7B8 when its value
// at +0x7C4 is below lbl_8042B694: by lbl_8042B698 * (lbl_8042B694 - v) when the height difference
// +0x70C - +0x9A0 is in [lbl_8042B688, lbl_8042B68C), or by lbl_8042B698 * (lbl_8042B690 - v) when
// it is in (lbl_8042C498, lbl_8042B688). HYPOTHESIS: a height-dependent speed boost of the AI;
// field and constant roles are UNKNOWN.
#include "types.h"

struct Linked800D9FD4 {
	u8 pad0[0x140];
	s32 mode; // 0x140
};

struct Player800D9FD4 {
	u8 pad0[0x70C];
	f32 unknown70C; // 0x70C
	u8 pad710[0x7B8 - 0x710];
	f32 unknown7B8; // 0x7B8
	u8 pad7BC[0x7C4 - 0x7BC];
	f32 unknown7C4; // 0x7C4
	u8 pad7C8[0x9A0 - 0x7C8];
	f32 unknown9A0; // 0x9A0
	u8 pad9A4[0x9B8 - 0x9A4];
	Linked800D9FD4* linked; // 0x9B8
};

extern "C" {
extern f32 lbl_8042B688;
extern f32 lbl_8042B68C;
extern f32 lbl_8042B690;
extern f32 lbl_8042B694;
extern f32 lbl_8042B698;
extern f32 lbl_8042C498;

void fn_800D9FD4(Player800D9FD4* p)
{
	f32 diff;

	if (p->linked->mode != 2) {
		return;
	}
	diff = p->unknown70C - p->unknown9A0;
	if (p->unknown7C4 < lbl_8042B694 && diff >= lbl_8042B688 && diff < lbl_8042B68C) {
		p->unknown7B8 = p->unknown7B8 + lbl_8042B698 * (lbl_8042B694 - p->unknown7C4);
		return;
	}
	if (p->unknown7C4 < lbl_8042B694 && diff > lbl_8042C498 && diff < lbl_8042B688) {
		p->unknown7B8 = p->unknown7B8 + lbl_8042B698 * (lbl_8042B690 - p->unknown7C4);
	}
}
}
