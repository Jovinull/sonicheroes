#include "types.h"

// The base class's five do nothing display hooks. Every object in the module
// that does not override one of these points at the copy here: both sample
// objects, the spring and the switch all share the last four.
//
// The claim is .text 0x550 to 0x564. There is nothing else to it: five empty
// functions, one word each.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out.
//
// The adjustor thunk at 0x548 just before is deliberately not included: it tail
// calls into the sample's parameter guard, and a tail call is not something the
// compiler emits from C.

extern "C" void objDefaultTDisp(void) { }

extern "C" void objDefaultPDisp(void) { }

extern "C" void objDefaultImmAftSetRaster(void) { }

extern "C" void objDefaultDebug(void) { }

extern "C" void objDefaultRender(void) { }
