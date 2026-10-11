#include "types.h"

// S20D WHALESTONE's EditOnChange (s20dWhalestoneEditOnChange here): it keeps the
// edited switch within 0..1.

typedef struct S20dWhalestoneParams {
	s8 mode; // 0x00
} S20dWhalestoneParams;

typedef struct S20dWhalestoneEdit {
	u8 unk00[0x2C];               // 0x00
	S20dWhalestoneParams* params; // 0x2C
} S20dWhalestoneEdit;

extern "C" void s20dWhalestoneEditOnChange(void* object, S20dWhalestoneEdit* edit)
{
	S20dWhalestoneParams* params = edit->params;

	if (params->mode < 0) {
		params->mode = 0;
	}
	if (params->mode >= 2) {
		params->mode = 1;
	}
}
