#include "types.h"

// The s13dBigfan family's EditOnChange (s13dBigfanEditOnChange here): its first parameter is
// kept at its minimum at least.

typedef struct S13dBigfanParams {
	f32 size; // 0x00
} S13dBigfanParams;

typedef struct S13dBigfanEdit {
	u8 unk00[0x2C];
	S13dBigfanParams* params; // 0x2C
} S13dBigfanEdit;

extern "C" const f32 s13dBigfanEditMin[1];

extern "C" void s13dBigfanEditOnChange(void* object, S13dBigfanEdit* edit)
{
	S13dBigfanParams* params = edit->params;
	const f32* min;

	if (params->size < *(min = s13dBigfanEditMin)) {
		params->size = *min;
	}
}
