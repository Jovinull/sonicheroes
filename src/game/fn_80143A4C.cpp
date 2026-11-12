// Unpacks the packed settings word at *arg1 into nine fields (2/2/3/4/3/3/1/1/2 bits from bit 0).

#include "types.h"

typedef struct {
	u32 unk0;
	u32 unk4;
	u32 unk8;
	u32 unkC;
	u32 unk10;
	u32 unk14;
	u8 unk18;
	u8 unk19;
	u32 unk1C;
} UnkStruct;

extern "C" void fn_80143A4C(UnkStruct* arg0, u32* arg1)
{
	u32 temp_r9 = *arg1;

	arg0->unk0  = temp_r9 & 3;
	arg0->unk4  = (temp_r9 >> 2) & 3;
	arg0->unk8  = (temp_r9 >> 4) & 7;
	arg0->unkC  = (temp_r9 >> 7) & 0xF;
	arg0->unk10 = (temp_r9 >> 11) & 7;
	arg0->unk14 = (temp_r9 >> 14) & 7;
	arg0->unk18 = (temp_r9 >> 17) & 1;
	arg0->unk19 = (temp_r9 >> 18) & 1;
	arg0->unk1C = (temp_r9 >> 19) & 3;
}
