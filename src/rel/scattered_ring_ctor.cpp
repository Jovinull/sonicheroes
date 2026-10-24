#include "types.h"

// TObjScatteredRing's constructor (the PS2 build's name): the out-of-line
// copy of the body in rel/scattered_ring.inc. TObjRing's constructor
// (rel/ring_cdtor.cpp) inlined: the rings a hurt player drops, from 1 to 20 of
// them, flying from the position along the angle (or none), with their speed
// and spread; each ring joins the group (Init), and the drop sounds when asked
// to.

#define SCATTERED_RING_CTOR_INLINE
#include "src/rel/scattered_ring.inc"
