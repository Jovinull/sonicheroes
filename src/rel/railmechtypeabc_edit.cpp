#include "types.h"

// The mechanical rail's EditOnChange (railmechtypeabcEditOnChange here): each
// of its three sizes left unset gets its default.

typedef struct RailmechtypeabcParams {
	f32 size0; // 0x00
	f32 size1; // 0x04
	f32 size2; // 0x08
} RailmechtypeabcParams;

typedef struct RailmechtypeabcEdit {
	u8 unk00[0x2C];
	RailmechtypeabcParams* params; // 0x2C
} RailmechtypeabcEdit;

extern "C" const f32 railmechtypeabcEditUnset[1];
extern "C" const f32 railmechtypeabcEditDefault[1];

extern "C" void railmechtypeabcEditOnChange(void* object, RailmechtypeabcEdit* edit)
{
	RailmechtypeabcParams* params = edit->params;

	if (*railmechtypeabcEditUnset == params->size0) {
		params->size0 = *railmechtypeabcEditDefault;
	}
	if (*railmechtypeabcEditUnset == params->size1) {
		params->size1 = *railmechtypeabcEditDefault;
	}
	if (*railmechtypeabcEditUnset == params->size2) {
		params->size2 = *railmechtypeabcEditDefault;
	}
}
