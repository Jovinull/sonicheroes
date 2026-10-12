// TObjBobcontainer::CheckGround: the bobsleigh crate takes the height of the
// ground below it from its shadow and answers 1 when it is closer to it than
// its falling distance (the field at 0xDC), 0 otherwise or when there is no
// ground. It is rel/container_check_ground.cpp without the third answer. Exec
// inlines it; this copy has no caller and is kept with force_active. The class
// is in game/obj_container.h.

#include "game/obj_container.h"
#include "game/vertical_colli.h"
#include "MSL_C/math.h"

extern "C" const f32 bobcontainerNoGround[1];

s32 TObjBobcontainer::CheckGround()
{
	if (bobcontainerNoGround[0] != (height = GetShadowPos(&pos, NULL, 1))) {
		double fall = __fabs(unkDC);
		double diff = __fabs(height - pos.y);
		if ((f32)diff < (f32)fall) {
			return 1;
		}
	}
	return 0;
}
