#include "types.h"

// TObjEnemySearcher::EnemyMD_Ready (the PS2 build's name): on starting, checks
// which way to aim (CheckDirectionOfPlayerRangeIn, inline); while ready, aims
// at the nearest leader in range, turns toward the aim (TurnToAimForSearcher,
// inline) and bobs. Built without fused multiply-add, as the retail is.

#include "src/rel/searcher.inc"

#include "src/rel/searcher_check_direction.inc"
#include "src/rel/searcher_turn_to_aim.inc"

extern "C" const f32 searcherBobHeight;

// bobs up and down around the home height
static inline void searcherBob(Searcher* searcher)
{
	if (searcher->turning) {
		searcher->bobAngle += 0x100;
		searcher->pos.y = searcher->home.y + searcherBobHeight * fn_800D7B00(searcher->bobAngle);
	}
}

extern "C" void EnemyMD_Ready__17TObjEnemySearcherFQ29TObjEnemy10eCtrlSMode(
    Searcher* searcher, s32 sub)
{
	switch (sub) {
		case 0:
			CheckDirectionOfPlayerRangeIn__17TObjEnemySearcherFv(searcher);
			break;
		case 1: {
			int player = nSearchPlayer::GetNearestLeaderNum(&searcher->pos, searcherSearchRange);

			if (player != -1 && lbl_802AD090[player] != NULL) {
				searcher->aimPos = lbl_802AD090[player]->pos;
			}
			TurnToAimForSearcher__17TObjEnemySearcherFv(searcher);
			searcherBob(searcher);
			break;
		}
		case 2:
		case 3:
			break;
	}
}
