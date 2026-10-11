#include "types.h"

// The dash ring's EditOnChange (dashRingEditOnChange here): it keeps the
// edited power within -5 to 30 and the no-control time a non negative count
// of frames. The shape is TObjSpring's guard (rel/spring_clamp.inc) with a
// higher top power.

typedef struct DashRingParams {
	f32 power;      // 0x00
	s16 noCtrlTime; // 0x04
} DashRingParams;

typedef struct DashRingEdit {
	u8 unk0[0x2C];          // 0x00
	DashRingParams* params; // 0x2C
} DashRingEdit;

extern "C" void dashRingEditOnChange(void* object, DashRingEdit* edit)
{
	DashRingParams* params = edit->params;

	if (params->power < -5.0f) {
		params->power = -5.0f;
	}
	if (params->power > 30.0f) {
		params->power = 30.0f;
	}
	if (params->noCtrlTime < 0) {
		params->noCtrlTime = 0;
	}
	if (params->noCtrlTime > 0x7FFF) {
		params->noCtrlTime = 0x7FFF;
	}
}
