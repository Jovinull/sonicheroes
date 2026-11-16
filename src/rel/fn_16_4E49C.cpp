#include "types.h"

struct RpClump {
	u8 data[4];
};
struct SPSTG_CLUMP_INSTANCE {
	s32 num;
	RpClump** pClump;
	s32 world_index;
};
struct SPSTG_UV {
	void* animation;
	char* filename;
	char* material;
};

extern "C" {
void* objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(
    RpClump* clump, void* atomic, char* texture);
void fn_16_4E7C4(void* target, void* atomic);
}

extern "C" void fn_16_4E49C(SPSTG_CLUMP_INSTANCE* inst, SPSTG_UV* uv)
{
	s32 i;
	s32 j;
	void* atomic;

	for (i = 0; uv[i].material != NULL; i++) {
		if (uv[i].animation != NULL) {
			for (j = 0; j < inst->num; j++) {
				atomic = objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(
				    inst->pClump[j], NULL, uv[i].material);
				if (atomic != NULL) {
					fn_16_4E7C4(uv[i].animation, atomic);
				}
			}
		}
	}
}
