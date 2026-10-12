#include "types.h"

// The reset hooks rel/stoprain_register.cpp puts in the stoprain's editor
// record. The empty hooks have nothing to do: the object loads nothing.

extern "C" void stoprainReset(void) { }
