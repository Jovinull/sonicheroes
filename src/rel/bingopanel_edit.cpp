#include "types.h"

// The bingo panel's EditOnChange (bingopanelEditOnChange here): an unset size
// gets its default and is kept at its minimum, the record's draw distance is
// set when it is zero, and its kind is kept at 0 or 1.

typedef struct BingopanelParams {
	f32 size; // 0x00
	s32 kind; // 0x04
} BingopanelParams;

typedef struct BingopanelEdit {
	u8 unk00[0x2A];
	u8 distance; // 0x2A
	u8 unk2B;
	BingopanelParams* params; // 0x2C
} BingopanelEdit;

extern "C" const f32 bingopanelEditUnset[1];
extern "C" const f32 bingopanelEditDefault[1];
extern "C" const f32 bingopanelEditMin[1];

extern "C" void bingopanelEditOnChange(void* object, BingopanelEdit* edit)
{
	BingopanelParams* params = edit->params;
	const f32* min;

	if (*bingopanelEditUnset == params->size) {
		params->size = *bingopanelEditDefault;
	}
	if (params->size < *(min = bingopanelEditMin)) {
		params->size = *min;
	}
	if (edit->distance == 0) {
		edit->distance = 1;
	}
	if (params->kind < 0) {
		params->kind = 0;
	}
	if (params->kind > 1) {
		params->kind = 1;
	}
}
