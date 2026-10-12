#include "types.h"

// The unload and load hooks rel/big_rings_assets.cpp puts in the big ring's
// editor record, in the thirteen stage modules that share it. The load clears the
// word at bigRingsState, reads the ring (keeping its material for the hint ring
// texture when there is a ring) and its effect, which ignores the lights. The
// unload forgets all of it (the stage resource manager owns the models).

typedef struct RpClump RpClump;
typedef struct RpMaterial RpMaterial;

extern "C" char bigRingsModelName[];
extern "C" char bigRingsTexture[];
extern "C" char bigRingsEffectName[];
extern "C" s32 bigRingsState;
extern "C" RpClump* bigRingsModel;
extern "C" RpMaterial* bigRingsMaterial;
extern "C" RpClump* bigRingsEffect;

RpClump* objPointerReadFromClumpAnim(char* name);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* material, char* name);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);

extern "C" void bigRingsUnload(void)
{
	bigRingsState    = 0;
	bigRingsModel    = NULL;
	bigRingsMaterial = NULL;
	bigRingsEffect   = NULL;
}

extern "C" void bigRingsLoad(void)
{
	bigRingsState = 0;
	bigRingsModel = objPointerReadFromClumpAnim(bigRingsModelName);
	if (bigRingsModel != NULL) {
		bigRingsMaterial
		    = objRpClumpGetMaterialWithSpecificTexture(bigRingsModel, NULL, bigRingsTexture);
	}
	bigRingsEffect = objPointerReadFromClumpAnim(bigRingsEffectName);
	if (bigRingsEffect != NULL) {
		objRpClumpForAllGeometrysToIgnoreLights(bigRingsEffect);
	}
}
