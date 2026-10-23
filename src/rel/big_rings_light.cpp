#include "types.h"

// TObjBigrings::SetRingLight (the PS2 build's name, by its place in the PS2
// order; bigRingsSetRingLight here): each of the three rings gets the
// placement's lights, and its first atomic's custom render data is set to
// 0x10.

typedef struct RpClump RpClump;
typedef struct RpAtomic RpAtomic;

typedef struct BigRingsElement {
	u8 unk00[0x28];
	RpClump* clump; // 0x28
	u8 unk2C[0x8];
} BigRingsElement; // 0x34

typedef struct BigRingsFrame {
	u8 unk00[0x18];
	u32 flags; // 0x18
} BigRingsFrame;

typedef struct BigRings {
	u8 unk00[0x28];
	BigRingsFrame* frame;   // 0x28, the set object's
	u8 unk2C[0x3C];         // 0x2C
	BigRingsElement* rings; // 0x68
} BigRings;

void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump* clump, u32 lights);
RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* after);
extern "C" void* RpAtomicMCCGetCustomRenderCallBack(RpAtomic* atomic);

extern "C" void bigRingsSetRingLight(BigRings* object)
{
	if (object->rings != NULL) {
		for (int i = 0; i < 3; i++) {
			objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
			    object->rings[i].clump, ((object->frame->flags & 0x1C0000) >> 18) + 4);
			*(s32*)RpAtomicMCCGetCustomRenderCallBack(
			    objRpClumpGetAtomic(object->rings[i].clump, NULL)) = 0x10;
		}
	}
}
