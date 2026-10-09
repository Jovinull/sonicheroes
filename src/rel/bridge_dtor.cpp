// TObjBridge's destructor, out of line. It takes its clump out of its world
// slot (fn_8015BBF8) if it was added, destroys it (fn_80150958) and clears both
// fields.
//
// The original walks its parts in a loop, here of one, like the multi-part
// objects' destructors (rel/big_chip_dtor.cpp). The loop is what puts the
// model file's address, the world table's address and the constant 0 for the
// two stores in registers before the part, the 0 in a saved register across
// both calls (`li r31, 0`); straight-line code rematerializes the 0 after each
// call instead. The class is shared through bridge_class.inc, where the
// destructor is declared after the class's first other virtual so this unit
// does not emit the vtable.

#define BRIDGE_CTOR inline
#include "src/rel/bridge_class.inc"

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

TObjBridge::~TObjBridge()
{
	ModelFile* file = &bridgeModelFile;

	for (int i = 0; i < 1; i++) {
		if (added == 1) {
			fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), clump);
			added = 0;
		}
		fn_80150958(clump);
		clump = NULL;
	}
}
