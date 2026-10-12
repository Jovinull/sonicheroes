#include "types.h"

// The jumpPanel object's EditOnChange (jumpPanelEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct JumpPanelParams {
	f32 f00; // 0x00
	f32 f04; // 0x04
	s16 f08; // 0x08
} JumpPanelParams;

typedef struct JumpPanelEdit {
	u8 unk00[0x2C];
	JumpPanelParams* params; // 0x2C
} JumpPanelEdit;

extern "C" const f32 jumpPanelBound0[1];
extern "C" const f32 jumpPanelBound1[1];

extern "C" void jumpPanelEditOnChange(void* object, JumpPanelEdit* edit)
{
	JumpPanelParams* params = edit->params;
	const f32* limit;

	if (params->f00 < *(limit = jumpPanelBound0)) {
		params->f00 = *limit;
	}
	if (params->f00 > *(limit = jumpPanelBound1)) {
		params->f00 = *limit;
	}
	if (params->f04 < *(limit = jumpPanelBound0)) {
		params->f04 = *limit;
	}
	if (params->f04 > *(limit = jumpPanelBound1)) {
		params->f04 = *limit;
	}
	if (params->f08 < 0) {
		params->f08 = 0;
	}
	if (params->f08 > 32767) {
		params->f08 = 32767;
	}
}
