#include "types.h"

// The s14Koware family's EditOnChange (s14KowareEditOnChange here): its first parameter is
// kept at its minimum at least.

typedef struct S14KowareParams {
	f32 size; // 0x00
} S14KowareParams;

typedef struct S14KowareEdit {
	u8 unk00[0x2C];
	S14KowareParams* params; // 0x2C
} S14KowareEdit;

extern "C" const f32 s14KowareEditMin[1];

extern "C" void s14KowareEditOnChange(void* object, S14KowareEdit* edit)
{
	S14KowareParams* params = edit->params;
	const f32* min;

	if (params->size < *(min = s14KowareEditMin)) {
		params->size = *min;
	}
}
