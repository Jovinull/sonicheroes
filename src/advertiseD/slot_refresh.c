#include "types.h"

// Recomputes which of the twenty-two slots are available, then points each
// slot's pair of objects at the right pair of models.
//
// The translation unit runs from fn_1_901C at 0x901C to the end of fn_1_905C
// at 0x922C. The three tables it walks live in .bss at 0x590, 0x640 and 0x6F0
// and nothing outside this run touches them, but they are left to the module
// and only declared here: this unit emits no .bss of its own.
//
// Slots 5 and 14 are special-cased against the current mode, and each picks a
// different model per mode. The indexes are written out rather than taken from
// the loop variable because that is what the original does: inside those two
// branches it reaches the table from its base with a constant offset, not
// through the pointer it is walking with.

typedef struct Panel {
	u8 unk0[0x228];  // 0x000
	s32 mode;        // 0x228
	u8 unk22C[0x18]; // 0x22C
	s32 enabled[22]; // 0x244
} Panel;

extern "C" void* lbl_1_bss_590[22][2];
extern "C" void* lbl_1_bss_640[22][2];
extern "C" void* lbl_1_bss_6F0[12];

extern "C" void fn_801A45A0(void* object, void* model);
extern "C" void fn_1_92D0(Panel* panel, s8* out, s32 index, s32 mode);

#pragma dont_inline on

extern "C" s32 fn_1_901C(Panel* panel, s32 index)
{
	s8 available;

	fn_1_92D0(panel, &available, index, panel->mode);
	return available != 0;
}

extern "C" void fn_1_905C(Panel* panel)
{
	s32 i;
	s32 j;

	for (i = 0; i != 22; i++) {
		panel->enabled[i] = fn_1_901C(panel, i);
	}

	for (j = 0; j != 22; j++) {
		if (panel->enabled[j] == 0) {
			fn_801A45A0(lbl_1_bss_590[j][0], lbl_1_bss_6F0[0]);
			fn_801A45A0(lbl_1_bss_590[j][1], lbl_1_bss_6F0[1]);
		} else {
			fn_801A45A0(lbl_1_bss_590[j][0], lbl_1_bss_640[j][0]);
			if (j == 5) {
				switch (panel->mode) {
					case 0:
						fn_801A45A0(lbl_1_bss_590[5][1], lbl_1_bss_6F0[3]);
						break;
					case 1:
						fn_801A45A0(lbl_1_bss_590[5][1], lbl_1_bss_6F0[5]);
						break;
					case 2:
						fn_801A45A0(lbl_1_bss_590[5][1], lbl_1_bss_6F0[2]);
						break;
					case 3:
						fn_801A45A0(lbl_1_bss_590[5][1], lbl_1_bss_6F0[4]);
						break;
				}
			} else if (j == 14) {
				fn_801A45A0(lbl_1_bss_590[j][0], lbl_1_bss_640[j][0]);
				switch (panel->mode) {
					case 0:
						fn_801A45A0(lbl_1_bss_590[14][1], lbl_1_bss_6F0[4]);
						break;
					case 1:
						fn_801A45A0(lbl_1_bss_590[14][1], lbl_1_bss_6F0[2]);
						break;
					case 2:
						fn_801A45A0(lbl_1_bss_590[14][1], lbl_1_bss_6F0[5]);
						break;
					case 3:
						fn_801A45A0(lbl_1_bss_590[14][1], lbl_1_bss_6F0[3]);
						break;
				}
			} else {
				fn_801A45A0(lbl_1_bss_590[j][1], lbl_1_bss_640[j][1]);
			}
		}
	}
}
