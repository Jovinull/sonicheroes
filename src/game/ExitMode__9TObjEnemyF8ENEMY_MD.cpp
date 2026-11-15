// TObjEnemy::ExitMode (symbol name from the retail map): leaves a mode by running its control routine in the exit phase.
#include "game/enemy/e_obj_enemy.h"

void TObjEnemy::ExitMode(ENEMY_MD mode)
{
	CtrlMode(mode, CTRL_SMODE_EXIT);
}
