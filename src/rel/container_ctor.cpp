// TObjContainer's constructor, which every crate's constructor calls: it takes
// the placement's position, angle and kind as SetParameter does (inline here),
// then clears the kind and the bytes beside it, the field at 0xDC and the clump,
// sets 0xBC to 1 and gives the collision its two shapes. The class is in
// game/obj_container.h.

#include "game/obj_container.h"

extern "C" char* CL_TObjContainer;
extern "C" const f32 containerZero[1];
extern "C" CCL_INFO containerCclInfo[2];

TObjContainer::TObjContainer(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjContainer;
	DispTime  = 0xF8;

	pos  = ObjParam->setData.pos;
	ang  = ObjParam->setData.ang;
	kind = *(s16*)ObjParam->setData.setBuffer;

	unkC2 = 0;
	kind  = 0;
	unkC1 = 0;
	unkDC = containerZero[0];
	unkBC = 1;
	clump = NULL;
	Init(containerCclInfo, 2, 5);
}
