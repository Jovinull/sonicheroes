#include "types.h"

// TObjEnemySearcher::SetUpAimPositionFirst (the PS2 build's name): the first
// aim is the aim distance straight ahead of the set position (turned by the
// set angle); the distance then flips sign, so the next aim lies behind.

#include "src/rel/searcher.inc"

struct RwMatrixTag {
	u8 data[0x40];
};

extern "C" const RwV3d AxisY;
extern "C" const f32 searcherZero;
extern "C" const f32 searcherOne;
extern "C" const f32 searcherMinusOne;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);

extern "C" void SetUpAimPositionFirst__17TObjEnemySearcherFv(Searcher* searcher)
{
	RwMatrixTag matrix;
	RwV3d aim;

	aim.x = searcherZero;
	aim.y = searcherZero;
	aim.z = searcher->aimDistance;
	fn_80195790(&matrix, &AxisY, searcherOne - fn_800D7AE4(searcher->set->angle + 0x8000),
	    fn_800D7B00(searcher->set->angle + 0x8000), 0);
	fn_80196050(&matrix, &searcher->set->pos, 2);
	fn_8019941C(&aim, &aim, 1, &matrix);
	searcher->aimPos = aim;
	searcher->aimDistance *= searcherMinusOne;
}
