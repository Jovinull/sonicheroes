#include "game/obj_colli_communication.h"

// rinoColObjectCreate, the factory the editor record for
// TObjColliCommunication points at; the class is in
// game/obj_colli_communication.h.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.

extern "C" void rinoColObjectCreate(void)
{
	new TObjColliCommunication(lbl_8042C10C);
}
