#include "types.h"

// Works out which of the seven entries the player has enough emblems for, then
// swaps the model of every one they do not.
//
// The translation unit is the single function fn_1_EF8C, .text 0xEF8C to
// 0xF06C. The thresholds it reads sit at .rodata 0x193C and the two model
// tables in .bss at 0x738 and 0x7A8; all three are left to the module and only
// referenced here, so this unit emits neither section.
//
// The second table is not walked. The original advances the first by a pair
// each turn of the loop and keeps reading the same pair out of the second,
// which is what the code below says.

typedef struct Panel {
	u8 unk0[0x370];  // 0x000
	s32 unlocked[7]; // 0x370
} Panel;

typedef struct SaveState {
	u8 padding[0x22]; // 0x00
	u8 emblems;       // 0x22
} SaveState;

extern "C" const u8 lbl_1_rodata_193C[];
extern "C" void* lbl_1_bss_738[7][2];
extern "C" void* lbl_1_bss_7A8[4];
extern "C" u8 lbl_803E774C[];

extern "C" SaveState* fn_80116D2C(void* state);
extern "C" void fn_801A45A0(void* object, void* model);

extern "C" void fn_1_EF8C(Panel* panel)
{
	SaveState* save;
	u32 i;

	save = fn_80116D2C(lbl_803E774C);
	for (i = 0; i < 7; i++) {
		if (lbl_1_rodata_193C[i] <= save->emblems) {
			panel->unlocked[i] = 1;
		} else {
			panel->unlocked[i] = 0;
		}
	}

	for (i = 0; i != 7; i++) {
		if (panel->unlocked[i] == 0) {
			fn_801A45A0(lbl_1_bss_738[i][0], lbl_1_bss_7A8[0]);
			fn_801A45A0(lbl_1_bss_738[i][1], lbl_1_bss_7A8[1]);
		}
	}
}
