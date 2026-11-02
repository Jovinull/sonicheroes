// TObjEnemyCloud::Finalize and Initialize (the PS2 build's names), out of line
// in stage28D; the bodies are shared through enemy_sky_load.inc.

#define SKY_LOADER     extern "C"
#define SKY_FINALIZE   Finalize__14TObjEnemyCloudFv
#define SKY_INITIALIZE Initialize__14TObjEnemyCloudFv
#define SKY(x)         enemySky##x
#include "src/rel/enemy_sky_load.inc"
