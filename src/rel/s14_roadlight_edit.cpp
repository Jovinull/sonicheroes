#include "types.h"

// The s14Roadlight family's EditOnChange (s14RoadlightEditOnChange here): its two distances are kept at their
// minimum at least.

typedef struct S14RoadlightParams {
	f32 range0; // 0x00
	f32 range1; // 0x04
} S14RoadlightParams;

typedef struct S14RoadlightEdit {
	u8 unk00[0x2C];
	S14RoadlightParams* params; // 0x2C
} S14RoadlightEdit;

extern "C" const f32 s14RoadlightEditMin[1];

extern "C" void s14RoadlightEditOnChange(void* object, S14RoadlightEdit* edit)
{
	S14RoadlightParams* params = edit->params;
	const f32* limit;

	if (params->range0 < *(limit = s14RoadlightEditMin)) {
		params->range0 = *limit;
	}
	if (params->range1 < *(limit = s14RoadlightEditMin)) {
		params->range1 = *limit;
	}
}
