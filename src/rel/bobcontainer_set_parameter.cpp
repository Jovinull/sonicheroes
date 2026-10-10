// TObjBobcontainer::SetParameter: the bobsleigh crate takes its position, angle
// and kind (the first parameter, a halfword kept as a byte) from its placement.
// The class is in game/obj_container.h.

#include "game/obj_container.h"

void TObjBobcontainer::SetParameter()
{
	pos  = ObjParam->setData.pos;
	ang  = ObjParam->setData.ang;
	kind = *(s16*)ObjParam->setData.setBuffer;
}
