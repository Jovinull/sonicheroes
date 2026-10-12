#include "types.h"

// EffSpark::TDisp (the PS2 build's class; its vtable's TDisp): with additive
// blending (source blend 3, destination 2, the old modes restored after) it
// tints and draws every live spark.

#include "src/rel/eff_spark_class.inc"

extern "C" s32 fn_80194294(s32 state, void* value);
extern "C" s32 fn_80194234(s32 state, void* value);
extern "C" void fn_8014FF2C(RpClump* clump);
void objRpClumpForAllMaterialsToChangeMaterialColor(RpClump* clump, RwRGBAReal* color);

void EffSpark::TDisp()
{
	EffSparkParticle* particle;
	s32 src;
	s32 dst;
	int i;

	fn_80194294(10, &src);
	fn_80194294(11, &dst);
	fn_80194234(10, (void*)3);
	fn_80194234(11, (void*)2);
	for (i = 0; i < 0x200; i++) {
		particle = sparks[i];
		if (particle != NULL) {
			objRpClumpForAllMaterialsToChangeMaterialColor(particle->clump, &particle->color);
			fn_8014FF2C(particle->clump);
		}
	}
	fn_80194234(10, (void*)src);
	fn_80194234(11, (void*)dst);
}
