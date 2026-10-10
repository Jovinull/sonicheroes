#include "types.h"

// The unload and load hooks and the factory rel/breakable_weight_register.cpp
// puts in the breakable weight's editor record, in the thirteen stage modules
// that share it.
//
// The load finds the weight's three textures in the stage's texture dictionary,
// reads its model, its laser effect and its broken model, then keeps the first
// material of the model that uses one of those textures, as rel/reel_hooks.cpp
// does for the reel. The unload only forgets what the load read (the stage
// resource manager owns it). The factory allocates 0x134 bytes and hands them
// to the module's constructor (left as assembly and named breakableWeightCtor
// here).

typedef struct RwTexDictionary RwTexDictionary;
typedef struct RwTexture RwTexture;
typedef struct RpClump RpClump;
typedef struct RpMaterial RpMaterial;

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" char* breakableWeightTextureNames[3];
extern "C" char breakableWeightModelName[];
extern "C" char breakableWeightLaserName[];
extern "C" char breakableWeightBrokenName[];
extern "C" RwTexture* breakableWeightTexture0;
extern "C" RwTexture* breakableWeightTexture1;
extern "C" RwTexture* breakableWeightTexture2;
extern "C" RpClump* breakableWeightModel;
extern "C" RpClump* breakableWeightLaser;
extern "C" RpClump* breakableWeightBroken;
extern "C" RpMaterial* breakableWeightMaterial;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* breakableWeightCtor(void* object, void* owner, s32 arg);
extern "C" RwTexture* fn_801A4BBC(RwTexDictionary* dictionary, char* name);
RwTexDictionary* objRwTexDictionaryGetPointer();
RpClump* objPointerReadFromClumpAnim(char* name);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* material, char* name);

extern "C" void breakableWeightUnload(void)
{
	breakableWeightModel    = NULL;
	breakableWeightLaser    = NULL;
	breakableWeightBroken   = NULL;
	breakableWeightMaterial = NULL;
	breakableWeightTexture0 = NULL;
	breakableWeightTexture1 = NULL;
	breakableWeightTexture2 = NULL;
}

extern "C" void breakableWeightLoad(void)
{
	RwTexDictionary* dictionary = objRwTexDictionaryGetPointer();
	s32 i;

	breakableWeightTexture0 = fn_801A4BBC(dictionary, breakableWeightTextureNames[0]);
	breakableWeightTexture1 = fn_801A4BBC(dictionary, breakableWeightTextureNames[1]);
	breakableWeightTexture2 = fn_801A4BBC(dictionary, breakableWeightTextureNames[2]);
	breakableWeightModel    = objPointerReadFromClumpAnim(breakableWeightModelName);
	breakableWeightLaser    = objPointerReadFromClumpAnim(breakableWeightLaserName);
	breakableWeightBroken   = objPointerReadFromClumpAnim(breakableWeightBrokenName);
	breakableWeightMaterial = NULL;
	for (i = 0; breakableWeightMaterial == NULL; i++) {
		breakableWeightMaterial = objRpClumpGetMaterialWithSpecificTexture(
		    breakableWeightModel, NULL, breakableWeightTextureNames[i]);
	}
}

extern "C" void breakableWeightCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x134);

	if (memory != NULL) {
		breakableWeightCtor(memory, lbl_8042C110, 0);
	}
}
