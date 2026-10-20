#include "types.h"

// The breakable weight's CheckPlayerTrespassArea (the PS2 build's
// TObjWeightExt name; breakableWeightCheckPlayerTrespassArea here; the
// weight's own is rel/weight_area_check.cpp), with the active-state filter as
// an argument. Nothing calls this copy; the weight's checks inline it (the
// inline of breakable_weight.inc, the same body). Written out here: calling
// the inline from this function gives other registers.

#include "src/rel/breakable_weight.inc"

extern "C" s32 breakableWeightCheckPlayerTrespassArea(BreakableWeight* object, s32 active)
{
	RwV3d pos;

	SetWeightMatrix(object);
	for (int i = 0; i < 8; i++) {
		if (fn_8003E2E4(i, 0, &pos, 0) == 0) {
			continue;
		}
		if (active) {
			if (lbl_802AD090[i] == NULL) {
				continue;
			}
			if ((lbl_802AD090[i]->flags & 1) == 0) {
				continue;
			}
		}
		if (fn_800AB32C(lbl_802AD070[i]) != 0) {
			continue;
		}
		fn_8019941C(&pos, &pos, 1, object->matrix);
		if (pos.y > breakableWeightTopMargin[0] + (object->pos.y - object->base)) {
			continue;
		}
		if ((f32)__fabs(pos.x) > breakableWeightHalfWidth[0] * object->scale.x) {
			continue;
		}
		if ((f32)__fabs(pos.z) > breakableWeightHalfDepth[0] * object->scale.z) {
			continue;
		}
		return 1;
	}
	return 0;
}
