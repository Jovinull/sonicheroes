#include "types.h"

// TObjGoalring::CheckDispBackRing (the PS2 build's name): whether the stage
// shows the two-part ring (see rel/goal_ring_class.inc).

#include "src/rel/goal_ring_class.inc"

u8 TObjGoalring::CheckDispBackRing()
{
	return goalRingTwoRings();
}
