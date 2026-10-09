// TObjWaterSurface's destructor, out of line. It takes its clump out of its
// world slot (fn_8015BBF8) if it was added, destroys it (fn_80150958) and
// clears both fields. The model file's address is taken once at the top, the
// original's `addi r5` before the test; there is no loop around the part here
// (compare rel/bridge_dtor.cpp, whose 0 sits in a saved register). The class is
// shared through water_surface_class.inc, where the destructor is declared
// after the class's first other virtual so this unit does not emit the vtable.

#define WATER_SURFACE_CTOR inline
#include "src/rel/water_surface_class.inc"

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

TObjWaterSurface::~TObjWaterSurface()
{
	WaterSurfaceModelFile* file = &waterSurfaceModelFile;

	if (added == 1) {
		fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), clump);
		added = 0;
	}
	fn_80150958(clump);
	clump = NULL;
}
