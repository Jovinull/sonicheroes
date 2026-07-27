#include "types.h"

// TObj3Spring's asset loader. Each of the four variants gets its model, named
// part and material. If the named part exists, bit 0x08 is cleared on every
// other part; otherwise every part gets bit 0x20 and the fallback UV animation
// is connected to the model.
//
// The claim is .text 0x2D20 to 0x2ED4. The code is identical in the thirteen
// stage modules that share the engine core; stage40D is a different revision.

typedef struct TriSpringPartData {
	u8 unk0[8];
	u32 flags;
} TriSpringPartData;

typedef struct TriSpringPart {
	u8 unk0[0x18];
	TriSpringPartData* data;
} TriSpringPart;

extern "C" void fn_8003C640(void* model);
extern "C" void* fn_8005C014(void* handle, void** slot);
extern "C" void* fn_8005E1DC(void* model, s32 index, const char* name);
extern "C" TriSpringPart* fn_8005E394(void* model, TriSpringPart* current);
extern "C" void* fn_8005E410(void* model, s32 index, const char* name);
extern "C" void* fn_8005EA04(const char* name);

extern "C" void* triSpringModels[4];
extern "C" void* triSpringDraws[4];
extern "C" void* triSpringMaterials[4];
extern "C" const char* triSpringModelNames[4];
extern "C" char triSpringNodeName[];
extern "C" char triSpringEffectNodeName[];
extern "C" char triSpringEffectName[];
extern "C" void* triSpringUvAnim;
extern "C" void* triSpringEffectMaterial;
extern "C" void* triSpringEffect;

extern "C" void triSpringLoad(void)
{
	for (s32 i = 0; i < 4; i++) {
		triSpringModels[i] = fn_8005EA04(triSpringModelNames[i]);
		if (triSpringModels[i] == NULL) {
			continue;
		}

		triSpringDraws[i]     = fn_8005E1DC(triSpringModels[i], 0, triSpringNodeName);
		triSpringMaterials[i] = fn_8005E410(triSpringModels[i], 0, triSpringNodeName);

		if (triSpringDraws[i] != NULL) {
			TriSpringPart* part = NULL;

			while ((part = fn_8005E394(triSpringModels[i], part)) != NULL) {
				if (triSpringDraws[i] != part) {
					part->data->flags &= ~8;
				}
			}
			continue;
		}

		fn_8003C640(triSpringModels[i]);

		TriSpringPart* part = NULL;
		while ((part = fn_8005E394(triSpringModels[i], part)) != NULL) {
			part->data->flags |= 0x20;
		}

		if (triSpringModels[i] != NULL) {
			triSpringEffectMaterial = fn_8005E410(triSpringModels[i], 0, triSpringEffectNodeName);
		}

		triSpringEffect = fn_8005EA04(triSpringEffectName);
		if (triSpringEffect != NULL && triSpringEffectMaterial != NULL) {
			triSpringUvAnim = triSpringEffect;
			fn_8005C014(
			    fn_8005E1DC(triSpringModels[i], 0, triSpringEffectNodeName), &triSpringUvAnim);
		}
	}
}
