#include "types.h"

// The unload and load hooks and the factory rel/weight_register.cpp puts in the
// weight's editor record, in the thirteen stage modules that share it.
//
// The load finds the weight's three textures in the stage's texture dictionary,
// reads its model, its laser effect and its broken model, then keeps the first
// material of the model that uses one of those textures, as rel/reel_hooks.cpp
// does for the reel. The unload only forgets what the load read (the stage
// resource manager owns it). The factory allocates 0x110 bytes and hands them
// to the module's constructor (left as assembly and named weightCtor here),
// with 0 as its third argument.

typedef struct RwTexDictionary RwTexDictionary;
typedef struct RwTexture RwTexture;
typedef struct RpClump RpClump;
typedef struct RpMaterial RpMaterial;

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" char* weightTextureNames[3];
extern "C" char weightModelName[];
extern "C" char weightLaserName[];
extern "C" char weightBrokenName[];
extern "C" RwTexture* weightTexture0;
extern "C" RwTexture* weightTexture1;
extern "C" RwTexture* weightTexture2;
extern "C" RpClump* weightModel;
extern "C" RpClump* weightLaser;
extern "C" RpClump* weightBroken;
extern "C" RpMaterial* weightMaterial;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* weightCtor(void* object, void* owner, s32 arg);
extern "C" RwTexture* fn_801A4BBC(RwTexDictionary* dictionary, char* name);
RwTexDictionary* objRwTexDictionaryGetPointer();
RpClump* objPointerReadFromClumpAnim(char* name);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* material, char* name);

extern "C" void weightUnload(void)
{
	weightModel    = NULL;
	weightLaser    = NULL;
	weightBroken   = NULL;
	weightMaterial = NULL;
	weightTexture0 = NULL;
	weightTexture1 = NULL;
	weightTexture2 = NULL;
}

extern "C" void weightLoad(void)
{
	RwTexDictionary* dictionary = objRwTexDictionaryGetPointer();
	s32 i;

	weightTexture0 = fn_801A4BBC(dictionary, weightTextureNames[0]);
	weightTexture1 = fn_801A4BBC(dictionary, weightTextureNames[1]);
	weightTexture2 = fn_801A4BBC(dictionary, weightTextureNames[2]);
	weightModel    = objPointerReadFromClumpAnim(weightModelName);
	weightLaser    = objPointerReadFromClumpAnim(weightLaserName);
	weightBroken   = objPointerReadFromClumpAnim(weightBrokenName);
	weightMaterial = NULL;
	for (i = 0; weightMaterial == NULL; i++) {
		weightMaterial
		    = objRpClumpGetMaterialWithSpecificTexture(weightModel, NULL, weightTextureNames[i]);
	}
}

extern "C" void weightCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x110);

	if (memory != NULL) {
		weightCtor(memory, lbl_8042C110, 0);
	}
}
