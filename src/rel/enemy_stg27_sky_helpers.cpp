// TObjEnemyStg27Sky's small members, out of line: SetPosition, DestroyClump,
// CloneClump and ResetVariable, the copies each module keeps beside the ones its
// constructor and destructor inline. The class and the bodies are shared
// through enemy_stg27_sky_class.inc.

#define ENEMY_STG27_SKY_CTOR inline
#define ENEMY_STG27_SKY_HELPER
#include "src/rel/enemy_stg27_sky_class.inc"
