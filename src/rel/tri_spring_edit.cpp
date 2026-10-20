#include "types.h"

// TObjTriSpring::EditOnChange (the PS2 build's name): keeps each edited
// parameter within its bounds and names the editor's kind field by the kind's
// value.

typedef struct TriSpringParams {
	f32 f00; // 0x00
	f32 f04; // 0x04
	s16 f08; // 0x08
	s8 f0A;  // 0x0A
} TriSpringParams;

typedef struct TriSpringEdit {
	u8 unk00[0x2C];
	TriSpringParams* params; // 0x2C
} TriSpringEdit;

typedef struct TriSpringChoice {
	const char* name; // 0x00
	s32 value;        // 0x04
} TriSpringChoice;

extern "C" const char* triSpringLabels[4];
extern "C" TriSpringChoice triSpringChoices[12];
extern "C" const f32 triSpringBound0[1];
extern "C" const f32 triSpringBound1[1];
extern "C" const f32 triSpringBound2[1];
extern "C" const f32 triSpringBound3[1];

extern "C" void EditOnChange__13TObjTriSpringFP13SETDATA_PARAM(void* object, TriSpringEdit* edit)
{
	TriSpringParams* params = edit->params;
	const f32* limit;

	if (params->f00 < *(limit = triSpringBound1)) {
		params->f00 = *limit;
	}
	if (params->f00 > *(limit = triSpringBound2)) {
		params->f00 = *limit;
	}
	if (params->f04 < *(limit = triSpringBound3)) {
		params->f04 = *limit;
	}
	if (params->f04 > *(limit = triSpringBound0)) {
		params->f04 = *limit;
	}
	if (params->f08 < 0) {
		params->f08 = 0;
	}
	if (params->f08 > 0x7FFF) {
		params->f08 = 0x7FFF;
	}
	if (params->f0A < 0) {
		params->f0A = 0;
	}
	if (params->f0A > 13) {
		params->f0A = 12;
	}
	triSpringLabels[3] = triSpringChoices[params->f0A].name;
}
