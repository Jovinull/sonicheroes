// TObjFloatJ's destructor, out of line. It takes its clump out of the world
// slot at +0x725C (fn_8015BBF8), where the constructor put it, destroys it
// (fn_80150958) and clears the pointer. The class is shared through
// float_j_class.inc, where the destructor is declared after the class's first
// other virtual so this unit does not emit the vtable.

#define FLOAT_J_CTOR inline
#include "src/rel/float_j_class.inc"

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

TObjFloatJ::~TObjFloatJ()
{
	fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x725C), clump);
	fn_80150958(clump);
	clump = NULL;
}
