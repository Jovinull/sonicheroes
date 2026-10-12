// TObjBobcontainer::BrokenSE, the virtual that plays the breaking sound
// (0x1046) through the sound object at lbl_8042C388 when there is one;
// rel/unbr_bobcont_broken_se.cpp overrides it. The class is in
// game/obj_container.h.

#include "game/obj_container.h"

extern "C" void* lbl_8042C388;
extern "C" void fn_800B52E8(void* sound, s32 id, s32 arg2, s32 arg3);

void TObjBobcontainer::BrokenSE()
{
	if (lbl_8042C388 != NULL) {
		fn_800B52E8(lbl_8042C388, 0x1046, 0, 0);
	}
}
