#include "types.h"

// The target's TDisp and Disp (targetTDisp and targetDisp here). With the game
// not paused and the target out (not in state 0 or 1), TDisp draws it while it
// fades (its fade below 1), with the fade as alpha and render states 0xA, 0xB
// and 0x14 set to 5, 2 and 1 (put back after); Disp draws it opaque once the
// fade is exactly 1. Both light it by the placement's light bits.

typedef struct RpClump RpClump;
typedef struct RpAtomic RpAtomic;

typedef struct TargetPlacement {
	u8 unk00[0x18];
	u32 flag; // 0x18
} TargetPlacement;

typedef struct Target {
	u8 unk00[0x28];
	TargetPlacement* placement; // 0x28
	u8 unk2C[0x8C];
	s32 state; // 0xB8
	u8 unkBC[0x2C];
	f32 fade;       // 0xE8
	RpClump* clump; // 0xEC
} Target;

class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 regular; // 0x4BE

	void SetCurrentNum(s8 num);
	void SetLightRegular(s8 num);
};

extern "C" u8* lbl_8042C180;
extern "C" CLIGHT lbl_802D5E80;
extern "C" const f32 targetOne[1];
extern "C" const f32 targetAlphaScale[1];

extern "C" RpAtomic* cannonSmokeBind(RpAtomic* atomic, void* data);
extern "C" void fn_8014FF2C(RpClump* clump);
extern "C" void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
extern "C" void fn_80194294(s32 state, void* value);
extern "C" void fn_80194234(s32 state, s32 value);

extern "C" void targetTDisp(Target* object)
{
	if ((s8)lbl_8042C180[0x20] == 0 && object->fade < targetOne[0] && object->clump != NULL
	    && object->state != 0 && object->state != 1) {
		u8 alpha = targetAlphaScale[0] * object->fade;
		s32 src;
		s32 dst;
		s32 cull;

		fn_8014FFBC(object->clump, cannonSmokeBind, &alpha);
		lbl_802D5E80.SetCurrentNum(((object->placement->flag & 0x1C0000) >> 18) + 4);
		lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
		fn_80194294(0xA, &src);
		fn_80194294(0xB, &dst);
		fn_80194294(0x14, &cull);
		fn_80194234(0xA, 5);
		fn_80194234(0xB, 2);
		fn_80194234(0x14, 1);
		fn_8014FF2C(object->clump);
		fn_80194234(0x14, cull);
		fn_80194234(0xA, src);
		fn_80194234(0xB, dst);
	}
}

extern "C" void targetDisp(Target* object)
{
	if ((s8)lbl_8042C180[0x20] == 0 && targetOne[0] == object->fade && object->clump != NULL
	    && object->state != 0 && object->state != 1) {
		u8 alpha = 0xFF;

		fn_8014FFBC(object->clump, cannonSmokeBind, &alpha);
		lbl_802D5E80.SetCurrentNum(((object->placement->flag & 0x1C0000) >> 18) + 4);
		lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
		fn_8014FF2C(object->clump);
	}
}
