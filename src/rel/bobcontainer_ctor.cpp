// TObjBobcontainer's constructor, which the unbreakable bobsleigh crate's
// constructor calls: as rel/container_ctor.cpp, it takes the placement's
// position, angle and kind as SetParameter does (inline here), then clears the
// kind and the bytes beside it, the field at 0xDC and the clump, sets 0xBC to 1
// and gives the collision its shape, then clears the collision's strength. The
// class is in game/obj_container.h.

#include "game/obj_container.h"

extern "C" char* CL_TObjBobcontainer;
extern "C" const f32 bobcontainerZero[1];
extern "C" CCL_INFO bobcontainerCclInfo[1];

TObjBobcontainer::TObjBobcontainer(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjBobcontainer;
	DispTime  = 0xF8;

	pos  = ObjParam->setData.pos;
	ang  = ObjParam->setData.ang;
	kind = *(s16*)ObjParam->setData.setBuffer;

	unkC2 = 0;
	kind  = 0;
	unkC1 = 0;
	unkDC = bobcontainerZero[0];
	unkBC = 1;
	clump = NULL;
	Init(bobcontainerCclInfo, 1, 5);
	strength = 0;
}
