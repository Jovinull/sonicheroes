#include "types.h"

// TEnemyGadgetNeedle's destructor and constructor (the PS2 build's names):
// the gadget clones its needles from the static model when built (at their
// smallest) and destroys them when torn down (the TEnemyGadget destructor
// inline, as the retail has it).

typedef struct RpClump RpClump;

typedef struct GadgetNeedle {
	char* name; // 0x00
	u8 unk04[0x14];
	void** vtable; // 0x18
	u8 unk1C[0x2];
	u16 size; // 0x1E
	u8 unk20[0x18];
	void* enemy;      // 0x38
	f32 growth;       // 0x3C
	RpClump* needles; // 0x40
} GadgetNeedle;

extern "C" void* lbl_8042C148;
extern "C" void* __vt__18TEnemyGadgetNeedle[];
extern "C" void* __vt__12TEnemyGadget[];
extern "C" char* gadgetNeedleClassName;
extern "C" const f32 gadgetBombScaleXZ;
extern "C" RpClump* needleFxClump;

extern "C" void __ct__12TEnemyGadgetFP9TObjEnemy(GadgetNeedle* gadget, void* owner);
extern "C" void __dt__7TObjectFv(GadgetNeedle* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, GadgetNeedle* object);
extern "C" void fn_80150958(RpClump* clump);
extern "C" RpClump* fn_80150588(RpClump* clump);

extern "C" GadgetNeedle* __dt__18TEnemyGadgetNeedleFv(GadgetNeedle* gadget, s16 flags)
{
	if (gadget != NULL) {
		gadget->vtable = __vt__18TEnemyGadgetNeedle;
		if (gadget->needles != NULL) {
			fn_80150958(gadget->needles);
			gadget->needles = NULL;
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

extern "C" GadgetNeedle* __ct__18TEnemyGadgetNeedleFP17TObjEnemySearcher(
    GadgetNeedle* gadget, void* owner)
{
	__ct__12TEnemyGadgetFP9TObjEnemy(gadget, owner);
	gadget->vtable  = __vt__18TEnemyGadgetNeedle;
	gadget->name    = gadgetNeedleClassName;
	gadget->size    = sizeof(GadgetNeedle);
	gadget->enemy   = owner;
	gadget->growth  = gadgetBombScaleXZ;
	gadget->needles = NULL;
	if (needleFxClump != NULL) {
		gadget->needles = fn_80150588(needleFxClump);
	}
	return gadget;
}
