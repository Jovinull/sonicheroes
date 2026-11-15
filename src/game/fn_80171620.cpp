#include "game/rw_engine.h"

struct Slot80171620 {
	int f0;
	int f4;
	int f8;
	int fc;
	f32 f10;
	int f14;
	Slot80171620* f18;
};

struct Rec80171620 {
	u8 pad[0x1d4];
	RwFreeList* freeList;
};

extern "C" {
extern Rec80171620 lbl_803EC968;
extern f32 lbl_8042F478;
void fn_80171698(Slot80171620* slot);

Slot80171620* fn_80171620(void)
{
	Slot80171620* slot = (Slot80171620*)lbl_8042C9A4->freeListAlloc(lbl_803EC968.freeList);
	if (slot != 0) {
		slot->f0  = 0;
		slot->f4  = 0;
		slot->f8  = 0;
		slot->fc  = 1;
		slot->f14 = 0;
		slot->f18 = slot;
		slot->f10 = lbl_8042F478;
		fn_80171698(slot);
	}
	return slot;
}
}
