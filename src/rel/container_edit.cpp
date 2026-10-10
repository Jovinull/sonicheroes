// TObjContainer's EditOnChange: the kind in the placement's parameters is held
// to 0 or 1 and names the editor's first field. The class is in
// game/obj_container.h.

#include "game/obj_container.h"

extern "C" const char* containerFieldNames[];
extern "C" const char* containerKindNames[2];

void TObjContainer::EditOnChange(SETDATA_PARAM* data)
{
	s16* kind = (s16*)data->setBuffer;

	if (*kind < 0) {
		*kind = 0;
	}
	if (*kind > 1) {
		*kind = 1;
	}
	containerFieldNames[0] = containerKindNames[*kind];
}
