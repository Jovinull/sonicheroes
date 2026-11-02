// stg28ObjUnload and stg28ObjLoad, the stage's object set's unload and load
// hooks: they free and load the sky (the loader enemy_sky_load.inc shares,
// inlined here).

#define SKY_LOADER     static inline
#define SKY_FINALIZE   skyFinalize
#define SKY_INITIALIZE skyInitialize
#define SKY(x)         enemySky##x
#include "src/rel/enemy_sky_load.inc"

extern "C" void stg28ObjUnload(void)
{
	skyFinalize();
}

extern "C" void stg28ObjLoad(void)
{
	skyInitialize();
}
