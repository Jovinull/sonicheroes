#include "types.h"

// TObjWeight's WeightPlayer (the PS2 build's name; weightPlayer here): with
// the weight's matrix built, every player the weight's collision touched
// (unless its state has bit 0x4000 set) that is under the weight (its position
// seen in the weight's frame no higher than the weight's height above its
// base, within its scaled half width and half depth) and within 3 of the base
// height is put on the base, its X and Z angles cleared.

#include "src/rel/weight.inc"

typedef struct WeightHitter {
	u8 unk00[0x78]; // 0x00
	u32 type;       // 0x78
} WeightHitter;

typedef struct WeightHit {
	u8 unk00[0x4];        // 0x00
	WeightHitter* hitter; // 0x04
} WeightHit;

typedef struct WeightRider {
	u8 unk00[0x10]; // 0x00
	s16 state;      // 0x10
} WeightRider;

extern "C" u8 lbl_8042C1A4[];
extern "C" WeightRider* lbl_802AD0D0[];
// 3.0, also the weight's blink scale
extern "C" const f32 weightBlinkScale[1];

extern "C" void fn_80021824(void* colli);
extern "C" WeightHit* fn_800211A8(void* colli);
extern "C" s32 fn_80041B64(u32 type);
extern "C" void objSetPlayerPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
    void* replace, s32 player, u8 flags, RwV3d* position, sAngle* angle);

static inline WeightHitter* weightHitter(WeightHit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

extern "C" void weightPlayer(Weight* object)
{
	WeightHitter* hitter;

	SetWeightMatrix(object);
	fn_80021824(lbl_8042C1A4);
	while ((hitter = weightHitter(fn_800211A8(object->colli))) != NULL) {
		s32 player = fn_80041B64(hitter->type);
		RwV3d pos;
		sAngle angle;
		RwV3d local;

		if (lbl_802AD0D0[player]->state & 0x4000) {
			continue;
		}
		fn_8003E2E4(player, 0, &pos, &angle);
		fn_8019941C(&local, &pos, 1, object->matrix);
		if (local.y > object->pos.y - object->base) {
			continue;
		}
		if ((f32)__fabs(local.x) > weightHalfWidth[0] * object->scale.x) {
			continue;
		}
		if ((f32)__fabs(local.z) > weightHalfDepth[0] * object->scale.z) {
			continue;
		}
		if ((f32)__fabs(pos.y - object->base) > weightBlinkScale[0]) {
			continue;
		}
		pos.y   = object->base;
		angle.z = 0;
		angle.x = 0;
		objSetPlayerPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
		    &object->replace, player, 0, &pos, &angle);
	}
}
