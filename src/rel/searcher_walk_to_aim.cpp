#include "types.h"

// TObjEnemySearcher::WalkToAim (the PS2 build's name): walks toward the aim
// at the walking speed, stopping within 5 of it or against a wall; on the
// ground a fall slower than 1.5 times gravity stops; returns 0 once it stopped
// (or when TObjEnemy's move step says so), 1 while walking or when it does not
// move at all.

#include "src/rel/searcher.inc"

extern "C" const f32 searcherZero;
extern "C" const f32 searcherMinusOne;
extern "C" const f32 searcherAimReach;
extern "C" const f32 searcherFallLimit;

extern "C" f32 fn_800A5AC0(Searcher* searcher);
extern "C" void fn_800A4668(Searcher* searcher);
extern "C" void fn_800A4A8C(Searcher* searcher, f32 speed);
extern "C" void fn_800A5C6C(Searcher* searcher, s32 flags);
extern "C" int fn_800A5888(Searcher* searcher, f32 limit);
extern "C" void fn_800A5B50(Searcher* searcher, s32 flags);

extern "C" int WalkToAim__17TObjEnemySearcherFv(Searcher* searcher)
{
	int walking = 1;

	if (searcher->turning == 0) {
		return 1;
	}
	if (fn_800A5AC0(searcher) < searcherAimReach || (searcher->colliFlags & 4)) {
		fn_800A4668(searcher);
		walking = 0;
	} else {
		fn_800A4A8C(searcher, searcher->walkSpeed);
	}
	fn_800A5C6C(searcher, 0xF00);
	if ((searcher->colliFlags & 2) && searcher->speedY < searcherFallLimit * searcher->gravity) {
		searcher->speedY = searcherZero;
	}
	if (fn_800A5888(searcher, searcherMinusOne)) {
		fn_800A5B50(searcher, 0xF00);
		walking = 0;
	}
	return walking;
}
