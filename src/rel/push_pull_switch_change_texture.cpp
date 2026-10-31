#include "types.h"

// TObjSwitchPushPull::ChangeTextureForLightPart
// (pushPullSwitchChangeTextureForLightPart here), the out-of-line copy nothing
// calls: it sets the given material on both of the switch's light parts. The
// material is held as a word before the loop, which keeps it in r30 and the
// index in r29 as the original has them.

typedef struct RpAtomic RpAtomic;

typedef struct PushPullSwitch {
	u8 unk00[0xF0];
	RpAtomic* lightParts[2]; // 0xF0
} PushPullSwitch;

extern "C" void RpAtomicMCCSetMaterialPointer(RpAtomic* atomic, void* material);

extern "C" void pushPullSwitchChangeTextureForLightPart(PushPullSwitch* object, void* material)
{
	u32 texture = (u32)material;
	s32 i;

	for (i = 0; i < 2; i++) {
		RpAtomicMCCSetMaterialPointer(object->lightParts[i], (void*)texture);
	}
}
