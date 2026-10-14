#include "types.h"

// TEnemyGadgetBomber's destructor and constructor (the PS2 build's names):
// torn down, the bomber destroys its clumps (DestroyClump, inline; then the
// TEnemyGadget destructor inline, as the retail has it); built, it starts with
// the bomb at its smallest, a drop height of 5, and clones its clumps
// (CloneClump, inline).

#include "src/rel/gadget_bomber.inc"

extern "C" void* lbl_8042C148;
extern "C" void* __vt__18TEnemyGadgetBomber[];
extern "C" void* __vt__12TEnemyGadget[];
extern "C" char* gadgetBomberClassName;
extern "C" const f32 gadgetBombScaleXZ;
extern "C" const f32 bomberDropHeight;

extern "C" void __ct__12TEnemyGadgetFP9TObjEnemy(GadgetBomber* gadget, void* owner);
extern "C" void __dt__7TObjectFv(GadgetBomber* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, GadgetBomber* object);

extern "C" GadgetBomber* __dt__18TEnemyGadgetBomberFv(GadgetBomber* gadget, s16 flags)
{
	if (gadget != NULL) {
		gadget->vtable = __vt__18TEnemyGadgetBomber;
		DestroyClump__18TEnemyGadgetBomberFv(gadget);
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

extern "C" GadgetBomber* __ct__18TEnemyGadgetBomberFP17TObjEnemySearcher(
    GadgetBomber* gadget, void* owner)
{
	__ct__12TEnemyGadgetFP9TObjEnemy(gadget, owner);
	gadget->vtable     = __vt__18TEnemyGadgetBomber;
	gadget->name       = gadgetBomberClassName;
	gadget->size       = sizeof(GadgetBomber);
	gadget->enemy      = owner;
	gadget->field3C    = 0;
	gadget->bombScale  = gadgetBombScaleXZ;
	gadget->field4C    = 0;
	gadget->dropHeight = bomberDropHeight;
	gadget->motion     = NULL;
	gadget->bomb       = NULL;
	CloneClump__18TEnemyGadgetBomberFv(gadget);
	return gadget;
}
