// Records a battle result: results 0 and 1 mark that team as the winner of the round (+0x98, the
// other team cleared), set the state byte +0x30 to 3 and call fn_800194E0; results 100 and above
// mark team (result - 100) as the winner, report it (fn_80019898) and add a victory to that team
// (PARAM_VICTORY at +0x30). Other results do nothing. HYPOTHESIS: 2P battle bookkeeping on the
// state lbl_8042C314; the roles are UNKNOWN.
#include "game/gparam.h"

struct Battle800A096C {
	u8 pad0[0x30];
	u8 victory[1]; // 0x30 (PARAM_VICTORY base; its first byte is also the state)
	u8 pad31[0x98 - 0x31];
	s32 winner[2]; // 0x98
};

extern "C" {
extern Battle800A096C* lbl_8042C314;
extern u8 lbl_8029C310[];
void fn_800194E0(void* state);
void fn_80019898(void* state, s32 team);
}

static inline void SetWinner(Battle800A096C* battle, s32 team)
{
	battle->winner[team]              = 1;
	battle->winner[team != 0 ? 0 : 1] = 0;
}

extern "C" void fn_800A096C(s32 result)
{
	Battle800A096C* battle = lbl_8042C314;

	if (result < 100) {
		if (result == 0 || result == 1) {
			battle->victory[0] = 3;
			fn_800194E0(lbl_8029C310);
			SetWinner(battle, result);
		}
	} else {
		SetWinner(battle, result -= 100);
		fn_80019898(lbl_8029C310, result);
		((PARAM_VICTORY*)battle->victory)->addVictory(result, 1);
	}
}
