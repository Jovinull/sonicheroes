#include "types.h"

// The laser fence's EditOnChange (laserFenceEditOnChange here): it keeps the
// edited kind between 0 and 4 and the width and height within their limits,
// keeps only the low byte of the value for kinds 2 and 4, and names the
// editor's kind and value fields for the kind.

typedef struct LaserFenceParams {
	s32 kind;   // 0x00
	f32 width;  // 0x04
	f32 height; // 0x08
	s32 value;  // 0x0C
} LaserFenceParams;

typedef struct LaserFenceEdit {
	u8 unk00[0x2C];
	LaserFenceParams* params; // 0x2C
} LaserFenceEdit;

extern "C" const char* laserFenceFieldNames[];
extern "C" const char* laserFenceKindFields[];
extern "C" const char* laserFenceValueFields[];
extern "C" const f32 laserFenceMinEdit[1];
extern "C" const f32 laserFenceMaxEdit[1];

extern "C" void laserFenceEditOnChange(void* object, LaserFenceEdit* edit)
{
	LaserFenceParams* params = edit->params;
	const f32* limit;

	if (params->kind < 0) {
		params->kind = 0;
	}
	if (params->kind >= 5) {
		params->kind = 4;
	}
	if (params->width < *(limit = laserFenceMinEdit)) {
		params->width = *limit;
	}
	if (params->width > *(limit = laserFenceMaxEdit)) {
		params->width = *limit;
	}
	if (params->height < *(limit = laserFenceMinEdit)) {
		params->height = *limit;
	}
	if (params->height > *(limit = laserFenceMaxEdit)) {
		params->height = *limit;
	}
	if (params->kind == 2 || params->kind == 4) {
		params->value = (u8)params->value;
	}
	laserFenceFieldNames[0] = laserFenceKindFields[params->kind];
	laserFenceFieldNames[3] = laserFenceValueFields[params->kind];
}
