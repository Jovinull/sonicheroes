// TObjContainer's destructor, out of line in every stage module's run: it
// takes the crate's clump out of the world slot at +0x725C if there is one,
// destroys it and clears the pointer, then ends the set object when its
// condition has bit 0x10000 set. The materials' destructors
// (rel/wood_container_dtor.cpp and the others) do the clump part themselves
// before calling this one. The class is in game/obj_container.h.

#include "game/obj_container.h"

extern "C" u8* lbl_8042C1D0;
extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

TObjContainer::~TObjContainer()
{
	if (clump != NULL) {
		fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x725C), clump);
		fn_80150958(clump);
		clump = NULL;
	}
	if (TstConditionBit(0x10000)) {
		SetEnd();
	}
}
