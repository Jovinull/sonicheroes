#include "types.h"

// Makes the special stages' first sled link object (BobLinkAttach here; the
// classes have no PS2 names), in stage01D and stage07D: a new object whose
// constructor, inlined with the base one, takes the timer, point, direction,
// flags and slots from the caller's parameters and attaches at once (as
// bobLinkAttach does).

#include "src/rel/bob_link_classes.inc"

extern "C" void bobLinkAttachCreate(BobLinkAttachParams* params)
{
	new BobLinkAttach(params);
}
