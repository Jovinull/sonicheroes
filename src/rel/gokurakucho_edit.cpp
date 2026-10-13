#include "types.h"

// The gokurakucho object's EditOnChange (gokurakuchoEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct GokurakuchoParams {
	f32 f00; // 0x00
	u8 pad04[0x4];
	f32 f08; // 0x08
} GokurakuchoParams;

typedef struct GokurakuchoEdit {
	u8 unk00[0x2C];
	GokurakuchoParams* params; // 0x2C
} GokurakuchoEdit;

extern "C" const f32 gokurakuchoZero[1];

extern "C" void gokurakuchoEditOnChange(void* object, GokurakuchoEdit* edit)
{
	GokurakuchoParams* params = edit->params;
	const f32* limit;

	if (params->f08 < *(limit = gokurakuchoZero)) {
		params->f08 = *limit;
	}
	if (params->f00 < *(limit = gokurakuchoZero)) {
		params->f00 = *limit;
	}
}
