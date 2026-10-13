#include "types.h"

// HintBall::CreateBalls, the PS2 build's name and signature. It makes the hint
// ring's twelve balls round the ring: each new ball (from the emitter's own
// virtual) gets its angle round the ring from the given start, its point (the
// ball offset turned about Y by the ring's yaw and about Z by its angle, at the
// ring's position), the ring's position, the given speed and its spread, a
// spin from the yaw, and the given life. It stops at the first ball it cannot
// get.

#define HINT_BALL_CREATE_INLINE
#include "src/rel/hint_ball_class.inc"
