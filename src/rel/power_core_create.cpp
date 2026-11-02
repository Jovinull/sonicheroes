#include "types.h"

// TEnemyPowerCore::Create (the PS2 build's name), the same in the bonus
// stages (31D-33D): a new power core from the given spawn parameters, its
// constructor (rel/power_core_class.inc) inlined.

#include "src/rel/power_core_class.inc"

extern "C" TObject* lbl_8042C10C;

extern "C" void Create__15TEnemyPowerCoreFPC15sEnemyPowerCore(const sEnemyPowerCore* params)
{
	new TEnemyPowerCore(lbl_8042C10C, params);
}
