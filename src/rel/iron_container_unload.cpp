#include "types.h"

// Clears the loaded iron-container resource. The resource manager owns the
// allocation, so this hook only drops the stage-local reference.

extern "C" void* ironContainerResource;

extern "C" void ironContainerUnload(void)
{
	ironContainerResource = NULL;
}
