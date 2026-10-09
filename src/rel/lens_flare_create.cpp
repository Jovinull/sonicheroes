// lensFlareCreate, the factory the editor record for TObjEFLensSet points at,
// in the thirteen stage modules that share the engine core.
//
// The allocation is a real new-expression of the C++ class with every
// constructor on the way inlined. TObjEFLensSet derives from TObjEFLens, the
// lens flare itself, and from the placement base; the PS2 build names all
// three classes, EFLensPtcl included. TObjEFLens adds three virtuals of its
// own (EditOnChange, GetPosition and SetPosition), which is why the placement
// base's vtable starts 0x38 into the set's.
//
// TObjEFLens joins the end of the module's chain of lens flares (as
// rel/s23_warppos_create.cpp does) and builds its twelve particles, each a real
// new-expression through the global operator new: a particle takes its index,
// its owner and its entry of the module's table, and joins the end of the
// owner's particle list. The set then folds the placement's kind into 0 or 1
// and sets or clears bit 0x400 of the placement's flags to match.

#define LENS_FLARE_CTOR     inline
#define LENS_FLARE_SET_CTOR inline
#define LENS_FLARE_DTOR     inline
#include "src/rel/lens_flare_class.inc"

extern "C" void lensFlareCreate(void)
{
	new TObjEFLensSet(lbl_8042C110);
}
