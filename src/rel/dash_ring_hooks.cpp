#include "types.h"

// The unload and load hooks rel/dash_ring_assets.cpp puts in the dash ring's
// editor record, in the twelve stage modules that share it.
//
// The load finds the ring's three textures in the stage's texture dictionary,
// reads the ring and its light (keeping the light's first material that uses
// one of the textures, as rel/reel_hooks.cpp does) and the ring's UV animation;
// when there is a ring, it keeps the material of its arrow texture and, when
// the animation and that material are both there, gives the ring's atomic with
// that texture its custom FX block, headed by the animation. The unload forgets
// the ring (the stage resource manager owns it).

typedef struct RwTexDictionary RwTexDictionary;
typedef struct RwTexture RwTexture;
typedef struct RpClump RpClump;
typedef struct RpAtomic RpAtomic;
typedef struct RpMaterial RpMaterial;

struct DashRingFX {
	RpClump* uv; // 0x00
	u8 pad04[0x40];
};

extern "C" char* dashRingTextureNames[3];
extern "C" char dashRingModelName[];
extern "C" char dashRingLightName[];
extern "C" char dashRingUVName[];
extern "C" char dashRingTexture[];
extern "C" RwTexture* dashRingTexture0;
extern "C" RwTexture* dashRingTexture1;
extern "C" RwTexture* dashRingTexture2;
extern "C" RpClump* dashRingModel;
extern "C" RpClump* dashRingLight;
extern "C" RpMaterial* dashRingLightMaterial;
extern "C" RpClump* dashRingUV;
extern "C" RpMaterial* dashRingMaterial;
extern "C" DashRingFX dashRingFX;

extern "C" RwTexture* fn_801A4BBC(RwTexDictionary* dictionary, char* name);
RwTexDictionary* objRwTexDictionaryGetPointer();
RpClump* objPointerReadFromClumpAnim(char* name);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* material, char* name);
RpAtomic* objRpClumpGetAtomicWithTexture(RpClump* clump, RpAtomic* atomic, char* name);
void AtomicSetCustomFXTexture(RpAtomic* atomic, void* fx);

extern "C" void dashRingUnload(void)
{
	dashRingModel = NULL;
}

extern "C" void dashRingLoad(void)
{
	RwTexDictionary* dictionary = objRwTexDictionaryGetPointer();
	s32 i;

	dashRingTexture0      = fn_801A4BBC(dictionary, dashRingTextureNames[0]);
	dashRingTexture1      = fn_801A4BBC(dictionary, dashRingTextureNames[1]);
	dashRingTexture2      = fn_801A4BBC(dictionary, dashRingTextureNames[2]);
	dashRingModel         = objPointerReadFromClumpAnim(dashRingModelName);
	dashRingLight         = objPointerReadFromClumpAnim(dashRingLightName);
	dashRingLightMaterial = NULL;
	for (i = 0; dashRingLightMaterial == NULL; i++) {
		dashRingLightMaterial = objRpClumpGetMaterialWithSpecificTexture(
		    dashRingLight, NULL, dashRingTextureNames[i]);
	}
	dashRingUV = objPointerReadFromClumpAnim(dashRingUVName);
	if (dashRingModel != NULL) {
		dashRingMaterial
		    = objRpClumpGetMaterialWithSpecificTexture(dashRingModel, NULL, dashRingTexture);
		if (dashRingUV != NULL && dashRingMaterial != NULL) {
			dashRingFX.uv = dashRingUV;
			AtomicSetCustomFXTexture(
			    objRpClumpGetAtomicWithTexture(dashRingModel, NULL, dashRingTexture), &dashRingFX);
		}
	}
}
