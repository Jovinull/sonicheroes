// TObjEnemyStg27Sky's destructor, out of line. It destroys its clump
// (fn_80150958) if it has one and clears the pointer. The class is shared
// through enemy_stg27_sky_class.inc, where the destructor is declared after the
// class's first other virtual so this unit does not emit the vtable.

#define ENEMY_STG27_SKY_CTOR inline
#include "src/rel/enemy_stg27_sky_class.inc"

extern "C" void fn_80150958(RpClump* clump);

TObjEnemyStg27Sky::~TObjEnemyStg27Sky()
{
	if (clump != NULL) {
		fn_80150958(clump);
		clump = NULL;
	}
}
