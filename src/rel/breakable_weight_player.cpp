#include "types.h"

// The breakable weight's WeightPlayer (the PS2 build's TObjWeightExt name;
// breakableWeightPlayer here; the weight's own is rel/weight_player.cpp): the
// same, putting every player the weight's collision touched that is under the
// weight and near its base on the base; then, while nobody rides the weight,
// a player whose team has more than one member becomes its rider for 900
// frames, from where it stands.

#include "src/rel/breakable_weight.inc"

typedef struct WeightHitter {
	u8 unk00[0x78]; // 0x00
	u32 type;       // 0x78
} WeightHitter;

typedef struct WeightHit {
	u8 unk00[0x4];        // 0x00
	WeightHitter* hitter; // 0x04
} WeightHit;

typedef struct WeightRider {
	u8 unk00[0x10];  // 0x00
	s16 state;       // 0x10
	u8 unk12[0x13C]; // 0x12
	s16 motion;      // 0x14E
} WeightRider;

typedef struct WeightPlayerTask {
	u8 unk00[0x9BC]; // 0x00
	s8 team;         // 0x9BC
} WeightPlayerTask;

typedef struct WeightTeam {
	u8 unk00[0x120]; // 0x00
	s8 unk120;       // 0x120
} WeightTeam;

extern "C" u8 lbl_8042C1A4[];
extern "C" WeightRider* lbl_802AD0D0[];
extern "C" WeightTeam* lbl_80303DC8[];
// 3.0
extern "C" const f32 breakableWeightNear[1];

extern "C" void fn_80021824(void* colli);
extern "C" WeightHit* fn_800211A8(void* colli);
extern "C" s32 fn_80041B64(u32 type);
extern "C" void fn_80043F28(WeightPlayerTask* task);
extern "C" void objSetPlayerPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
    void* replace, s32 player, u8 flags, RwV3d* position, sAngle* angle);

static inline WeightHitter* weightHitter(WeightHit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

extern "C" void breakableWeightPlayer(BreakableWeight* object)
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
		if ((f32)__fabs(local.x) > breakableWeightHalfWidth[0] * object->scale.x) {
			continue;
		}
		if ((f32)__fabs(local.z) > breakableWeightHalfDepth[0] * object->scale.z) {
			continue;
		}
		if ((f32)__fabs(pos.y - object->base) > breakableWeightNear[0]) {
			continue;
		}
		pos.y   = object->base;
		angle.z = 0;
		angle.x = 0;
		objSetPlayerPosition__17OBJ_ReplacePlayerFiUcP5RwV3dP6sAngle(
		    &object->replace, player, 0, &pos, &angle);
		if (object->rider == -1) {
			WeightPlayerTask* task = (WeightPlayerTask*)lbl_802AD070[player];

			if (lbl_80303DC8[task->team]->unk120 > 1) {
				fn_80043F28(task);
				object->rider      = player;
				object->riderTimer = 900;
				WeightRider* rider = lbl_802AD0D0[player];
				object->riderPos   = pos;
				rider->motion      = 0x51;
			}
		}
	}
}
