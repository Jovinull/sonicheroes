// TObjPowder's destructor, out of line. For each of its 128 grains that has a
// clump it takes the clump out of the world slot of the model file the
// placement picks (fn_8015BBF8) if it was added, destroys it (fn_80150958)
// and clears both fields. The placement's parameters are read inside the
// clump test, before the added test, as the original loads them. The class
// is shared through powder_class.inc, where the destructor is declared after
// the class's first other virtual so this unit does not emit the vtable.

#define POWDER_CTOR inline
#include "src/rel/powder_class.inc"

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

TObjPowder::~TObjPowder()
{
	for (int i = 0; i < 128; i++) {
		if (parts[i].clump != NULL) {
			PowderParam* param = (PowderParam*)ObjParam->setData.setBuffer;
			if (parts[i].added == 1) {
				fn_8015BBF8(
				    *(void**)(lbl_8042C1D0 + 0x7250 + powderModelFiles[param->kind].world * 4),
				    parts[i].clump);
				parts[i].added = 0;
			}
			fn_80150958(parts[i].clump);
			parts[i].clump = NULL;
		}
	}
}
