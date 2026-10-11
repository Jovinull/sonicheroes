#include "types.h"

// The slotlarge object's EditOnChange (slotlargeEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct SlotlargeParams {
	s32 f00; // 0x00
} SlotlargeParams;

typedef struct SlotlargeEdit {
	u8 unk00[0x2C];
	SlotlargeParams* params; // 0x2C
} SlotlargeEdit;

extern "C" void slotlargeEditOnChange(void* object, SlotlargeEdit* edit)
{
	SlotlargeParams* params = edit->params;

	if (params->f00 < 1) {
		params->f00 = 1;
	}
	if (params->f00 > 2) {
		params->f00 = 2;
	}
}
