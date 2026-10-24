#include "types.h"

// The warp position's EditOnChange (s23WarpPosEditOnChange here): its first parameter is
// kept at its minimum at least.

typedef struct S23WarpPosParams {
	f32 size; // 0x00
} S23WarpPosParams;

typedef struct S23WarpPosEdit {
	u8 unk00[0x2C];
	S23WarpPosParams* params; // 0x2C
} S23WarpPosEdit;

extern "C" const f32 s23WarpPosEditMin[1];

extern "C" void s23WarpPosEditOnChange(void* object, S23WarpPosEdit* edit)
{
	S23WarpPosParams* params = edit->params;
	const f32* min;

	if (params->size < *(min = s23WarpPosEditMin)) {
		params->size = *min;
	}
}
