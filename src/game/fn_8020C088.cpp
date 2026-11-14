// Registers a key-frame interpolation scheme (HYPOTHESIS: RtAnimRegisterInterpolationScheme):
// copies it into the next free slot of lbl_8040EBA4 and counts it. Returns 1; a full table
// records error 1 and a type that is already registered error 0 of the animation plugin (0x1B7),
// both returning 0.
// NonMatching: the retail code copies the scheme in load/store word pairs and reloads the count
// after the copy; ours interleaves the copy and keeps the count (27 words differ).
#include "game/rt_anim.h"

extern "C" {
s32 fn_8020C088(const RtAnimInterpolatorInfo* info)
{
	if (lbl_8042CF78 < RT_ANIM_MAX_INTERPOLATORS) {
		s32 i;
		for (i = 0; i < lbl_8042CF78; i++) {
			if (info->typeID == lbl_8040EBA4[i].typeID) {
				RwError error;
				error.pluginID  = RT_ANIM_PLUGIN_ID;
				error.errorCode = fn_8019408C(0);
				fn_80193FE8(&error);
				return 0;
			}
		}
		lbl_8040EBA4[lbl_8042CF78] = *info;
		lbl_8042CF78++;
		return 1;
	}
	{
		RwError error;
		error.pluginID  = RT_ANIM_PLUGIN_ID;
		error.errorCode = fn_8019408C(1);
		fn_80193FE8(&error);
	}
	return 0;
}
}
