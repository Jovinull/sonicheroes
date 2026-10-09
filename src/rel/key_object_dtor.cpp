// TObjKey's destructor, out of line. With a clump, it takes it out of the
// world slot at +0x725C (fn_8015BBF8), destroys it (fn_80150958) and clears the
// pointer; it ends the set object when its condition has bit 0x10000 set; and
// it deletes the object at +0xD8 if there is one, through its virtual
// destructor (the explicit test plus the delete's own gives the original's
// two `beq`). The class is shared through key_object_class.inc, where the
// destructor is declared after the class's first other virtual so this unit
// does not emit the vtable.

#define KEY_OBJECT_CTOR inline
#include "src/rel/key_object_class.inc"

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

TObjKey::~TObjKey()
{
	if (clump != NULL) {
		fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x725C), clump);
		fn_80150958(clump);
		clump = NULL;
	}
	if (TstConditionBit(0x10000)) {
		SetEnd();
	}
	if ((TObject*)unkD8 != NULL) {
		delete (TObject*)unkD8;
	}
}
