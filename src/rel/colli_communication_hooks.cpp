#include "types.h"

// The unload and load hooks rel/colli_communication_create.cpp's register puts
// in the editor record for TObjColliCommunication. The volume loads nothing, so
// both are empty.

extern "C" void rinoColObjectUnload(void) { }

extern "C" void rinoColObjectLoad(void) { }
