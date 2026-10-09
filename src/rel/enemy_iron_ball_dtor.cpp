// TObjEnemyIronBall's destructor, out of line. Its body is empty: the vtable
// resets and the base destructors are the compiler's. The class is shared
// through enemy_iron_ball_class.inc, where the destructor is declared after the
// class's first other virtual so this unit does not emit the vtable.

#define ENEMY_IRON_BALL_CTOR inline
#include "src/rel/enemy_iron_ball_class.inc"

TObjEnemyIronBall::~TObjEnemyIronBall() { }
