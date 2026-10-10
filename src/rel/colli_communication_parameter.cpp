// TObjColliCommunication's SetColliParameter, SetParameter and ResetVariable,
// out of line: the copies each module keeps although the constructor inlines
// them (no caller; force_active). They are in game/obj_colli_communication.h.

#define COLLI_COMM_INLINE
#include "game/obj_colli_communication.h"
