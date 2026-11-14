// Installs the key-frame callbacks registered for a key-frame type into an interpolator
// (HYPOTHESIS: RtAnimInterpolatorSetKeyFrameCallBacks with RtAnimGetInterpolatorInfo inlined):
// looks the type up in the table lbl_8040EBA4 of lbl_8042CF78 registered 0x30-byte records and
// copies its four callbacks to 0x3C-0x48. An unknown type records error 2 of plugin 0x1B7 (with
// the type) and returns 0; otherwise returns 1.
#include "game/rt_anim.h"

struct Interpolator8020C864 {
	u8 pad0[0x3C];
	void* callbacks[4]; // 0x3C
};

static inline RtAnimInterpolatorInfo* GetInterpolatorInfo(s32 typeID)
{
	s32 i;
	for (i = 0; i < lbl_8042CF78; i++) {
		if (typeID == lbl_8040EBA4[i].typeID) {
			return &lbl_8040EBA4[i];
		}
	}
	RwError error;
	error.pluginID  = RT_ANIM_PLUGIN_ID;
	error.errorCode = fn_8019408C(2, typeID);
	fn_80193FE8(&error);
	return 0;
}

extern "C" {
s32 fn_8020C864(Interpolator8020C864* interpolator, s32 typeID)
{
	RtAnimInterpolatorInfo* info = GetInterpolatorInfo(typeID);

	if (!info) {
		return 0;
	}
	interpolator->callbacks[0] = info->callbacks[0];
	interpolator->callbacks[1] = info->callbacks[1];
	interpolator->callbacks[2] = info->callbacks[2];
	interpolator->callbacks[3] = info->callbacks[3];
	return 1;
}
}
