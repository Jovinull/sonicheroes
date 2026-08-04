#include "types.h"

// The no-op reset hook and the unload hook shared by the twelve stage modules
// that carry this revision of the cannon object. The unload path only forgets
// the loaded resource; the stage resource manager owns its lifetime.

extern "C" void* cannonResource;

extern "C" void cannonReset(void) { }

extern "C" void cannonUnload(void)
{
	if (cannonResource != NULL) {
		cannonResource = NULL;
	}
}
