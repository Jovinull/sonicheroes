#include "types.h"

// S20D CURBSTONE's EditOnChange (s20dCurbstoneEditOnChange here): it keeps the
// edited switch within 0..1.

typedef struct S20dCurbstoneParams {
	s8 mode; // 0x00
} S20dCurbstoneParams;

typedef struct S20dCurbstoneEdit {
	u8 unk00[0x2C];              // 0x00
	S20dCurbstoneParams* params; // 0x2C
} S20dCurbstoneEdit;

extern "C" void s20dCurbstoneEditOnChange(void* object, S20dCurbstoneEdit* edit)
{
	S20dCurbstoneParams* params = edit->params;

	if (params->mode < 0) {
		params->mode = 0;
	}
	if (params->mode >= 2) {
		params->mode = 1;
	}
}
