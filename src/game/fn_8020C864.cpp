// Installs the key-frame callbacks registered for a key-frame type into an interpolator
// (HYPOTHESIS: RtAnimInterpolatorSetKeyFrameCallBacks with RtAnimGetInterpolatorInfo inlined):
// looks the type up in the table lbl_8040EBA4 of lbl_8042CF78 registered 0x30-byte records and
// copies its four callbacks to 0x3C-0x48. An unknown type records error 2 of plugin 0x1B7 (with
// the type) and returns 0; otherwise returns 1.
#include "game/rw_engine.h"

// Registered key-frame type (only the type ID and the copied callbacks are known).
struct InterpolatorInfo8020C864 {
	s32 typeID; // 0x0
	u8 pad4[0x8];
	void* callbacks[4]; // 0xC
	u8 pad1C[0x30 - 0x1C];
};

struct Interpolator8020C864 {
	u8 pad0[0x3C];
	void* callbacks[4]; // 0x3C
};

extern "C" {
extern InterpolatorInfo8020C864 lbl_8040EBA4[];
extern s32 lbl_8042CF78;
}

static inline InterpolatorInfo8020C864* GetInterpolatorInfo(s32 typeID)
{
	s32 i;
	for (i = 0; i < lbl_8042CF78; i++) {
		if (typeID == lbl_8040EBA4[i].typeID) {
			return &lbl_8040EBA4[i];
		}
	}
	RwError error;
	error.pluginID  = 0x1B7;
	error.errorCode = fn_8019408C(2, typeID);
	fn_80193FE8(&error);
	return 0;
}

extern "C" {
s32 fn_8020C864(Interpolator8020C864* interpolator, s32 typeID)
{
	InterpolatorInfo8020C864* info = GetInterpolatorInfo(typeID);

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
