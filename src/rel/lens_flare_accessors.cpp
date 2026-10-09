// The lens classes' small virtuals that the original emits together after the
// factory: TObjEFLensTmp's GetPosition and SetPosition, and TObjEFLensSet's
// GetPosition, the placement's position. TObjEFLensSet's SetPosition follows
// them as rel/lens_flare_test.cpp (lensFlareIsSet). The run starts one
// function earlier, with TObjEFLensTmp's EditOnChange (`while (param ==
// NULL) { }`), which is left in the auto region: its branch back to its own
// first instruction is a relocation against the function's symbol in the
// split original and a resolved local branch in ours, so exato does not call
// it exact although objdiff and the link agree. The classes are in
// lens_flare_class.inc.

#define LENS_FLARE_CTOR     inline
#define LENS_FLARE_SET_CTOR inline
#define LENS_FLARE_DTOR     inline
#include "src/rel/lens_flare_class.inc"

RwV3d* TObjEFLensTmp::GetPosition()
{
	return &pos;
}

s32 TObjEFLensTmp::SetPosition(RwV3d* position)
{
	pos = *position;
	return 1;
}

RwV3d* TObjEFLensSet::GetPosition()
{
	return &ObjParam->setData.pos;
}
