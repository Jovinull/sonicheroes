#include "types.h"

// TEnemyGadgetShot's destructor (the PS2 build's name): the gadget cancels its
// shot (its Cancel, virtually; the TEnemyGadget destructor inline, as the
// retail has it). The constructor stays in assembly, like TEnemyGadgetMGun's
// (rel/gadget_mgun_cdtor.cpp).

#include "src/rel/searcher.inc"

typedef struct GadgetShot {
	char* name; // 0x00
	u8 unk04[0x14];
	void** vtable; // 0x18
	u8 unk1C[0x2];
	u16 size; // 0x1E
	u8 unk20[0x10];
	s32 gmode; // 0x30
	u8 unk34[0xC];
	s32 pitch; // 0x40
	s32 shot;  // 0x44
} GadgetShot;

extern "C" void* __vt__16TEnemyGadgetShot[];
extern "C" void* __vt__12TEnemyGadget[];

extern "C" void __dt__7TObjectFv(GadgetShot* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(THeapCtrl* heap, GadgetShot* object);

extern "C" GadgetShot* __dt__16TEnemyGadgetShotFv(GadgetShot* gadget, s16 flags)
{
	if (gadget != NULL) {
		gadget->vtable = __vt__16TEnemyGadgetShot;
		((TEnemyGadget*)gadget)->Cancel();
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
