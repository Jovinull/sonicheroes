#include "types.h"

// The hint ring's render callback (a local callbackSetMaterial in the PS2
// build; hintringLightRender here, named after the ring as
// rel/push_pull_switch_light_render.cpp names the switch's): the atomic's
// material takes the atomic's colour and the atomic is drawn by its original
// callback with the world's lights ignored.

typedef struct RpWorld RpWorld;

typedef struct RwRGBA {
	u8 red, green, blue, alpha;
} RwRGBA;

typedef struct RpMaterial {
	u8 unk0[0x4];
	RwRGBA color; // 0x04
} RpMaterial;

struct RpAtomic {
	u8 unk00[0x48];
	RpAtomic* (*renderCallBack)(RpAtomic* atomic); // 0x48
};

class CLIGHT
{
public:
	void StartIgnoreLight(RpWorld* world);
	void EndIgnoreLight(RpWorld* world);
};

typedef struct World {
	u8 unk0[0x725C]; // 0x0000
	RpWorld* scene;  // 0x725C
} World;

extern "C" CLIGHT lbl_802D5E80;
extern "C" World* lbl_8042C1D0;
extern "C" RpAtomic* hintringObjectAtomic;

extern "C" RpMaterial* RpAtomicMCCGetMaterialPointer(RpAtomic* atomic);
extern "C" RwRGBA* RpAtomicMCCGetColor(RpAtomic* atomic);

extern "C" RpAtomic* hintringLightRender(RpAtomic* atomic)
{
	RpMaterial* material = RpAtomicMCCGetMaterialPointer(atomic);

	material->color = *RpAtomicMCCGetColor(atomic);
	lbl_802D5E80.StartIgnoreLight(lbl_8042C1D0->scene);
	hintringObjectAtomic->renderCallBack(atomic);
	lbl_802D5E80.EndIgnoreLight(lbl_8042C1D0->scene);
	return atomic;
}
