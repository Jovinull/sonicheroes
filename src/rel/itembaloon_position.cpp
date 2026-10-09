// TObjItembaloon's two virtuals of its own, UpdatePosition and GetPosition (the
// PS2 build's names), on the balloon's position. The class is shared through
// itembaloon_class.inc.

#define ITEMBALOON_CTOR inline
#include "src/rel/itembaloon_class.inc"

void TObjItembaloon::UpdatePosition(RwV3d* position)
{
	pos = *position;
}

RwV3d* TObjItembaloon::GetPosition()
{
	return &pos;
}
