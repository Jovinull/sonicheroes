#include "types.h"

// The unload and load hooks rel/target_assets.cpp puts in the target's editor
// record: the load reads the target's model, the unload forgets it (the stage
// resource manager owns it).

typedef struct RpClump RpClump;

extern "C" char targetModelName[];
extern "C" RpClump* targetResource;

RpClump* objPointerReadFromClumpAnim(char* name);

extern "C" void targetUnload(void)
{
	targetResource = NULL;
}

extern "C" void targetLoad(void)
{
	targetResource = objPointerReadFromClumpAnim(targetModelName);
}
