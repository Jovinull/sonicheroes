#include "types.h"

// TObjEnemySearcher::AddScore, GetSearcherBodyAngle and TurnToAimForSearcher
// (the PS2 build's names): the score for breaking a searcher (200 for the
// search light kind, 6, else 100) goes to whoever broke it; the body's angle is
// the searcher's turned half a turn about y and tilted by its lean (degrees);
// turning toward the aim reports whether it got there (an angle difference
// under 0x80 snaps it on; rel/searcher_turn_to_aim.inc).

#include "src/rel/searcher.inc"

extern "C" const f32 searcherDegToAngle;

static inline TEnemyScoreMan* searcherScoreMan()
{
	if (TEnemyScoreMan::EnemyScoreMan == NULL) {
		TEnemyScoreMan::CreateInstance();
	}
	return TEnemyScoreMan::EnemyScoreMan;
}

extern "C" void AddScore__17TObjEnemySearcherFv(Searcher* searcher)
{
	if (searcher->kind == 6) {
		searcherScoreMan()->AddScore(searcher->breaker, 200);
	} else {
		searcherScoreMan()->AddScore(searcher->breaker, 100);
	}
}

extern "C" void GetSearcherBodyAngle__17TObjEnemySearcherFP6sAngle(
    Searcher* searcher, sAngle* angle)
{
	if (angle != NULL) {
		angle->x = searcher->ang.x;
		angle->y = searcher->ang.y;
		angle->z = searcher->ang.z;
		angle->y += 0x8000;
		angle->x += (s32)(searcherDegToAngle * searcher->leanX);
		angle->z += (s32)(searcherDegToAngle * searcher->leanZ);
	}
}

#define SEARCHER_TURN_TO_AIM_INLINE
#include "src/rel/searcher_turn_to_aim.inc"
