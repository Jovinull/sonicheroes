#include "game/obj_colli_communication.h"

// TObjColliCommunication::CreateInstance, the static factory the PS2 build
// names CreateInstance__22TObjColliCommunicationFv: the same new-expression as
// rel/colli_communication_create.cpp, returning the object. Nothing in the
// module calls it, so it is listed in each module's force_active.

TObjColliCommunication* TObjColliCommunication::CreateInstance()
{
	return new TObjColliCommunication(lbl_8042C10C);
}
