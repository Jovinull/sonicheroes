#include "types.h"

typedef struct HintMessage {
	u8 unk00[0x30];
	s32 unk30; // 0x30
	u8 unk34[0x8];
	s32 unk3C; // 0x3C
	u8 unk40[0x18];
	s32 unk58; // 0x58
} HintMessage;

extern "C" u8 fn_16_49BD8(HintMessage* arg0)
{
	s32 var_r31;
	u8 var_r30;

	var_r31 = 0;
	var_r30 = 0;
	if (arg0->unk30 == 0 && arg0->unk3C == 0) {
		var_r30 = 1;
	}
	if (var_r30 != 0 && arg0->unk58 == -1) {
		var_r31 = 1;
	}
	return var_r31;
}
