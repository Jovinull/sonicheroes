#include "types.h"

// The ring object's unload and load hooks (endObjRing and initObjRing in the
// PS2 build, local there; ringObjectUnload and ringObjectLoad here). The load
// reads the ring models (OBJ_RING.DFF and OBJ_RINGL.DFF), loads the sparkle
// effect's textures and, unless another module did, installs
// ObjRingScattering (the rings a player loses) in the first slot of the hook
// block at lbl_8042B338; the unload clears the hook, releases the sparkle
// textures and forgets the models.

struct RwV3d;
struct sRealAngle3;

// The hook block at lbl_8042B338 (rel/lens_flare_load.cpp uses the second
// slot).
struct ObjectHooks {
	void (*ringScattering)(u32, RwV3d*, sRealAngle3*, f32, f32); // 0x00
	void* createEfLens;                                          // 0x04
};

extern "C" ObjectHooks lbl_8042B338;
extern "C" void* ringModel;
extern "C" void* ringLargeModel;
extern "C" char ringModelName[];
extern "C" char ringLargeModelName[];

void* objPointerReadFromClumpAnim(char* name);
void ReleaseTextureEfSparkle();
void LoadTextureEfSparkle();
void ObjRingScattering(u32 count, RwV3d* pos, sRealAngle3* ang, f32 speed, f32 spread);

extern "C" void ringObjectUnload(void)
{
	lbl_8042B338.ringScattering = NULL;
	ReleaseTextureEfSparkle();
	ringModel      = NULL;
	ringLargeModel = NULL;
}

extern "C" void ringObjectLoad(void)
{
	ringModel      = objPointerReadFromClumpAnim(ringModelName);
	ringLargeModel = objPointerReadFromClumpAnim(ringLargeModelName);
	LoadTextureEfSparkle();
	if (lbl_8042B338.ringScattering == NULL) {
		lbl_8042B338.ringScattering = ObjRingScattering;
	}
}
