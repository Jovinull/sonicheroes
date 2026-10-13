#include "types.h"

// The bobsleigh's unload and load hooks (bobsleighObjectUnload and
// bobsleighObjectLoad here; the names are ours). The load reads the sled, the
// launcher (keeping its material for the obj_dsh3 texture when there is one)
// and the launcher's UV animation, then sets up the signals and lights
// (initObjBobsleigh_Sub); the unload forgets them and ends that set-up.

typedef struct RpClump RpClump;
typedef struct RpMaterial RpMaterial;

extern "C" char bobsleighModelName[];
extern "C" char bobsleighLauncherModelName[];
extern "C" char bobsleighLauncherTexture[];
extern "C" char bobsleighLauncherUvAnimName[];
extern "C" RpClump* bobsleighModel;
extern "C" RpClump* bobsleighLauncherModel;
extern "C" RpMaterial* bobsleighLauncherMaterial;
extern "C" RpClump* bobsleighLauncherUvAnim;

RpClump* objPointerReadFromClumpAnim(char* name);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* material, char* name);
void endObjBobsleigh_Sub();
void initObjBobsleigh_Sub();

extern "C" void bobsleighObjectUnload(void)
{
	bobsleighModel            = NULL;
	bobsleighLauncherModel    = NULL;
	bobsleighLauncherMaterial = NULL;
	bobsleighLauncherUvAnim   = NULL;
	endObjBobsleigh_Sub();
}

extern "C" void bobsleighObjectLoad(void)
{
	bobsleighModel         = objPointerReadFromClumpAnim(bobsleighModelName);
	bobsleighLauncherModel = objPointerReadFromClumpAnim(bobsleighLauncherModelName);
	if (bobsleighLauncherModel != NULL) {
		bobsleighLauncherMaterial = objRpClumpGetMaterialWithSpecificTexture(
		    bobsleighLauncherModel, NULL, bobsleighLauncherTexture);
	}
	bobsleighLauncherUvAnim = objPointerReadFromClumpAnim(bobsleighLauncherUvAnimName);
	initObjBobsleigh_Sub();
}
