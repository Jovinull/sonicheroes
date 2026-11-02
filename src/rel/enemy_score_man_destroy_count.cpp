// The two destroyed enemy counters of the bonus stages' own copy of the score
// manager (31D-33D; main's game/enemy/e_scoreman.cpp has them as fn_8011C0E8
// and fn_8011C13C): each counts one more and, at the goal (flag 4 or 8),
// saves the time; the first also keeps the total.
#include "game/enemy/e_scoreman.h"

struct ScoreModeView {
	u8 unknown[0x22];
	s8 flag22, flag23, flag24;
};

extern "C" {
extern ScoreModeView* lbl_8042C180;
void saveTime__18PARAM_SAVEPOSITIONFv(void*);
}

extern "C" void scoreManCountDestroy(TEnemyScoreMan* self)
{
	++self->mDestroyEnemyTotal;
	if (lbl_8042C180->flag24 == 4 || lbl_8042C180->flag24 == 8) {
		self->mSaveDestroyEnemyTotal = self->mDestroyEnemyTotal;
		saveTime__18PARAM_SAVEPOSITIONFv(&static_cast<ScoreSavedStateBase&>(*self));
	}
}
extern "C" void scoreManCountExtra(TEnemyScoreMan* self)
{
	++self->counter58;
	if (lbl_8042C180->flag24 == 4 || lbl_8042C180->flag24 == 8)
		saveTime__18PARAM_SAVEPOSITIONFv(&static_cast<ScoreSavedStateBase&>(*self));
}
