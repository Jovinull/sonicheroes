#include "types.h"

// The reset and unload hooks in HERMITCRAB OBJECT's editor record: the reset
// has nothing to do; the unload destroys the crab's model and its animation
// interpolator and forgets them.

typedef struct RpClump RpClump;

extern "C" RpClump* hermitcrabModel;
extern "C" void* hermitcrabAnimation;
extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8020C2D8(void* interpolator);

extern "C" void hermitcrabObjectReset(void) { }

extern "C" void hermitcrabObjectUnload(void)
{
	fn_80150958(hermitcrabModel);
	hermitcrabModel = NULL;
	fn_8020C2D8(hermitcrabAnimation);
	hermitcrabAnimation = NULL;
}
