#include "types.h"

// TObjReel::SetParameter (the PS2 build's name, by its place in the PS2
// order; reelSetParameter here): the out-of-line copy of the body in
// rel/reel.inc, which Exec inlines.

#define REEL_SET_PARAMETER_INLINE
#include "src/rel/reel.inc"
