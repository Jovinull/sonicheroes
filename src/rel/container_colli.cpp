// TObjContainer's SetOriginalCColli and SetFallingCColli (the PS2 build's
// names), which switch the crate's second collision shape between its resting
// form (attribute 0x10) and its falling one (attribute 0, centred and sized
// from the crate's height against its position). The unit is built without
// fused multiply-add (cflags_rel_nofma), as the falling shape's centre shows
// the original was. The class is in game/obj_container.h.

#include "game/obj_container.h"

extern "C" const f32 containerHalf[1];

void TObjContainer::SetOriginalCColli()
{
	info[1].attr = 0x10;
}

void TObjContainer::SetFallingCColli()
{
	info[1].attr     = 0;
	info[1].center.y = containerHalf[0] * (pos.y + height) - pos.y;
	info[1].b        = containerHalf[0] * (pos.y - height);
}
