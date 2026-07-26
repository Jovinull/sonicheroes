#include "types.h"

// TObjDashpanel's parameter guard, the last slot of its second base's vtable.
// The shortest of the family: two fields, no labels to refresh.
//
// The claim is .text 0x81C0 to 0x8228 and .rodata 0x160 to 0x168. The two
// limits are read here and nowhere else in the module, and they start on an
// eight byte boundary, so unlike the other guards this one can take its own
// constants rather than reaching them as externals.
//
// The code is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out, as everywhere
// else.

typedef struct DashpanelParams {
	f32 power;      // 0x00
	s16 noCtrlTime; // 0x04
} DashpanelParams;

typedef struct Frame {
	u8 unk0[0x2C];           // 0x00
	DashpanelParams* params; // 0x2C
} Frame;

// The object it is called on is not used: everything it touches hangs off the
// keyframe it is handed.
extern "C" void dashpanelClamp(void* object, Frame* frame)
{
	DashpanelParams* params = frame->params;

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
