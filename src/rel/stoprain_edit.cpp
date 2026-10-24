#include "types.h"

// The rain stopper's EditOnChange (stoprainEditOnChange here): its three
// sizes are kept at their minimum at least, two of the record's words are
// cleared, and its draw distance is kept at 0x80 at least.

typedef struct StoprainParams {
	f32 size0; // 0x00
	f32 size1; // 0x04
	f32 size2; // 0x08
} StoprainParams;

typedef struct StoprainEdit {
	u8 unk00[0xC];
	s32 e0C; // 0x0C
	u8 unk10[0x4];
	s32 e14; // 0x14
	u8 unk18[0x12];
	u8 distance; // 0x2A
	u8 unk2B;
	StoprainParams* params; // 0x2C
} StoprainEdit;

extern "C" const f32 stoprainEditMin[1];

extern "C" void stoprainEditOnChange(void* object, StoprainEdit* edit)
{
	StoprainParams* params = edit->params;
	const f32* min;

	if (params->size0 < *(min = stoprainEditMin)) {
		params->size0 = *min;
	}
	if (params->size1 < *(min = stoprainEditMin)) {
		params->size1 = *min;
	}
	if (params->size2 < *(min = stoprainEditMin)) {
		params->size2 = *min;
	}
	edit->e0C = 0;
	edit->e14 = 0;
	if (edit->distance < 0x80) {
		edit->distance = 0x80;
	}
}
