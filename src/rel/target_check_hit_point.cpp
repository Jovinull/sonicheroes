#include "types.h"

// TObjTarget::CheckHitPoint (the PS2 build's name, by its place in the PS2
// order; targetCheckHitPoint here): the out-of-line copy of the body in
// rel/target.inc, which CheckFireDunk and CheckThunderShoot inline.

#define TARGET_CHECK_HIT_POINT_INLINE
#include "src/rel/target.inc"
