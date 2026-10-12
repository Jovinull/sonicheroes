// TObjBobcontUnbreakable::BrokenSE: the unbreakable bobsleigh crate plays its
// own sound (0x1048) through the sound object at lbl_8042C388 when there is
// one. The class is shared through unbr_bobcont_class.inc.

#define UNBR_BOBCONT_CTOR inline
#include "src/rel/unbr_bobcont_class.inc"

extern "C" void* lbl_8042C388;
extern "C" void fn_800B52E8(void* sound, s32 id, s32 arg2, s32 arg3);

void TObjBobcontUnbreakable::BrokenSE()
{
	if (lbl_8042C388 != NULL) {
		fn_800B52E8(lbl_8042C388, 0x1048, 0, 0);
	}
}
