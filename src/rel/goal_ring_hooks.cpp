#include "types.h"

// The goal ring's unload and load hooks (goalRingUnload and goalRingLoad
// here). The load reads the four models (OBJ_GOALRING.DFF, OBJ_BACKRING.DFF,
// OBJ_BACKRING_B.DFF and the star effect, OBJ_STAR.DFF), takes the effect
// model's first two materials and loads the sparkle effect's textures; the
// unload releases the sparkle textures and forgets the models and materials.

typedef struct RpClump RpClump;
typedef struct RpMaterial RpMaterial;

extern "C" RpClump* goalRingModel;
extern "C" RpClump* goalRingModel2;
extern "C" RpClump* goalRingBackModel;
extern "C" RpClump* goalRingEffectModel;
extern "C" RpMaterial* goalRingEffectMaterials[2];
extern "C" char goalRingModelName[];
extern "C" char goalRingModel2Name[];
extern "C" char goalRingBackModelName[];
extern "C" char goalRingEffectModelName[];

RpClump* objPointerReadFromClumpAnim(char* name);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* after, char* texture);
void ReleaseTextureEfSparkle();
void LoadTextureEfSparkle();

extern "C" void goalRingUnload(void)
{
	ReleaseTextureEfSparkle();
	goalRingModel              = NULL;
	goalRingModel2             = NULL;
	goalRingBackModel          = NULL;
	goalRingEffectModel        = NULL;
	goalRingEffectMaterials[0] = NULL;
	goalRingEffectMaterials[1] = NULL;
}

extern "C" void goalRingLoad(void)
{
	goalRingModel     = objPointerReadFromClumpAnim(goalRingModelName);
	goalRingModel2    = objPointerReadFromClumpAnim(goalRingModel2Name);
	goalRingBackModel = objPointerReadFromClumpAnim(goalRingBackModelName);
	if ((goalRingEffectModel = objPointerReadFromClumpAnim(goalRingEffectModelName)) != NULL) {
		goalRingEffectMaterials[0]
		    = objRpClumpGetMaterialWithSpecificTexture(goalRingEffectModel, NULL, NULL);
		goalRingEffectMaterials[1] = objRpClumpGetMaterialWithSpecificTexture(
		    goalRingEffectModel, goalRingEffectMaterials[0], NULL);
	}
	LoadTextureEfSparkle();
}
