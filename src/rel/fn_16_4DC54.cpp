#include "types.h"

struct RpClump;
struct RpAtomic;

extern "C" RpAtomic* objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(
    RpClump* clump, RpAtomic* skip, char* name);

extern "C" s32 fn_16_4DC54(RpClump* clump, register RpAtomic** table, char* name)
{
	RpAtomic* atomic;
	s32 i;

	atomic = objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(clump, 0, name);
	for (i = 0; table[i] != 0; i++) {
		if (atomic == table[i]) {
			return i;
		}
	}
	return -1;
}
