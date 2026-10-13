// TObjEnemySearcher::TurnToAimForSearcher (the PS2 build's name): turns
// toward the aim and reports whether it got there (an angle difference under
// 0x80 snaps it on). EnemyMD_Ready inlines it; rel/searcher_score.cpp has the
// out-of-line copy (SEARCHER_TURN_TO_AIM_INLINE empty).

s32 AdjustAngle(s32 angle, s32 aim, s32 speed);
extern "C" s32 fn_800A5A54(Searcher* searcher);

#ifndef SEARCHER_TURN_TO_AIM_INLINE
#define SEARCHER_TURN_TO_AIM_INLINE inline
#endif

extern "C" SEARCHER_TURN_TO_AIM_INLINE int TurnToAimForSearcher__17TObjEnemySearcherFv(
    Searcher* searcher)
{
	s32 diff;

	if (searcher->turning == 0) {
		return 0;
	}
	diff            = fn_800A5A54(searcher);
	searcher->ang.y = AdjustAngle(searcher->ang.y, searcher->aimAngY, searcher->turnSpeed);
	if (diff < 0x80) {
		searcher->ang.y = searcher->aimAngY;
		return 1;
	}
	return 0;
}
