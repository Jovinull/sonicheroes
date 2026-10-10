#include "types.h"

// The unload and load hooks rel/laser_fence_assets.cpp puts in the laser
// fence's editor record: the load reads the laser and the fence models, the
// unload forgets them (the stage resource manager owns them).

typedef struct RpClump RpClump;

extern "C" char laserFenceLaserName[];
extern "C" char laserFenceModelName[];
extern "C" RpClump* laserFenceLaser;
extern "C" RpClump* laserFenceModel;

RpClump* objPointerReadFromClumpAnim(char* name);

extern "C" void laserFenceUnload(void)
{
	laserFenceModel = NULL;
	laserFenceLaser = NULL;
}

extern "C" void laserFenceLoad(void)
{
	laserFenceLaser = objPointerReadFromClumpAnim(laserFenceLaserName);
	laserFenceModel = objPointerReadFromClumpAnim(laserFenceModelName);
}
