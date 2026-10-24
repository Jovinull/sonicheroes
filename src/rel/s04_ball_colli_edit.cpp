#include "types.h"

// The ball collision's EditOnChange (s04BallColliEditOnChange here): its first parameter is
// kept at zero at least.

typedef struct S04BallColliParams {
	f32 size; // 0x00
} S04BallColliParams;

typedef struct S04BallColliEdit {
	u8 unk00[0x2C];
	S04BallColliParams* params; // 0x2C
} S04BallColliEdit;

extern "C" const f32 s04BallColliZero[1];

extern "C" void s04BallColliEditOnChange(void* object, S04BallColliEdit* edit)
{
	S04BallColliParams* params = edit->params;
	const f32* min;

	if (params->size < *(min = s04BallColliZero)) {
		params->size = *min;
	}
}
