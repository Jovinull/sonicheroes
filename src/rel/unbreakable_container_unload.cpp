#include "types.h"

// Clears the loaded unbreakable-container resource. The resource manager owns
// the allocation, so this hook only drops the stage-local reference.

extern "C" void* unbreakableContainerResource;

extern "C" void unbreakableContainerUnload(void)
{
	unbreakableContainerResource = NULL;
}
