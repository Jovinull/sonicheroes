#include "types.h"

// The unload and load hooks rel/fan_object_register.cpp puts in the stage13D
// fan's editor record. The load reads the object's model and the unload forgets
// it (the stage resource manager owns it).

typedef struct RpClump RpClump;

extern "C" char fanObjectModelName[];
extern "C" RpClump* fanObjectModel;

RpClump* objPointerReadFromClumpAnim(char* name);

extern "C" void fanUnload(void)
{
	fanObjectModel = NULL;
}

extern "C" void fanLoad(void)
{
	fanObjectModel = objPointerReadFromClumpAnim(fanObjectModelName);
}
