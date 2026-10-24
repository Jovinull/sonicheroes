#include "types.h"

// The far battleships' EditOnChange (s13dSenkanFarMoveEditOnChange here; the
// class is TObjS13ShipFarMove, whose vtable holds it): its two delays are kept
// at zero at least, its two counts between 1 and 10, and its three distances
// at their minimum at least.

typedef struct S13dSenkanFarMoveParams {
	s8 count0;  // 0x00
	s8 count1;  // 0x01
	s16 delay0; // 0x02
	s16 delay1; // 0x04
	u8 unk06[0x2];
	f32 range0; // 0x08
	f32 range1; // 0x0C
	f32 range2; // 0x10
} S13dSenkanFarMoveParams;

typedef struct S13dSenkanFarMoveEdit {
	u8 unk00[0x2C];
	S13dSenkanFarMoveParams* params; // 0x2C
} S13dSenkanFarMoveEdit;

extern "C" const f32 s13dSenkanFarMoveEditMin[1];

extern "C" void s13dSenkanFarMoveEditOnChange(void* object, S13dSenkanFarMoveEdit* edit)
{
	S13dSenkanFarMoveParams* params = edit->params;
	const f32* min;

	if (params->delay0 < 0) {
		params->delay0 = 0;
	}
	if (params->delay1 < 0) {
		params->delay1 = 0;
	}
	if (params->count0 < 1) {
		params->count0 = 1;
	}
	if (params->count0 > 10) {
		params->count0 = 10;
	}
	if (params->count1 < 1) {
		params->count1 = 1;
	}
	if (params->count1 > 10) {
		params->count1 = 10;
	}
	if (params->range0 < *(min = s13dSenkanFarMoveEditMin)) {
		params->range0 = *min;
	}
	if (params->range1 < *(min = s13dSenkanFarMoveEditMin)) {
		params->range1 = *min;
	}
	if (params->range2 < *(min = s13dSenkanFarMoveEditMin)) {
		params->range2 = *min;
	}
}
