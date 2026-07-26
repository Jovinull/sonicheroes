#include "types.h"

// TObjDashpanel, as far as it has been carved: the parameter guard and the two
// asset hooks after it.
//
// The guard is the last slot of the class's second base's vtable, the shortest
// of that family: two fields, no labels to refresh.
//
// The claim is .text 0x81C0 to 0x8314 and .rodata 0x160 to 0x168. The two
// limits are read here and nowhere else in the module, and they start on an
// eight byte boundary, so unlike the other guards this one can take its own
// constants rather than reaching them as externals. The three blocks the hooks
// fill in stay with the module and are reached as externals.
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

extern "C" void* fn_8005C014(void* handle, void** slot);
extern "C" void* fn_8005E1DC(void* model, s32 index, const char* name);
extern "C" u8* fn_8005E410(void* model, s32 index, const char* name);
extern "C" void* fn_8005EA04(const char* name);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void* dashpanelModel;
extern "C" u8* dashpanelMaterial;
extern "C" void* dashpanelEffect;
extern "C" void* stageUvAnim;
extern "C" char dashpanelModelName[];
extern "C" char dashpanelTextureName[];
extern "C" char dashpanelEffectName[];

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

extern "C" void dashpanelUnload(void)
{
	dashpanelModel    = NULL;
	dashpanelMaterial = NULL;
	dashpanelEffect   = NULL;
}

// Loads the panel's model and the sliding texture that runs along it. The
// second half only runs when both the UV animation and the material it drives
// are there, since one is fed into the other.
extern "C" void dashpanelLoad(void)
{
	dashpanelModel = fn_8005EA04(dashpanelModelName);
	if (dashpanelModel != NULL) {
		dashpanelMaterial = fn_8005E410(dashpanelModel, 0, dashpanelTextureName);
	}

	dashpanelEffect = fn_8005EA04(dashpanelEffectName);
	if (dashpanelEffect != NULL && dashpanelMaterial != NULL) {
		stageUvAnim = dashpanelEffect;
		fn_8005C014(fn_8005E1DC(dashpanelModel, 0, dashpanelTextureName), &stageUvAnim);
	}
}
