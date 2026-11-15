#include "game/enemy/e_database.h"
#include "game/enemy/e_iconman.h"

extern "C" void fn_800A73B4(void)
{
	TEnemyIconMan::Finalize();
	if (TEnemyDataBase::mpDataBase == NULL) {
		new TEnemyDataBase;
	}
	TEnemyDataBase::mpDataBase->Delete(ENEMY_DB_COMMON);
	if (TEnemyDataBase::mpDataBase != NULL) {
		delete TEnemyDataBase::mpDataBase;
		TEnemyDataBase::mpDataBase = NULL;
	}
}
