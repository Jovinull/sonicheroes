// Copies the record of the current player lbl_8042C1FC from the table lbl_803EA4E8 (0x44-byte
// records) into the output (HYPOTHESIS: a camera or player state snapshot). The retail code
// copies the four leading words and the float one by one and the four 12-byte vectors as word
// blocks. Field names are inferred from this function only.
#include "types.h"

// Three-component vector copied as plain words.
struct VecWords801310C8 {
	u32 w[3];
};

struct Record801310C8 {
	s32 word0;              // 0x0
	s32 word4;              // 0x4
	s32 word8;              // 0x8
	s32 wordC;              // 0xC
	VecWords801310C8 vec10; // 0x10
	VecWords801310C8 vec1C; // 0x1C
	VecWords801310C8 vec28; // 0x28
	VecWords801310C8 vec34; // 0x34
	f32 value40;            // 0x40
};

extern "C" {
extern s32 lbl_8042C1FC;
extern Record801310C8 lbl_803EA4E8[];

void fn_801310C8(Record801310C8* out)
{
	s32 player = lbl_8042C1FC;

	out->word0   = lbl_803EA4E8[player].word0;
	out->word4   = lbl_803EA4E8[player].word4;
	out->word8   = lbl_803EA4E8[player].word8;
	out->wordC   = lbl_803EA4E8[player].wordC;
	out->vec10   = lbl_803EA4E8[player].vec10;
	out->vec1C   = lbl_803EA4E8[player].vec1C;
	out->vec28   = lbl_803EA4E8[player].vec28;
	out->vec34   = lbl_803EA4E8[player].vec34;
	out->value40 = lbl_803EA4E8[player].value40;
}
}
