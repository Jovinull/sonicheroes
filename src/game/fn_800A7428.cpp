#include "game/enemy/e_database.h"
#include "game/enemy/e_iconman.h"

extern "C" char lbl_80253058[];

extern "C" void fn_800A7428()
{
	TEnemyDataBase::GetInstance()->Add(ENEMY_DB_COMMON, lbl_80253058);
	TEnemyIconMan::Initialize();
}
