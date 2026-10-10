#include "types.h"

// The unload and load hooks rel/fan_assets.cpp puts in the fan's editor record.
// The load reads the object's model and the unload forgets it (the stage
// resource manager owns it).

typedef struct RpClump RpClump;

extern "C" char fanModelName[];
extern "C" RpClump* fanModel;

RpClump* objPointerReadFromClumpAnim(char* name);

extern "C" void fanUnload(void)
{
	fanModel = NULL;
}

extern "C" void fanLoad(void)
{
	fanModel = objPointerReadFromClumpAnim(fanModelName);
}
