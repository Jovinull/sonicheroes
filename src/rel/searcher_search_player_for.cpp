#include "types.h"

// TObjEnemySearcher::SearchPlayerFirst and SearchPlayerForSearcher (the PS2
// build's names). ForSearcher asks whether the searcher sees a player
// (fn_800A6334) and drives the searcher's icon from the answer: when it is
// exactly 1 and the searcher has its icon, the icon goes off if the gauge is on,
// else it changes to the first kind and is shown at zero. First does the same
// with the ground object's state in place of the question while the searcher is
// in mode 6 (the ground object being there), and asks the question otherwise.
// Both come out in the order they are defined here.

enum eEnemyIcon { E_ICON_NONE, E_ICON_FIRST };

class TEnemyIconMan
{
public:
	void Off();
	s32 IsOn();
	void Change(eEnemyIcon icon);
	void On(f32 value, f32 time);
};

typedef struct SearcherGround {
	u8 unk000[0xF0];
	s32 state; // 0xF0
} SearcherGround;

typedef struct SearcherIcons {
	u8 unk000[0x2B0];
	TEnemyIconMan* gauge; // 0x2B0
	TEnemyIconMan* icon;  // 0x2B4
	u8 unk2B8[0x38];
	SearcherGround* ground; // 0x2F0
	u8 unk2F4[0x28];
	s32 mode; // 0x31C
} SearcherIcons;

extern "C" s32 fn_800A6334(SearcherIcons* searcher);

static inline void searcherShowIcon(SearcherIcons* searcher, s32 found)
{
	if (found == 1 && searcher->icon != NULL) {
		if (searcher->gauge != NULL && searcher->gauge->IsOn()) {
			searcher->icon->Off();
		} else {
			searcher->icon->Change(E_ICON_FIRST);
			searcher->icon->On(0.0f, 0.0f);
		}
	}
}

extern "C" s32 SearchPlayerForSearcher__17TObjEnemySearcherFv(SearcherIcons* searcher)
{
	s32 found = fn_800A6334(searcher);

	searcherShowIcon(searcher, found);
	return found;
}

extern "C" s32 SearchPlayerFirst__17TObjEnemySearcherFv(SearcherIcons* searcher)
{
	if (searcher->mode != 6) {
		s32 found = fn_800A6334(searcher);

		searcherShowIcon(searcher, found);
		return found;
	}
	if (searcher->ground != NULL) {
		s32 state = searcher->ground->state;

		searcherShowIcon(searcher, state);
		return state;
	}
	return 0;
}
