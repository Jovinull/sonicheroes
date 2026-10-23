#include "types.h"

// TObjReel::SetPosition (the PS2 build's name, by its place in the PS2 order;
// reelSetPosition here): the out-of-line copy of the body in rel/reel.inc,
// which Exec inlines twice.

#define REEL_SET_POSITION_INLINE
#include "src/rel/reel.inc"
