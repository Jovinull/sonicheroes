#include "types.h"

// The s13SenkanBelt family's EditOnChange (s13SenkanBeltEditOnChange here): its first parameter is
// kept at its minimum at least.

typedef struct S13SenkanBeltParams {
	f32 size; // 0x00
} S13SenkanBeltParams;

typedef struct S13SenkanBeltEdit {
	u8 unk00[0x2C];
	S13SenkanBeltParams* params; // 0x2C
} S13SenkanBeltEdit;

extern "C" const f32 s13SenkanBeltEditMin[1];

extern "C" void s13SenkanBeltEditOnChange(void* object, S13SenkanBeltEdit* edit)
{
	S13SenkanBeltParams* params = edit->params;
	const f32* min;

	if (params->size < *(min = s13SenkanBeltEditMin)) {
		params->size = *min;
	}
}
