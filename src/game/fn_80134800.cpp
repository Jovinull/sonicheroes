// Saves the current player's live record into its slot of the record table (HYPOTHESIS; names
// inferred): remembers the player number (lbl_8042C7B4) and copies the player's 0x38-byte record
// from lbl_803EC208 into row `player`, column fn_8004E608(lbl_8042C1F8) of lbl_803EB408 (16
// records per row).
#include "types.h"

struct Pair80134800 {
	s32 a; // 0x0
	s32 b; // 0x4
};

struct Record80134800 {
	f32 value0;          // 0x0
	f32 value4;          // 0x4
	f32 value8;          // 0x8
	f32 valueC;          // 0xC
	f32 value10;         // 0x10
	s32 value14;         // 0x14
	s32 value18;         // 0x18
	Pair80134800 pair1C; // 0x1C
	s32 value24;         // 0x24
	Pair80134800 pair28; // 0x28
	s32 value30;         // 0x30
	f32 value34;         // 0x34
};

extern "C" {
extern Record80134800 lbl_803EC208[];
extern Record80134800 lbl_803EB408[][16];
extern s32 lbl_8042C1FC;
extern s32 lbl_8042C7B4;
extern void* lbl_8042C1F8;
s32 fn_8004E608(void* context);

void fn_80134800(void)
{
	Record80134800* record;

	lbl_8042C7B4                                          = lbl_8042C1FC;
	record                                                = &lbl_803EC208[lbl_8042C1FC];
	lbl_803EB408[lbl_8042C7B4][fn_8004E608(lbl_8042C1F8)] = *record;
}
}
