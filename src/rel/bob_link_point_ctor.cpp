#include "types.h"

// The constructor of the special stages' second sled link class (BobLinkPoint
// here; the classes have no PS2 names), in stage01D and stage07D. The base
// constructor (rel/bob_link_base.cpp has it as bobLinkCtor) is inlined: it
// lets go of the current link and becomes the current one, unlinked. Then the
// point, direction, timer and slots come from the caller's parameters, and the
// object attaches at once (as bobLinkAttachPoint does).

#define BOB_LINK_POINT_CTOR
#include "src/rel/bob_link_classes.inc"
