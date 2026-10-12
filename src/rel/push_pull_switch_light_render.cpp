#include "types.h"

// The render callback TObjSwitchPushPull's constructor gives the switch's two
// light parts (a file-local callbackSetMaterial in the PS2 build; named here
// for the switch, since several units have one of that name). It copies the
// atomic's material into both light materials, draws with light set 0x10 and
// the regular light, and then renders the atomic with the callback of the
// atomic the stage keeps for the switch.

struct RpAtomic {
	u8 unk00[0x48];
	RpAtomic* (*renderCallBack)(RpAtomic* atomic); // 0x48
};

class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 regular; // 0x4BE

	void SetCurrentNum(s8 num);
	void SetLightRegular(s8 num);
};

extern "C" CLIGHT lbl_802D5E80;
extern "C" void* pushPullSwitchMaterials[2];
extern "C" RpAtomic* pushPullSwitchAtomic;

extern "C" void* RpAtomicMCCGetMaterialPointer(RpAtomic* atomic);
extern "C" void fn_8015498C(void* material, void* source);

extern "C" RpAtomic* pushPullSwitchLightRender(RpAtomic* atomic)
{
	void* material = RpAtomicMCCGetMaterialPointer(atomic);

	for (int i = 0; i < 2; i++) {
		fn_8015498C(pushPullSwitchMaterials[i], material);
	}
	lbl_802D5E80.SetCurrentNum(0x10);
	lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
	pushPullSwitchAtomic->renderCallBack(atomic);
	return atomic;
}
