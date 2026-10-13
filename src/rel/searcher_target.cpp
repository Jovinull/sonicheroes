#include "types.h"

// TObjEnemySearcher::GetMachineGunAttackAngle, GetTargetAngle and GetTargetVec
// (the PS2 build's names): the machine gun's attack angle; the vector from the
// searcher to its target player (15 above the player's position; straight
// ahead without a target) and the angle between that direction and the
// searcher's facing. Built with deferred inlining like the rest of the
// searcher's file (GetTargetAngle inlines GetTargetVec, defined after it), so
// the functions are defined last to first.

#include "src/rel/searcher.inc"

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct PlayerState {
	u8 unk00[0x18];
	RwV3d pos; // 0x18
} PlayerState;

extern "C" PlayerState* lbl_802AD090[];
extern "C" const RwV3d AxisY;
extern "C" const RwV3d searcherDefaultTargetVec;
extern "C" const f32 searcherTargetLift;
extern "C" const f32 searcherOne;
extern "C" const RwV3d searcherBack;
extern "C" const sAngle searcherZeroAngle;

extern "C" int fn_800A5844(Searcher* searcher);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);
extern "C" void fn_801990E0(RwV3d* out, RwV3d* in);
int VectorAngle(RwV3d* a, RwV3d* b, RwV3d* up);

extern "C" RwV3d GetTargetVec__17TObjEnemySearcherFv(Searcher* searcher)
{
	int player = fn_800A5844(searcher);
	RwV3d vec  = searcherDefaultTargetVec;

	if (player != -1 && lbl_802AD090[player] != NULL) {
		RwV3d pos = lbl_802AD090[player]->pos;

		pos.y += searcherTargetLift;
		vec.x = pos.x - searcher->pos.x;
		vec.y = pos.y - searcher->pos.y;
		vec.z = pos.z - searcher->pos.z;
	}
	return vec;
}

extern "C" sAngle GetTargetAngle__17TObjEnemySearcherFv(Searcher* searcher)
{
	RwV3d dir = GetTargetVec__17TObjEnemySearcherFv(searcher);

	fn_801990E0(&dir, &dir);
	RwMatrixTag matrix;

	fn_80195790(&matrix, &AxisY, searcherOne - fn_800D7AE4(searcher->ang.y + 0x8000),
	    fn_800D7B00(searcher->ang.y + 0x8000), 0);
	RwV3d facing = searcherBack;
	RwV3d out;

	fn_8019941C(&out, &facing, 1, &matrix);
	sAngle angle = searcherZeroAngle;

	angle.x = VectorAngle(&dir, &out, NULL);
	return angle;
}

extern "C" s32 GetMachineGunAttackAngle__17TObjEnemySearcherFv(Searcher* searcher)
{
	return searcher->mgunAttackAngle;
}
