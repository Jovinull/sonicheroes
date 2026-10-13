#include "types.h"

#include "src/rel/hint_ball_class.inc"

// HintBall's constructor (the PS2 build's HintBall::__ct with the same
// arguments). It builds the particle base with the flags and sprite, clears the
// two counters at 0xC and 0xE and makes the ring's twelve balls (CreateBalls,
// inlined).

HintBall::HintBall(RwV3d* pos, sRealAngle3* angle, int start, float speed, float life,
    Pt_FLAGS flags, SPRITE_INFO* sprite)
    : PARTICLE_MATERIAL(flags, sprite)
{
	unkC = 0;
	unkE = 0;
	CreateBalls(pos, angle, start, speed, life);
}
