#include "types.h"

// The elevator's EditOnChange (s04dElevatorEditOnChange here): its two
// distances are kept at their minimum at least.

typedef struct S04dElevatorParams {
	u8 unk00[0x4];
	f32 range0; // 0x04
	f32 range1; // 0x08
} S04dElevatorParams;

typedef struct S04dElevatorEdit {
	u8 unk00[0x2C];
	S04dElevatorParams* params; // 0x2C
} S04dElevatorEdit;

extern "C" const f32 s04dElevatorEditMin[1];

extern "C" void s04dElevatorEditOnChange(void* object, S04dElevatorEdit* edit)
{
	S04dElevatorParams* params = edit->params;
	const f32* min;

	if (params->range0 < *(min = s04dElevatorEditMin)) {
		params->range0 = *min;
	}
	if (params->range1 < *(min = s04dElevatorEditMin)) {
		params->range1 = *min;
	}
}
