// TObjEnemy::InitMode (symbol name from the retail map): enters a mode by running its control routine in the init phase.
#include "game/enemy/e_obj_enemy.h"

void TObjEnemy::InitMode(ENEMY_MD mode)
{
	CtrlMode(mode, CTRL_SMODE_INIT);
}
