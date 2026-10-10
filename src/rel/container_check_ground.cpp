// TObjContainer::CheckGround (the PS2 build's name): the crate takes the height
// of the ground below it from its shadow. It answers 2 when there is no ground
// (the shadow's -1000000), 1 when the crate is at least its falling distance
// (the field at 0xDC) above it, and 0 when it is resting on it. Exec inlines
// it; this copy has no caller and is kept with force_active. The compare uses
// the shadow's answer itself, not the field it was stored in, and the two
// distances stay doubles until the comparison rounds them, which is the
// original's order. The class is in game/obj_container.h.

#include "game/obj_container.h"
#include "game/vertical_colli.h"
#include "MSL_C/math.h"

extern "C" const f32 containerNoGround[1];

s32 TObjContainer::CheckGround()
{
	if (containerNoGround[0] != (height = GetShadowPos(&pos, NULL, 1))) {
		double fall = __fabs(unkDC);
		double diff = __fabs(height - pos.y);
		if ((f32)diff < (f32)fall) {
			return 0;
		}
		return 1;
	}
	return 2;
}
