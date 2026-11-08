#include "types.h"

// TObjEnemySearcher::SearchPlayerForSearcher (the PS2 build's name): asks
// whether the searcher sees a player (fn_800A6334); when it does exactly, and
// the searcher has its icon, the icon goes off if the gauge is on, else it
// changes to the first kind and is shown at zero.

enum eEnemyIcon { E_ICON_NONE, E_ICON_FIRST };

class TEnemyIconMan
{
public:
	void Off();
	s32 IsOn();
	void Change(eEnemyIcon icon);
	void On(f32 value, f32 time);
};

typedef struct SearcherIcons {
	u8 unk000[0x2B0];
	TEnemyIconMan* gauge; // 0x2B0
	TEnemyIconMan* icon;  // 0x2B4
} SearcherIcons;

extern "C" s32 fn_800A6334(SearcherIcons* searcher);

extern "C" s32 SearchPlayerForSearcher__17TObjEnemySearcherFv(SearcherIcons* searcher)
{
	s32 found = fn_800A6334(searcher);

	if (found == 1 && searcher->icon != NULL) {
		if (searcher->gauge != NULL && searcher->gauge->IsOn()) {
			searcher->icon->Off();
		} else {
			searcher->icon->Change(E_ICON_FIRST);
			searcher->icon->On(0.0f, 0.0f);
		}
	}
	return found;
}
