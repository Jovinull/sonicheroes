#include "types.h"

// The spring mushroom's Unload hook (springMushUnload here): the mushroom's
// delta morph animation is released (fn_8013BD74).

struct RpDMorphAnimation;

extern "C" RpDMorphAnimation* springMushResource;

extern "C" void fn_8013BD74(RpDMorphAnimation* animation);

extern "C" void springMushUnload(void)
{
	fn_8013BD74(springMushResource);
}
