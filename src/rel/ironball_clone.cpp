#include "types.h"

// TObjIronball::CloneClump (the PS2 build's name; ironballCloneClump here), the
// out-of-line copy nothing calls (the constructor has its own), the same in the
// thirteen stage modules that share the engine core: a kind-1 ball
// clones the single model; any other clones the ball, the two chain links and
// the two hooks. Each clone takes the light the placement's flags pick (bits
// 18-20, after the four the stage keeps) and goes into the world.

typedef struct RpClump RpClump;

typedef struct World {
	u8 unk0[0x725C];
	void* scene; // 0x725C
} World;

typedef struct SetData {
	u8 unk0[0x18];
	u32 flags; // 0x18
} SetData;

typedef struct Ironball {
	u8 unk00[0x28];
	SetData* setdata; // 0x28
	u8 unk2C[0x8C];
	s32 kind; // 0xB8
	u8 unkBC[0x24];
	RpClump* models[5]; // 0xE0
} Ironball;

extern "C" void* ironballModels[4];
extern "C" World* lbl_8042C1D0;

extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* scene, RpClump* clump);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump* clump, u32 light);

extern "C" void ironballCloneClump(Ironball* object)
{
	if (object->kind == 1) {
		object->models[0] = fn_80150588(ironballModels[0]);
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
		    object->models[0], ((object->setdata->flags & 0x1C0000) >> 18) + 4);
		fn_8015BB08(lbl_8042C1D0->scene, object->models[0]);
		object->models[1] = NULL;
		object->models[2] = NULL;
		object->models[3] = NULL;
		object->models[4] = NULL;
	} else {
		s32 i;

		object->models[0] = fn_80150588(ironballModels[1]);
		object->models[1] = fn_80150588(ironballModels[2]);
		object->models[2] = fn_80150588(ironballModels[2]);
		object->models[3] = fn_80150588(ironballModels[3]);
		object->models[4] = fn_80150588(ironballModels[3]);
		for (i = 0; i < 5; i++) {
			objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
			    object->models[i], ((object->setdata->flags & 0x1C0000) >> 18) + 4);
			fn_8015BB08(lbl_8042C1D0->scene, object->models[i]);
		}
	}
}
