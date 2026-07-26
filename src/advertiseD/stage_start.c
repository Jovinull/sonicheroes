#include "types.h"

// Hands the attract mode over to the stage it has selected: sets the settings
// the run needs, points the loader at the chosen stage, and moves to state 7.
//
// The translation unit is the single function fn_1_9954, .text 0x9954 to
// 0x9AC0. The table of stage ids it reads sits at .rodata 0xBD0 and nothing
// outside this function touches it; it is named rather than written out, so
// this unit claims no .rodata of its own.
//
// The table is read three times against the same index, and the original
// reloads it each time rather than keeping it, which is why it is written out
// three times here instead of through a local.

typedef struct Attract {
	u8 unk0[0x2C];   // 0x000
	s32 state;       // 0x02C
	u8 unk30[0x1F4]; // 0x030
	s32 slot;        // 0x224
	s32 mode;        // 0x228
	s32 unk22C;      // 0x22C
} Attract;

extern "C" const s32 lbl_1_rodata_BD0[];
extern "C" u8 lbl_8029C310[];
extern "C" u8 lbl_80303EC8[];

extern "C" void fn_800191F8(void* loader, s32 arg1, s32 arg2);
extern "C" void fn_8001934C(void* loader, s32 slot, s32 value);
extern "C" void fn_8001936C(void* loader, s32 slot, s32 stage);
extern "C" void fn_8001938C(void* loader);
extern "C" void fn_800A96B0(void* settings, s32 id, s32 value);

extern "C" void fn_1_9954(Attract* attract)
{
	if (attract->unk22C == 0) {
		fn_800A96B0(lbl_80303EC8, 0x28, 0);
	} else {
		fn_800A96B0(lbl_80303EC8, 0x28, 1);
	}

	fn_800191F8(lbl_8029C310, 0, 0);
	fn_800A96B0(lbl_80303EC8, 0x27, 0);
	fn_800A96B0(lbl_80303EC8, 0x18, 0);
	fn_8001938C(lbl_8029C310);
	fn_8001934C(lbl_8029C310, 0, attract->mode);

	if (attract->mode == 3 && lbl_1_rodata_BD0[attract->slot] == 8) {
		fn_8001936C(lbl_8029C310, 0, 0x24);
	} else {
		fn_8001936C(lbl_8029C310, 0, lbl_1_rodata_BD0[attract->slot]);
	}

	if (lbl_1_rodata_BD0[attract->slot] == 0x17) {
		fn_8001936C(lbl_8029C310, 1, 0x18);
	}

	attract->state = 7;
	fn_800A96B0(lbl_80303EC8, 0x2A, 6);
}
