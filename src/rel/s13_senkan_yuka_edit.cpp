#include "types.h"

// The battleship floor board's EditOnChange (s13FBoardEditOnChange here; the
// class is TObjS13FBoard, registered as s13SenkanYuka): its count and two
// distances are kept at zero at least, a negative speed gets its default and
// the speed is kept at 1 at most, and its offset is kept within its distance
// on either side.

typedef struct S13FBoardParams {
	s16 count; // 0x00
	u8 unk02[0x2];
	f32 range0; // 0x04
	f32 range1; // 0x08
	f32 offset; // 0x0C
	f32 speed;  // 0x10
} S13FBoardParams;

typedef struct S13FBoardEdit {
	u8 unk00[0x2C];
	S13FBoardParams* params; // 0x2C
} S13FBoardEdit;

extern "C" const f32 s13FBoardOne[1];
extern "C" const f32 s13FBoardZero[1];
extern "C" const f32 s13FBoardDefaultSpeed[1];

extern "C" void s13FBoardEditOnChange(void* object, S13FBoardEdit* edit)
{
	S13FBoardParams* params = edit->params;
	const f32* limit;

	if (params->count < 0) {
		params->count = 0;
	}
	if (params->range0 < *(limit = s13FBoardZero)) {
		params->range0 = *limit;
	}
	if (params->range1 < *(limit = s13FBoardZero)) {
		params->range1 = *limit;
	}
	if (params->speed < *s13FBoardZero) {
		params->speed = *s13FBoardDefaultSpeed;
	}
	if (params->speed > *(limit = s13FBoardOne)) {
		params->speed = *limit;
	}
	if (params->offset >= *s13FBoardZero && params->offset > params->range1) {
		params->offset = params->range1;
	}
	if (params->offset < *s13FBoardZero && params->offset < params->range1) {
		params->offset = -params->range1;
	}
}
