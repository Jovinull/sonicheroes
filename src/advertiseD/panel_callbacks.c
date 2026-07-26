#include "types.h"

// Four one-step callbacks over the same panel: two forward to the child it
// holds, two put the panel into state 5 and hand its animator the row of the
// table that matches the panel's index.
//
// The translation unit runs from fn_1_9AC0 at 0x9AC0 to the end of fn_1_9B64
// at 0x9BB0. The two tables it reads sit at .rodata 0xD70 and 0xE20 with a
// long stretch of other constants between them, so the .rodata is left to the
// module and only referenced here: this unit emits none of its own.
//
// fn_1_9B18 and fn_1_9B64 are the same function against different tables,
// which is how the original has them.

typedef struct Entry {
	s32 unk0;
	s32 unk4;
} Entry;

typedef struct Panel {
	u8 unk0[0x2C];   // 0x000
	s32 unk2C;       // 0x02C
	u8 unk30[0x30];  // 0x030
	s32 unk60;       // 0x060
	u8 unk64[0x1C0]; // 0x064
	s32 index;       // 0x224
	u8 unk228[0xC];  // 0x228
	void* child;     // 0x234
} Panel;

extern "C" const Entry lbl_1_rodata_D70[];
extern "C" const Entry lbl_1_rodata_E20[];

extern "C" void fn_1_7B24(void* animator, const Entry* entry);
extern "C" void fn_1_8C1C(void* child);
extern "C" void fn_1_8C28(void* child);

extern "C" void fn_1_9AC0(Panel* panel)
{
	if (panel->child != NULL) {
		fn_1_8C28(panel->child);
	}
}

extern "C" void fn_1_9AEC(Panel* panel)
{
	if (panel->child != NULL) {
		fn_1_8C1C(panel->child);
	}
}

extern "C" void fn_1_9B18(Panel* panel)
{
	panel->unk2C = 1;
	panel->unk60 = 5;
	fn_1_7B24(panel->unk64, &lbl_1_rodata_E20[panel->index]);
}

extern "C" void fn_1_9B64(Panel* panel)
{
	panel->unk2C = 1;
	panel->unk60 = 5;
	fn_1_7B24(panel->unk64, &lbl_1_rodata_D70[panel->index]);
}
