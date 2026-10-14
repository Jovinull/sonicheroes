#include "types.h"

// TObjEnemySearcher::CheckHitPoint (the PS2 build's name): when the hit points
// changed, shows the hit point gauge for three seconds (with 100 more while
// the searcher sounds its siren, enemy mode 0x24) and hides the other icon;
// both icons follow the searcher. Returns whether the hit points changed.

#include "src/rel/searcher.inc"

extern "C" const f32 searcherIconShowTime;

extern "C" int CheckHitPoint__17TObjEnemySearcherFv(Searcher* searcher)
{
	int changed  = 0;
	f32 hitPoint = searcher->hitPoint;

	if (hitPoint != searcher->shownHitPoint) {
		searcher->shownHitPoint = hitPoint;
		if (searcher->gauge != NULL) {
			if (searcher->mode == 0x24) {
				searcher->gauge->On(hitPoint, searcherIconShowTime, 100);
			} else {
				searcher->gauge->On(hitPoint, searcherIconShowTime);
			}
		}
		if (searcher->icon != NULL) {
			searcher->icon->Off();
		}
		changed = 1;
	}
	if (searcher->gauge != NULL) {
		searcher->gauge->SetPos(&searcher->pos, NULL);
	}
	if (searcher->icon != NULL) {
		searcher->icon->SetPos(&searcher->pos, NULL);
	}
	return changed;
}
