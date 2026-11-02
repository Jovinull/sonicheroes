// TObjEnemySky's small members, out of line: SetPosition, DestroyClump,
// CloneClump and ResetVariable, the copies stage28D keeps beside the ones its
// constructor and destructor inline. The class and the bodies are shared
// through enemy_sky_class.inc.

#define ENEMY_SKY_CTOR inline
#define ENEMY_SKY_HELPER
#include "src/rel/enemy_sky_class.inc"
