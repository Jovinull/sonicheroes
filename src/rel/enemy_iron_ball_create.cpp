// TObjEnemyIronBall::Create, the static factory the PS2 build names
// Create__17TObjEnemyIronBallFP14sEnemyIronBall, in stage05D and stage07D: the
// iron balls an enemy throws, created from a filled-in sEnemyIronBall.
//
// The allocation is a real new-expression of the C++ class with its
// constructor inlined; rel/sample1_create.cpp has the long form. The class is
// TObject and the collision block, with no placement, under the task at
// lbl_8042C10C.
//
// The ball keeps its own copy of the description at 0xB0. That member has a
// default constructor of its own, which is why its fields are cleared (and the
// time set to 300) between the vtable store and the class name, before the
// constructor copies the caller's description over them. The collision then
// takes the module's shape centred on the ball and drops bit 0x40 of its
// flags. The zero is the module's constant, read as an external.

#define ENEMY_IRON_BALL_CTOR inline
#include "src/rel/enemy_iron_ball_class.inc"

void TObjEnemyIronBall::Create(sEnemyIronBall* param)
{
	new TObjEnemyIronBall(lbl_8042C10C, param);
}
