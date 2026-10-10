// TObjContWood's destructor, out of line: it takes the crate's clump out of
// the world slot at +0x725C, destroys it and clears the pointer, and the
// compiler then calls TObjContainer's destructor, which does the same check
// before ending the set object. The class is shared through
// wood_container_class.inc.

#define WOOD_CONTAINER_CTOR inline
#include "src/rel/wood_container_class.inc"

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

TObjContWood::~TObjContWood()
{
	if (clump != NULL) {
		fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x725C), clump);
		fn_80150958(clump);
		clump = NULL;
	}
}
