#include "types.h"

// The unload and load hooks rel/pole_assets.cpp puts in the pole's editor
// record. The load reads the object's model and the unload forgets it (the
// stage resource manager owns it).

typedef struct RpClump RpClump;

extern "C" char poleModelName[];
extern "C" RpClump* poleModel;

RpClump* objPointerReadFromClumpAnim(char* name);

extern "C" void poleUnload(void)
{
	poleModel = NULL;
}

extern "C" void poleLoad(void)
{
	poleModel = objPointerReadFromClumpAnim(poleModelName);
}
