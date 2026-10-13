#include "types.h"

// TObjEnemySearcher::CheckDirectionOfPlayerRangeIn (the PS2 build's name):
// aims up (0xD000) when the nearest leader in range lies within a quarter turn
// of the searcher's facing (its back axis turned by its heading against the
// leader's normalized position), down (0x3000) otherwise or with nobody in
// range. The same test as TObjEnemyPawn's (rel/pawn_check_direction.inc).

#include "src/rel/searcher.inc"

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct PlayerState {
	u8 unk00[0x18];
	RwV3d pos; // 0x18
} PlayerState;

namespace nSearchPlayer
{
s32 GetNearestLeaderNum(const RwV3d* pos, f32 range);
}

extern "C" PlayerState* lbl_802AD090[];
extern "C" const RwV3d AxisY;
extern "C" const f32 searcherSearchRange;
extern "C" const RwV3d searcherFacing;
extern "C" const f32 searcherOne;
extern "C" const RwV3d searcherNoTarget;
extern "C" const RwV3d searcherAngleUp;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);
extern "C" void fn_801990E0(RwV3d* out, RwV3d* in);
int VectorAngle(RwV3d* a, RwV3d* b, RwV3d* up);

extern "C" void CheckDirectionOfPlayerRangeIn__17TObjEnemySearcherFv(Searcher* searcher)
{
	int player = nSearchPlayer::GetNearestLeaderNum(&searcher->pos, searcherSearchRange);
	int angle;

	if (player == -1) {
		searcher->aimPitch = 0x3000;
		return;
	}
	RwMatrixTag matrix;
	RwV3d facing = searcherFacing;

	fn_80195790(&matrix, &AxisY, searcherOne - fn_800D7AE4(searcher->ang.y + 0x8000),
	    fn_800D7B00(searcher->ang.y + 0x8000), 0);
	fn_8019941C(&facing, &facing, 1, &matrix);
	RwV3d target = searcherNoTarget;

	if (lbl_802AD090[player] != NULL) {
		target = lbl_802AD090[player]->pos;
	}
	fn_801990E0(&target, &target);
	RwV3d up = searcherAngleUp;

	angle = VectorAngle(&facing, &target, &up);
	if (angle >= 0 && angle <= 0x4000) {
		searcher->aimPitch = 0x10000 - 0x3000;
	} else {
		searcher->aimPitch = 0x3000;
	}
}
