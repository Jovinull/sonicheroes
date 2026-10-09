// TObjEnemyStg27Cloud's destructor, out of line. It destroys its two clumps
// (fn_80150958), the second first, each only if present, and clears the
// pointers, as TObjEnemyCloud's does (rel/enemy_cloud_dtor.cpp). The class is
// shared through enemy_stg27_cloud_class.inc, where the destructor is declared
// after the class's first other virtual so this unit does not emit the
// vtable.

#define ENEMY_STG27_CLOUD_CTOR inline
#include "src/rel/enemy_stg27_cloud_class.inc"

extern "C" void fn_80150958(RpClump* clump);

TObjEnemyStg27Cloud::~TObjEnemyStg27Cloud()
{
	if (clump2 != NULL) {
		fn_80150958(clump2);
		clump2 = NULL;
	}
	if (clump != NULL) {
		fn_80150958(clump);
		clump = NULL;
	}
}
