#include "types.h"

// TObjEnemyPawn::SearchPlayerForPawn (the PS2 build's name), the same in the
// eleven stage modules that carry the pawn: the pawn looks for a player
// (fn_800A6334) and, when asked to show it and one was just found, turns its
// alert off if the alert is showing, or otherwise switches its icon to the
// found mark and shows it. The 0.0 is the unit's own literal, which the
// module's other pawn code reads as pawnZero (tools/fix_stage11_symbols.py
// names it and makes it global).

enum eEnemyIcon { ENEMY_ICON_0, ENEMY_ICON_1 };

class TEnemyIconMan
{
public:
	s32 IsOn();
	void Off();
	void Change(eEnemyIcon icon);
	void On(f32 a, f32 b);
};

typedef struct Pawn {
	u8 unk000[0x2D8];
	TEnemyIconMan* alert; // 0x2D8
	TEnemyIconMan* icon;  // 0x2DC
} Pawn;

extern "C" s32 fn_800A6334(Pawn* pawn);

extern "C" s32 SearchPlayerForPawn__13TObjEnemyPawnFi(Pawn* pawn, s32 showIcon)
{
	s32 found = fn_800A6334(pawn);

	if (showIcon != 0 && found == 1 && pawn->icon != NULL) {
		if (pawn->alert != NULL && pawn->alert->IsOn()) {
			pawn->icon->Off();
		} else {
			pawn->icon->Change(ENEMY_ICON_1);
			pawn->icon->On(0.0f, 0.0f);
		}
	}
	return found;
}
