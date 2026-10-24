#include "types.h"

// The s14WallSide family's EditOnChange (s14WallSideEditOnChange here): its first parameter is
// kept at its minimum at least.

typedef struct S14WallSideParams {
	f32 size; // 0x00
} S14WallSideParams;

typedef struct S14WallSideEdit {
	u8 unk00[0x2C];
	S14WallSideParams* params; // 0x2C
} S14WallSideEdit;

extern "C" const f32 s14WallSideEditMin[1];

extern "C" void s14WallSideEditOnChange(void* object, S14WallSideEdit* edit)
{
	S14WallSideParams* params = edit->params;
	const f32* min;

	if (params->size < *(min = s14WallSideEditMin)) {
		params->size = *min;
	}
}
