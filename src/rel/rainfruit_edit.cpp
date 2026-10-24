#include "types.h"

// The rain fruit's EditOnChange (rainfruitEditOnChange here): the record's
// draw distance is kept at 0x80 at least and its kind between 0 and 2.

typedef struct RainfruitParams {
	u8 unk00[0xA];
	s16 kind; // 0x0A
} RainfruitParams;

typedef struct RainfruitEdit {
	u8 unk00[0x2A];
	u8 distance; // 0x2A
	u8 unk2B;
	RainfruitParams* params; // 0x2C
} RainfruitEdit;

extern "C" void rainfruitEditOnChange(void* object, RainfruitEdit* edit)
{
	RainfruitParams* params = edit->params;

	if (edit->distance < 0x80) {
		edit->distance = 0x80;
	}
	if (params->kind > 2) {
		params->kind = 2;
	}
	if (params->kind < 0) {
		params->kind = 0;
	}
}
