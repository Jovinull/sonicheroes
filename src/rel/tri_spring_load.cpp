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
extern "C" void* AtomicSetCustomFXTexture__FP8RpAtomicPv(void* handle, void** slot);
extern "C" void* objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(
    void* model, s32 index, const char* name);
extern "C" TriSpringPart* objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(
    void* model, TriSpringPart* current);
extern "C" void* objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
    void* model, s32 index, const char* name);
extern "C" void* objPointerReadFromClumpAnim__FPc(const char* name);

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
		triSpringModels[i] = objPointerReadFromClumpAnim__FPc(triSpringModelNames[i]);
		if (triSpringModels[i] == NULL) {
			continue;
		}

		triSpringDraws[i] = objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(
		    triSpringModels[i], 0, triSpringNodeName);
		triSpringMaterials[i] = objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
		    triSpringModels[i], 0, triSpringNodeName);

		if (triSpringDraws[i] != NULL) {
			TriSpringPart* part = NULL;

			while ((part = objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(triSpringModels[i], part))
			    != NULL) {
				if (triSpringDraws[i] != part) {
					part->data->flags &= ~8;
				}
			}
			continue;
		}

		fn_8003C640(triSpringModels[i]);

		TriSpringPart* part = NULL;
		while (
		    (part = objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(triSpringModels[i], part)) != NULL) {
			part->data->flags |= 0x20;
		}

		if (triSpringModels[i] != NULL) {
			triSpringEffectMaterial
			    = objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
			        triSpringModels[i], 0, triSpringEffectNodeName);
		}

		triSpringEffect = objPointerReadFromClumpAnim__FPc(triSpringEffectName);
		if (triSpringEffect != NULL && triSpringEffectMaterial != NULL) {
			triSpringUvAnim = triSpringEffect;
			AtomicSetCustomFXTexture__FP8RpAtomicPv(
			    objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(
			        triSpringModels[i], 0, triSpringEffectNodeName),
			    &triSpringUvAnim);
		}
	}
}
