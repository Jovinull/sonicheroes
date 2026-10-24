#include "types.h"

// callbackSetMaterial (a local function in the PS2 build): the form gate's
// atomic render callback. The atomic's material is tinted by the gate's
// formation (speed blue, flight yellow, power red), the geometry modulating
// it, and the atomic is drawn by the default callback ignoring the stage's
// lights.

typedef struct RwRGBA {
	u8 red, green, blue, alpha;
} RwRGBA;

typedef struct FormgateMaterial {
	u8 unk0[0x4];
	RwRGBA color; // 0x4
} FormgateMaterial;

typedef struct FormgateGeometry {
	u8 unk0[0x8];
	u32 flags; // 0x8
} FormgateGeometry;

struct RpAtomic {
	u8 unk00[0x18];
	FormgateGeometry* geometry; // 0x18
};

struct RpWorld;

typedef struct FormgateRender {
	u8 unk00[0x48];
	RpAtomic* (*callback)(RpAtomic* atomic); // 0x48
} FormgateRender;

typedef struct FormgateScene {
	u8 unk0000[0x725C];
	RpWorld* world; // 0x725C
} FormgateScene;

class CLIGHT
{
public:
	void StartIgnoreLight(RpWorld* world);
	void EndIgnoreLight(RpWorld* world);
};

extern "C" CLIGHT lbl_802D5E80;
extern "C" FormgateScene* lbl_8042C1D0;
extern "C" FormgateRender* formgateDefaultRender;

extern "C" FormgateMaterial* RpAtomicMCCGetMaterialPointer(RpAtomic* atomic);
extern "C" s32* RpAtomicMCCGetUsrData(RpAtomic* atomic);

RpAtomic* callbackSetMaterial(RpAtomic* atomic)
{
	u8 red, green, blue, alpha;

	atomic->geometry->flags |= 0x40;
	FormgateMaterial* material = RpAtomicMCCGetMaterialPointer(atomic);
	switch (*RpAtomicMCCGetUsrData(atomic)) {
		case 0:
			red   = 0x00;
			green = 0x5A;
			blue  = 0xAA;
			alpha = 0xC0;
			break;
		case 1:
			red   = 0xFA;
			green = 0xA5;
			blue  = 0x19;
			alpha = 0xC0;
			break;
		case 2:
		default:
			red   = 0xF0;
			green = 0x19;
			blue  = 0x3C;
			alpha = 0xC0;
			break;
	}
	material->color.red   = red;
	material->color.green = green;
	material->color.blue  = blue;
	material->color.alpha = alpha;
	lbl_802D5E80.StartIgnoreLight(lbl_8042C1D0->world);
	formgateDefaultRender->callback(atomic);
	lbl_802D5E80.EndIgnoreLight(lbl_8042C1D0->world);
	return atomic;
}
