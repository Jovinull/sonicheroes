#include "types.h"

// The s13SenkanMov family's EditOnChange (s13SenkanMovEditOnChange here): its first parameter is
// kept at its minimum at least.

typedef struct S13SenkanMovParams {
	f32 size; // 0x00
} S13SenkanMovParams;

typedef struct S13SenkanMovEdit {
	u8 unk00[0x2C];
	S13SenkanMovParams* params; // 0x2C
} S13SenkanMovEdit;

extern "C" const f32 s13SenkanMovEditMin[1];

extern "C" void s13SenkanMovEditOnChange(void* object, S13SenkanMovEdit* edit)
{
	S13SenkanMovParams* params = edit->params;
	const f32* min;

	if (params->size < *(min = s13SenkanMovEditMin)) {
		params->size = *min;
	}
}
