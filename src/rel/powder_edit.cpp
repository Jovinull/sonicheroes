#include "types.h"

// The powder's EditOnChange (powderEditOnChange here): unset sizes get their
// defaults and the first is kept at its minimum, its kind is kept between 0
// and 2, its count between 1 and 0x7D, and its interval at 10 at least.

typedef struct PowderParams {
	f32 size;     // 0x00
	s32 kind;     // 0x04
	s32 count;    // 0x08
	s32 interval; // 0x0C
	f32 height;   // 0x10
	f32 width;    // 0x14
} PowderParams;

typedef struct PowderEdit {
	u8 unk00[0x2C];
	PowderParams* params; // 0x2C
} PowderEdit;

extern "C" const f32 powderEditUnset[1];
extern "C" const f32 powderEditDefault[1];
extern "C" const f32 powderEditMin[1];

extern "C" void powderEditOnChange(void* object, PowderEdit* edit)
{
	PowderParams* params = edit->params;
	const f32* min;

	if (*powderEditUnset == params->size) {
		params->size = *powderEditDefault;
	}
	if (params->size < *(min = powderEditMin)) {
		params->size = *min;
	}
	if (params->kind < 0) {
		params->kind = 0;
	}
	if (*powderEditUnset == params->width) {
		params->width = *powderEditMin;
	}
	if (params->height <= *powderEditUnset) {
		params->height = *powderEditMin;
	}
	if (params->kind >= 3) {
		params->kind = 2;
	}
	if (params->count < 1) {
		params->count = 1;
	}
	if (params->count >= 0x80) {
		params->count = 0x7D;
	}
	if (params->interval <= 10) {
		params->interval = 10;
	}
}
