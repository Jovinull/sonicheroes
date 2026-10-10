#include "types.h"

// The unload and load hooks rel/key_register.cpp puts in the key's editor
// record: the load reads the key's model, the unload forgets it (the stage
// resource manager owns it).

typedef struct RpClump RpClump;

extern "C" char keyObjectModelName[];
extern "C" RpClump* keyObjectResource;

RpClump* objPointerReadFromClumpAnim(char* name);

extern "C" void keyObjectUnload(void)
{
	keyObjectResource = NULL;
}

extern "C" void keyObjectLoad(void)
{
	keyObjectResource = objPointerReadFromClumpAnim(keyObjectModelName);
}
