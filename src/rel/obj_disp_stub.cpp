#include "types.h"

// The base class's empty Disp, the copy the cannon's translation unit keeps
// between its factory and its editor record (rel/obj_base_stubs.cpp has the
// other five do nothing display hooks). The objects that do not draw
// themselves point at it.

extern "C" void Disp__7TObjectFv(void) { }
