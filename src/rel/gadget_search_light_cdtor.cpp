#include "game/enemy/e_database.h"

// TEnemyGadgetSearchLight::SetClump, its destructor and constructor (the PS2
// build's names): the search light keeps the clump it is given; it clones its
// lamp model (0x18 of the searcher files) when built and destroys it when torn
// down (the TEnemyGadget destructor inline, as the retail has it).

typedef struct GadgetSearchLight {
	char* name; // 0x00
	u8 unk04[0x14];
	void** vtable; // 0x18
	u8 unk1C[0x2];
	u16 size; // 0x1E
	u8 unk20[0xC];
	RpClump* pClump; // 0x2C
	u8 unk30[0x8];
	void* enemy; // 0x38
	s32 field3C; // 0x3C
	u8 unk40[0xC];
	RpClump* lamp; // 0x4C
} GadgetSearchLight;

extern "C" void* lbl_8042C148;
extern "C" void* __vt__23TEnemyGadgetSearchLight[];
extern "C" void* __vt__12TEnemyGadget[];
extern "C" char* gadgetSearchLightClassName;

extern "C" void __ct__12TEnemyGadgetFP9TObjEnemy(GadgetSearchLight* gadget, void* owner);
extern "C" void __dt__7TObjectFv(GadgetSearchLight* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, GadgetSearchLight* object);
extern "C" void fn_80150958(RpClump* clump);
extern "C" RpClump* fn_80150588(RpClump* clump);

extern "C" void SetClump__23TEnemyGadgetSearchLightFP7RpClump(
    GadgetSearchLight* gadget, RpClump* clump)
{
	gadget->pClump = clump;
}

extern "C" GadgetSearchLight* __dt__23TEnemyGadgetSearchLightFv(
    GadgetSearchLight* gadget, s16 flags)
{
	if (gadget != NULL) {
		gadget->vtable = __vt__23TEnemyGadgetSearchLight;
		if (gadget->lamp != NULL) {
			fn_80150958(gadget->lamp);
			gadget->lamp = NULL;
		}
		if (gadget != NULL) {
			gadget->vtable = __vt__12TEnemyGadget;
			__dt__7TObjectFv(gadget, 0);
		}
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, gadget);
		}
	}
	return gadget;
}

extern "C" GadgetSearchLight* __ct__23TEnemyGadgetSearchLightFP17TObjEnemySearcher(
    GadgetSearchLight* gadget, void* owner)
{
	RpClump* lamp;

	__ct__12TEnemyGadgetFP9TObjEnemy(gadget, owner);
	gadget->vtable  = __vt__23TEnemyGadgetSearchLight;
	gadget->name    = gadgetSearchLightClassName;
	gadget->size    = sizeof(GadgetSearchLight);
	gadget->enemy   = owner;
	gadget->field3C = 0;
	gadget->lamp    = NULL;
	lamp            = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)2, 0x18);
	if (lamp != NULL) {
		gadget->lamp = fn_80150588(lamp);
	}
	return gadget;
}
