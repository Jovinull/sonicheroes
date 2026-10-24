#include "types.h"

// The s13HoudaiFumi family's EditOnChange (s13HoudaiFumiEditOnChange here): its size is kept between its minimum
// and its maximum.

typedef struct S13HoudaiFumiParams {
	f32 size; // 0x00
} S13HoudaiFumiParams;

typedef struct S13HoudaiFumiEdit {
	u8 unk00[0x2C];
	S13HoudaiFumiParams* params; // 0x2C
} S13HoudaiFumiEdit;

extern "C" const f32 s13HoudaiFumiEditMax[1];
extern "C" const f32 s13HoudaiFumiEditMin[1];

extern "C" void s13HoudaiFumiEditOnChange(void* object, S13HoudaiFumiEdit* edit)
{
	S13HoudaiFumiParams* params = edit->params;
	const f32* limit;

	if (params->size > *(limit = s13HoudaiFumiEditMax)) {
		params->size = *limit;
	}
	if (params->size < *(limit = s13HoudaiFumiEditMin)) {
		params->size = *limit;
	}
}
