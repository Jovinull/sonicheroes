#include "types.h"

// The unload and load hooks rel/reel_assets.cpp puts in REEL OBJECT's editor
// record, in the twelve stage modules that carry that revision of the reel.
//
// Load finds the reel's three textures in the stage's texture dictionary,
// reads the reel's model and then looks for the first of those texture names
// that one of the model's materials uses, keeping that material. Unload only
// forgets the model and the material; the stage resource manager owns their
// lifetime.

typedef struct RwTexDictionary RwTexDictionary;
typedef struct RwTexture RwTexture;
typedef struct RpClump RpClump;
typedef struct RpMaterial RpMaterial;

extern char* reelTextureNames[3];
extern char reelModelName[];
extern RpClump* reelClump;
extern RpMaterial* reelMaterial;
extern RwTexture* reelTexture0;
extern RwTexture* reelTexture1;
extern RwTexture* reelTexture2;

RwTexDictionary* objRwTexDictionaryGetPointer();
RpClump* objPointerReadFromClumpAnim(char* name);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* material, char* name);
extern "C" RwTexture* fn_801A4BBC(RwTexDictionary* dictionary, char* name);

extern "C" void reelUnload(void)
{
	reelClump    = NULL;
	reelMaterial = NULL;
}

extern "C" void reelLoad(void)
{
	RwTexDictionary* dictionary = objRwTexDictionaryGetPointer();
	s32 i;

	reelTexture0 = fn_801A4BBC(dictionary, reelTextureNames[0]);
	reelTexture1 = fn_801A4BBC(dictionary, reelTextureNames[1]);
	reelTexture2 = fn_801A4BBC(dictionary, reelTextureNames[2]);
	reelClump    = objPointerReadFromClumpAnim(reelModelName);
	reelMaterial = NULL;
	for (i = 0; reelMaterial == NULL; i++) {
		reelMaterial
		    = objRpClumpGetMaterialWithSpecificTexture(reelClump, NULL, reelTextureNames[i]);
	}
}
