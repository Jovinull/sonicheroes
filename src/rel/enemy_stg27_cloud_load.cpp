// TObjEnemyStg27Cloud::Finalize and Initialize (the PS2 build's names), out of
// line in stages 26 and 27; the bodies are shared through enemy_sky_load.inc.

#define SKY_LOADER     extern "C"
#define SKY_FINALIZE   Finalize__19TObjEnemyStg27CloudFv
#define SKY_INITIALIZE Initialize__19TObjEnemyStg27CloudFv
#define SKY(x)         enemyStg27Sky##x
#include "src/rel/enemy_sky_load.inc"
