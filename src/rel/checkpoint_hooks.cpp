#include "types.h"

// The unload and load hooks and the factory rel/checkpoint_register.cpp puts
// in the checkpoint's editor record, in the thirteen stage modules that share
// it.
//
// The load reads the checkpoint's five models: the star (keeping the first
// material of each of its first two atomics' geometries), the post, its effect
// (keeping the materials of the three bonus textures), the checkpoint light
// (keeping the blue light's material) and the star effect (keeping its first
// material). Each material is looked up only when its model was read. The
// unload forgets all of it; the stage resource manager owns the models. The
// factory allocates 0x7C bytes and hands them to the module's constructor
// (left as assembly and named checkpointCtor here).

typedef struct RpClump RpClump;
typedef struct RpMaterial RpMaterial;
typedef struct RpAtomic RpAtomic;

struct CheckpointGeometry {
	u8 pad00[0x20];
	RpMaterial** materials; // 0x20
};

struct CheckpointAtomic {
	u8 pad00[0x18];
	CheckpointGeometry* geometry; // 0x18
};

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" char checkpointStarName[];
extern "C" char checkpointModelName[];
extern "C" char checkpointEffectName[];
extern "C" char checkpointBonusTexture1[];
extern "C" char checkpointBonusTexture2[];
extern "C" char checkpointBonusTexture3[];
extern "C" char checkpointLightName[];
extern "C" char checkpointLightTexture[];
extern "C" char checkpointStarEffectName[];
extern "C" RpClump* checkpointStar;
extern "C" RpMaterial* checkpointStarMaterials[2];
extern "C" RpClump* checkpointModel;
extern "C" RpClump* checkpointEffect;
extern "C" RpMaterial* checkpointEffectMaterials[3];
extern "C" RpClump* checkpointLight;
extern "C" RpMaterial* checkpointLightMaterial;
extern "C" RpClump* checkpointStarEffect;
extern "C" RpMaterial* checkpointStarEffectMaterial;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* checkpointCtor(void* object, void* owner);
RpClump* objPointerReadFromClumpAnim(char* name);
RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* atomic);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* material, char* name);

extern "C" void checkpointUnload(void)
{
	checkpointStar               = NULL;
	checkpointStarMaterials[0]   = NULL;
	checkpointStarMaterials[1]   = NULL;
	checkpointModel              = NULL;
	checkpointEffect             = NULL;
	checkpointEffectMaterials[0] = NULL;
	checkpointEffectMaterials[1] = NULL;
	checkpointEffectMaterials[2] = NULL;
	checkpointLight              = NULL;
	checkpointLightMaterial      = NULL;
	checkpointStarEffect         = NULL;
	checkpointStarEffectMaterial = NULL;
}

extern "C" void checkpointLoad(void)
{
	checkpointStar = objPointerReadFromClumpAnim(checkpointStarName);
	if (checkpointStar != NULL) {
		CheckpointAtomic* first = (CheckpointAtomic*)objRpClumpGetAtomic(checkpointStar, NULL);
		CheckpointGeometry* geometry
		    = ((CheckpointAtomic*)objRpClumpGetAtomic(checkpointStar, (RpAtomic*)first))->geometry;
		checkpointStarMaterials[0] = first->geometry->materials[0];
		checkpointStarMaterials[1] = geometry->materials[0];
	}
	checkpointModel  = objPointerReadFromClumpAnim(checkpointModelName);
	checkpointEffect = objPointerReadFromClumpAnim(checkpointEffectName);
	if (checkpointEffect != NULL) {
		checkpointEffectMaterials[0] = objRpClumpGetMaterialWithSpecificTexture(
		    checkpointEffect, NULL, checkpointBonusTexture1);
		checkpointEffectMaterials[1] = objRpClumpGetMaterialWithSpecificTexture(
		    checkpointEffect, NULL, checkpointBonusTexture2);
		checkpointEffectMaterials[2] = objRpClumpGetMaterialWithSpecificTexture(
		    checkpointEffect, NULL, checkpointBonusTexture3);
	}
	checkpointLight = objPointerReadFromClumpAnim(checkpointLightName);
	if (checkpointLight != NULL) {
		checkpointLightMaterial = objRpClumpGetMaterialWithSpecificTexture(
		    checkpointLight, NULL, checkpointLightTexture);
	}
	checkpointStarEffect = objPointerReadFromClumpAnim(checkpointStarEffectName);
	if (checkpointStarEffect != NULL) {
		checkpointStarEffectMaterial
		    = objRpClumpGetMaterialWithSpecificTexture(checkpointStarEffect, NULL, NULL);
	}
}

extern "C" void checkpointCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x7C);

	if (memory != NULL) {
		checkpointCtor(memory, lbl_8042C110);
	}
}
