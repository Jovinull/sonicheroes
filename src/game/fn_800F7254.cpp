// Destructor of the class whose vtable is lbl_80259FD0, with its base destructor (vtable
// lbl_8025A0A8) inlined: the base removes its clump (+0xE8) from the stage world
// (+0x72A0 of lbl_8042C1D0; fn_8015BBF8) and destroys it (fn_80150958), then destroys the C_COLLI
// (+0x28) and TObject bases; the object is freed when flags > 0. Returns the object. The class
// names are UNKNOWN.
#include "types.h"

struct Obj800F7254 {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x28 - 0x1C];
	u8 colli[0xE8 - 0x28]; // 0x28 (C_COLLI base)
	void* clump;           // 0xE8
};

struct Stage800F7254 {
	u8 pad0[0x72A0];
	void* world; // 0x72A0
};

struct THeapCtrl;

extern "C" {
extern void* lbl_80259FD0[];
extern void* lbl_8025A0A8[];
extern Stage800F7254* lbl_8042C1D0;
extern THeapCtrl* lbl_8042C148;
void fn_8015BBF8(void* world, void* clump);
void fn_80150958(void* clump);
void __dt__7C_COLLIFv(void* colli, s32 flags);
void __dt__7TObjectFv(void* o, s32 flags);
void Free__9THeapCtrlFPv(THeapCtrl* heap, void* p);

Obj800F7254* fn_800F7254(Obj800F7254* o, s16 flags)
{
	if (o != NULL) {
		o->vtable = lbl_80259FD0;
		if (o != NULL) {
			o->vtable = lbl_8025A0A8;
			if (o->clump != NULL) {
				fn_8015BBF8(lbl_8042C1D0->world, o->clump);
				fn_80150958(o->clump);
				o->clump = NULL;
			}
			__dt__7C_COLLIFv(o->colli, 0);
			__dt__7TObjectFv(o, 0);
		}
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
