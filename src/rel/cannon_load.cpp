#include "types.h"

// The load hook and the factory rel/cannon_register.cpp puts in the cannon's
// editor record, in the thirteen stage modules that carry this revision of
// the cannon.
//
// The load reads the cannon's model and its effect model; the effect ignores
// the lights, keeps three of its materials (each search goes on from the one
// before, so they are stored last to first) and gets alpha applied to colour.
// The factory allocates 0x164 bytes and hands them to the module's constructor
// (left as assembly and named cannonCtor here, as rel/reel_assets.cpp names the
// reel's).

typedef struct RpClump RpClump;
typedef struct RpMaterial RpMaterial;

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" char cannonModelName[];
extern "C" char cannonEffectName[];
extern "C" RpClump* cannonResource;
extern "C" RpClump* cannonEffect;
extern "C" RpMaterial* cannonEffectMaterials[3];

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* cannonCtor(void* object, void* owner);
RpClump* objPointerReadFromClumpAnim(char* name);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* material, char* name);
void objRpClumpForAllGeometriesToAffectAlphaToColor(RpClump* clump);

extern "C" void cannonLoad(void)
{
	cannonResource = objPointerReadFromClumpAnim(cannonModelName);
	cannonEffect   = objPointerReadFromClumpAnim(cannonEffectName);
	if (cannonEffect != NULL) {
		objRpClumpForAllGeometrysToIgnoreLights(cannonEffect);
		cannonEffectMaterials[2]
		    = objRpClumpGetMaterialWithSpecificTexture(cannonEffect, NULL, NULL);
		cannonEffectMaterials[1] = objRpClumpGetMaterialWithSpecificTexture(
		    cannonEffect, cannonEffectMaterials[2], NULL);
		cannonEffectMaterials[0] = objRpClumpGetMaterialWithSpecificTexture(
		    cannonEffect, cannonEffectMaterials[1], NULL);
		objRpClumpForAllGeometriesToAffectAlphaToColor(cannonEffect);
	}
}

extern "C" void cannonCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x164);

	if (memory != NULL) {
		cannonCtor(memory, lbl_8042C110);
	}
}
