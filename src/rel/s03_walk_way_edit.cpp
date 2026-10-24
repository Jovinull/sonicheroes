#include "types.h"

// The walkway's EditOnChange (s03WalkWayEditOnChange here): its three
// distances are kept at zero at least.

typedef struct S03WalkWayParams {
	u8 unk00[0x4];
	f32 range0; // 0x04
	f32 range1; // 0x08
	f32 range2; // 0x0C
} S03WalkWayParams;

typedef struct S03WalkWayEdit {
	u8 unk00[0x2C];
	S03WalkWayParams* params; // 0x2C
} S03WalkWayEdit;

extern "C" const f32 s03WalkWayZero[1];

extern "C" void s03WalkWayEditOnChange(void* object, S03WalkWayEdit* edit)
{
	S03WalkWayParams* params = edit->params;
	const f32* zero;

	if (params->range0 < *(zero = s03WalkWayZero)) {
		params->range0 = *zero;
	}
	if (params->range1 < *(zero = s03WalkWayZero)) {
		params->range1 = *zero;
	}
	if (params->range2 < *(zero = s03WalkWayZero)) {
		params->range2 = *zero;
	}
}
