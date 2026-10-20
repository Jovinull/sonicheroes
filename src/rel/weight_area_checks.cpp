#include "types.h"
#include "MSL_C/math.h"

// Two of TObjWeight's area checks (weightCheckActivePlayerUnder and weightCheckPlayerUnder here): with the
// weight's matrix built, each answers whether some player stands under the
// weight, its position seen in the weight's frame no higher than the weight's
// height above its base (plus a margin) and within its scaled half width and
// half depth. The first counts only the players whose state has bit 0 set.

#include "src/rel/weight.inc"

typedef struct WeightPlayerState {
	u8 unk00[0x6]; // 0x00
	s16 flags;     // 0x06
} WeightPlayerState;

extern "C" WeightPlayerState* lbl_802AD090[];
extern "C" void* lbl_802AD070[];
extern "C" const f32 weightHalfDepth[1];
extern "C" const f32 weightHalfWidth[1];
extern "C" const f32 weightTopMargin[1];

extern "C" s32 fn_8003E2E4(s32 player, s32 kind, RwV3d* position, s32 arg3);
extern "C" s32 fn_800AB32C(void* task);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);

// the checks are inline (Exec uses them) and these are their own copies: only a
// body inlined into the function gives the retail's registers and stack slots
static inline s32 ActivePlayerUnder(Weight* object)
{
	RwV3d pos;

	SetWeightMatrix(object);
	for (int i = 0; i < 8; i++) {
		if (fn_8003E2E4(i, 0, &pos, 0) == 0) {
			continue;
		}
		if (lbl_802AD090[i] == NULL) {
			continue;
		}
		if ((lbl_802AD090[i]->flags & 1) == 0) {
			continue;
		}
		if (fn_800AB32C(lbl_802AD070[i]) != 0) {
			continue;
		}
		fn_8019941C(&pos, &pos, 1, object->matrix);
		if (pos.y > weightTopMargin[0] + (object->pos.y - object->base)) {
			continue;
		}
		if ((f32)__fabs(pos.x) > weightHalfWidth[0] * object->scale.x) {
			continue;
		}
		if ((f32)__fabs(pos.z) > weightHalfDepth[0] * object->scale.z) {
			continue;
		}
		return 1;
	}
	return 0;
}

extern "C" s32 weightCheckActivePlayerUnder(Weight* object)
{
	return ActivePlayerUnder(object);
}

static inline s32 PlayerUnder(Weight* object)
{
	RwV3d pos;

	SetWeightMatrix(object);
	for (int i = 0; i < 8; i++) {
		if (fn_8003E2E4(i, 0, &pos, 0) == 0) {
			continue;
		}
		if (fn_800AB32C(lbl_802AD070[i]) != 0) {
			continue;
		}
		fn_8019941C(&pos, &pos, 1, object->matrix);
		if (pos.y > weightTopMargin[0] + (object->pos.y - object->base)) {
			continue;
		}
		if ((f32)__fabs(pos.x) > weightHalfWidth[0] * object->scale.x) {
			continue;
		}
		if ((f32)__fabs(pos.z) > weightHalfDepth[0] * object->scale.z) {
			continue;
		}
		return 1;
	}
	return 0;
}

extern "C" s32 weightCheckPlayerUnder(Weight* object)
{
	return PlayerUnder(object);
}
