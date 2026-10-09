// TObjRailChimney's destructor, out of line. For its part it takes the clump
// out of its world slot (fn_8015BBF8) if it was added, destroys it
// (fn_80150958) and clears both fields. The loop over one part is the
// original's: it hoists the model file's address, the world table's and the
// constant 0 before the part, into saved registers (rel/bridge_dtor.cpp has the
// long form). The class is shared through rail_chimney_class.inc, where the
// destructor is declared after the class's first other virtual so this unit
// does not emit the vtable.

#define RAIL_CHIMNEY_CTOR inline
#include "src/rel/rail_chimney_class.inc"

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

TObjRailChimney::~TObjRailChimney()
{
	ModelFile* file = &railChimneyModelFile;

	for (int i = 0; i < 1; i++) {
		if (added == 1) {
			fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), clump);
			added = 0;
		}
		fn_80150958(clump);
		clump = NULL;
	}
}
