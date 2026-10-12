#include "types.h"

// The four hooks rel/flower_register.cpp puts in the flower's editor record, in
// the thirteen stage modules that share it: the empty reset, the unload that
// forgets what the load read, the load, and the factory.
//
// The load reads the flower's models (the closed flower and its animation, the
// open one and the two halves of the other) and the warp effect, keeps the
// warp's blue light material, reads the warp's UV animation into the head of
// its custom FX block and gives that block to the warp's atomic that uses the
// blue light texture. The factory allocates 0x198 bytes and hands them to the
// module's constructor (left as assembly and named flowerObjectCtor here).

typedef struct RpClump RpClump;
typedef struct RpAtomic RpAtomic;
typedef struct RpMaterial RpMaterial;

struct FlowerWarpFX {
	RpClump* uv; // 0x00
	u8 pad04[0x40];
};

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" char flowerObjectModelCName[];
extern "C" char flowerObjectAnimCName[];
extern "C" char flowerObjectModelAName[];
extern "C" char flowerObjectModelBAName[];
extern "C" char flowerObjectModelBBName[];
extern "C" char flowerObjectWarpName[];
extern "C" char flowerObjectWarpTexture[];
extern "C" char flowerObjectWarpUVName[];
extern "C" RpClump* flowerObjectModelC;
extern "C" RpClump* flowerObjectAnimC;
extern "C" RpClump* flowerObjectModelA;
extern "C" RpClump* flowerObjectModelBA;
extern "C" RpClump* flowerObjectModelBB;
extern "C" RpClump* flowerObjectWarp;
extern "C" RpMaterial* flowerObjectWarpMaterial;
extern "C" RpClump* flowerObjectWarpUV;
extern "C" FlowerWarpFX flowerObjectWarpFX;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* flowerObjectCtor(void* object, void* owner);
RpClump* objPointerReadFromClumpAnim(char* name);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* material, char* name);
RpAtomic* objRpClumpGetAtomicWithTexture(RpClump* clump, RpAtomic* atomic, char* name);
void AtomicSetCustomFXTexture(RpAtomic* atomic, void* fx);

extern "C" void flowerObjectReset(void) { }

extern "C" void flowerObjectUnload(void)
{
	flowerObjectModelC       = NULL;
	flowerObjectAnimC        = NULL;
	flowerObjectModelA       = NULL;
	flowerObjectModelBA      = NULL;
	flowerObjectModelBB      = NULL;
	flowerObjectWarp         = NULL;
	flowerObjectWarpMaterial = NULL;
	flowerObjectWarpUV       = NULL;
}

extern "C" void flowerObjectLoad(void)
{
	flowerObjectModelC  = objPointerReadFromClumpAnim(flowerObjectModelCName);
	flowerObjectAnimC   = objPointerReadFromClumpAnim(flowerObjectAnimCName);
	flowerObjectModelA  = objPointerReadFromClumpAnim(flowerObjectModelAName);
	flowerObjectModelBA = objPointerReadFromClumpAnim(flowerObjectModelBAName);
	flowerObjectModelBB = objPointerReadFromClumpAnim(flowerObjectModelBBName);
	flowerObjectWarp    = objPointerReadFromClumpAnim(flowerObjectWarpName);
	flowerObjectWarpMaterial
	    = objRpClumpGetMaterialWithSpecificTexture(flowerObjectWarp, NULL, flowerObjectWarpTexture);
	flowerObjectWarpUV    = objPointerReadFromClumpAnim(flowerObjectWarpUVName);
	flowerObjectWarpFX.uv = flowerObjectWarpUV;
	AtomicSetCustomFXTexture(
	    objRpClumpGetAtomicWithTexture(flowerObjectWarp, NULL, flowerObjectWarpTexture),
	    &flowerObjectWarpFX);
}

extern "C" void flowerObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x198);

	if (memory != NULL) {
		flowerObjectCtor(memory, lbl_8042C110);
	}
}
