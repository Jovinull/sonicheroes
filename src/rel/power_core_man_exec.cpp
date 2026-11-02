#include "types.h"

// TEnemyPowerCoreMan::Exec (the PS2 build's name), the same in the bonus
// stages (31D-33D): while the game runs, five requests in a row make a power
// core at the last requested place, of the type the manager decides from the
// leaders' player numbers (DecideTypeFromLeaderPlayerNumber, left as
// assembly), its constructor inlined.

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

extern "C" void Exec__18TEnemyPowerCoreManFv(PowerCoreMan* object)
{
	if (powerCoreGameStopped()) {
		object->count = 0;
		return;
	}
	if (object->count > 4) {
		object->count = 0;
		object->params.type
		    = DecideTypeFromLeaderPlayerNumber__18TEnemyPowerCoreManFi(object, object->type);
		new TEnemyPowerCore(lbl_8042C10C, &object->params);
	}
}
