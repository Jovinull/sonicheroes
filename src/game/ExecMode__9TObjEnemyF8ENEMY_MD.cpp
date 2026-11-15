// TObjEnemy::ExecMode (symbol name from the retail map): runs the control routine of a mode in the
// exec phase.
#include "game/enemy/e_obj_enemy.h"

void TObjEnemy::ExecMode(ENEMY_MD mode)
{
	CtrlMode(mode, CTRL_SMODE_EXEC);
}
