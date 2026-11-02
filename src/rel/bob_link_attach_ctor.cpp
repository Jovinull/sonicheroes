#include "types.h"

// The constructor of the special stages' first sled link class
// (BobLinkAttach here; the classes have no PS2 names), in stage01D and
// stage07D: rel/bob_link_classes.inc has it, with the base constructor
// inlined.

#define BOB_LINK_ATTACH_CTOR
#include "src/rel/bob_link_classes.inc"
