#include "types.h"

// Makes the special stages' second sled link object (BobLinkPoint here; the
// classes have no PS2 names), in stage01D and stage07D: a new object, its
// constructor (rel/bob_link_classes.inc) inlined.

#include "src/rel/bob_link_classes.inc"

extern "C" void bobLinkPointCreate(BobLinkPointParams* params)
{
	new BobLinkPoint(params);
}
