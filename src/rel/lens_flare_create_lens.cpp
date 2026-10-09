// CreateEfLens (PS2 symbols), which the module's load routine hands out by
// address: a free-standing lens flare, a real new-expression of
// TObjEFLensTmp with both constructors inlined, then placed through its own
// SetPosition (a virtual call) if the allocation succeeded. TObjEFLensTmp has
// a single base, so the allocation lands in r31 directly, without the `mr r0,
// r3` the placed objects' factories have. The classes are in
// lens_flare_class.inc.

#define LENS_FLARE_CTOR     inline
#define LENS_FLARE_SET_CTOR inline
#define LENS_FLARE_DTOR     inline
#include "src/rel/lens_flare_class.inc"

TObjEFLens* CreateEfLens(TObject* parent, RwV3d* position)
{
	TObjEFLensTmp* lens = new TObjEFLensTmp(parent);

	if (lens != NULL) {
		lens->SetPosition(position);
	}
	return lens;
}
