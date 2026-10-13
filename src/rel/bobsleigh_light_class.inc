#include "game/effect/eff_bomb.h"
#include "game/material.h"

// TObjBobsleighLight (the PS2 build's class): the lights along the bobsleigh
// course, one main model and eight others, each with a DealMaterial to tint it.
// DestroyClump and CloneClump are inline here and also have out-of-line copies
// (rel/bobsleigh_light_destroy.cpp, rel/bobsleigh_light_clone.cpp).

class TObjBobsleighLight : public TObject
{
public:
	u8 pad28[0xC];
	f32 alpha;                   // 0x34
	f32 shade;                   // 0x38
	s32 unk3C;                   // 0x3C
	RpClump* clump;              // 0x40
	RpClump* clumps[8];          // 0x44
	DealMaterial* material;      // 0x64
	DealMaterial* materials[8];  // 0x68
	s32 lit[8];                  // 0x88

	TObjBobsleighLight(TObject* parent, RpClump* model);
	// Exec comes first so that it is the key function: no unit of ours emits
	// the vtable, which stays in each module's data.
	virtual void Exec();
	virtual void TDisp();
	virtual ~TObjBobsleighLight();
	void DestroyClump();
	void CloneClump(RpClump* model);
};

extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_80150958(RpClump* clump);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump* clump, u32 light);

#ifndef BOBSLEIGH_LIGHT_DESTROY_INLINE
#define BOBSLEIGH_LIGHT_DESTROY_INLINE inline
#endif

// Frees every model and its material.
BOBSLEIGH_LIGHT_DESTROY_INLINE void TObjBobsleighLight::DestroyClump()
{
	if (material != NULL) {
		delete material;
		material = NULL;
	}
	if (clump != NULL) {
		fn_80150958(clump);
		clump = NULL;
	}
	for (int i = 0; i < 8; i++) {
		if (materials[i] != NULL) {
			delete materials[i];
			materials[i] = NULL;
		}
		if (clumps[i] != NULL) {
			fn_80150958(clumps[i]);
			clumps[i] = NULL;
		}
	}
}

#ifndef BOBSLEIGH_LIGHT_CLONE_INLINE
#define BOBSLEIGH_LIGHT_CLONE_INLINE inline
#endif

// Makes the models it lacks from the given one, lit with set 0x10, each with a
// DealMaterial over it.
BOBSLEIGH_LIGHT_CLONE_INLINE void TObjBobsleighLight::CloneClump(RpClump* model)
{
	if (model != NULL) {
		if (clump == NULL) {
			clump = fn_80150588(model);
			objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clump, 0x10);
			material = new DealMaterial(clump);
		}
		for (int i = 0; i < 8; i++) {
			if (clumps[i] == NULL) {
				clumps[i] = fn_80150588(model);
				objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clumps[i], 0x10);
				materials[i] = new DealMaterial(clumps[i]);
			}
		}
	}
}
