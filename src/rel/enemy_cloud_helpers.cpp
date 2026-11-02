// TObjEnemyCloud's small members, out of line: SetPosition, DestroyClump,
// CloneClump and ResetVariable, the copies stage28D keeps beside the ones its
// constructor and destructor inline. The class and the bodies are shared
// through enemy_cloud_class.inc.

#define ENEMY_CLOUD_CTOR inline
#define ENEMY_CLOUD_HELPER
#include "src/rel/enemy_cloud_class.inc"
