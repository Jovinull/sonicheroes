// TObjChao's destructor, out of line: it deletes the object at 0xEC if there is
// one, destroys the chao's clump and clears both pointers, then ends the set
// object when its condition has bit 0x10000 set. The class is in
// chao_class.inc.

#include "src/rel/chao_class.inc"

extern "C" void fn_80150958(RpClump* clump);

TObjChao::~TObjChao()
{
	if (unkEC != NULL) {
		delete unkEC;
		unkEC = NULL;
	}
	if (clump != NULL) {
		fn_80150958(clump);
		clump = NULL;
	}
	if (TstConditionBit(0x10000)) {
		SetEnd();
	}
}
