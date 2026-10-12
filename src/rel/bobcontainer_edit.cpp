// TObjBobcontainer's EditOnChange: the kind in the placement's parameters is
// held to 0 or 1 and names the editor's first field. The class is in
// game/obj_container.h.

#include "game/obj_container.h"

extern "C" const char* unbrBobcontObjectFieldNames[];
extern "C" const char* bobcontainerKindNames[2];

void TObjBobcontainer::EditOnChange(SETDATA_PARAM* data)
{
	s16* kind = (s16*)data->setBuffer;

	if (*kind < 0) {
		*kind = 0;
	}
	if (*kind > 1) {
		*kind = 1;
	}
	unbrBobcontObjectFieldNames[0] = bobcontainerKindNames[*kind];
}
