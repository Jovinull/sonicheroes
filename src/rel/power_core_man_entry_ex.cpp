#include "types.h"

// TEnemyPowerCoreMan::EntryEx (the PS2 build's name), the same in the bonus
// stages (31D-33D): a power core of the given type at a place right away; the
// manager decides its type from the leaders' player numbers
// (DecideTypeFromLeaderPlayerNumber, left as assembly) and creates it (as
// TEnemyPowerCore::Create does, inlined).

#include "src/rel/power_core_class.inc"

typedef struct PowerCoreMan {
	u8 unk00[0x28];
	s32 count;              // 0x28
	s32 type;               // 0x2C
	sEnemyPowerCore params; // 0x30
} PowerCoreMan;

extern "C" TObject* lbl_8042C10C;
extern "C" s32 DecideTypeFromLeaderPlayerNumber__18TEnemyPowerCoreManFi(
    PowerCoreMan* object, s32 type);

extern "C" void EntryEx__18TEnemyPowerCoreManFPC5RwV3di(
    PowerCoreMan* object, const RwV3d* pos, s32 type)
{
	object->count        = 0;
	object->type         = type;
	object->params.pos.x = pos->x;
	object->params.pos.y = pos->y;
	object->params.pos.z = pos->z;
	object->params.type
	    = DecideTypeFromLeaderPlayerNumber__18TEnemyPowerCoreManFi(object, object->type);
	new TEnemyPowerCore(lbl_8042C10C, &object->params);
}
