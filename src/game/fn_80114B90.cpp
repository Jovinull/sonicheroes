#include "types.h"

// Destructor (HYPOTHESIS; the class name is UNKNOWN): installs the class vtable lbl_80288DC0;
// for each of the two handles at 0x11C and 0x120, unregisters it from the list at word 0x7258 or
// 0x72A0 of lbl_8042C1D0 (fn_8015BBF8), releases it (fn_80150958) and clears it; then runs the
// C_COLLI destructor of the member at 0x28 and the TObject destructor, and frees the object on
// the game heap when the delete flag is positive. Returns the object.

struct THeapCtrl {
	void Free(void* p);
};

struct Stage80114B90 {
	u8 pad0[0x7258];
	void* list7258; // 0x7258
	u8 pad725C[0x72A0 - 0x725C];
	void* list72A0; // 0x72A0
};

struct Obj80114B90 {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x28 - 0x1C];
	u8 colli[0x11C - 0x28]; // 0x28: C_COLLI
	void* handle11C;        // 0x11C
	void* handle120;        // 0x120
};

extern "C" {
extern THeapCtrl* lbl_8042C148;
extern Stage80114B90* lbl_8042C1D0;
extern u8 lbl_80288DC0[];
void fn_8015BBF8(void* list, void* handle);
void fn_80150958(void* handle);
void __dt__7C_COLLIFv(void* colli, s16 flags);
void __dt__7TObjectFv(void* object, s16 flags);

Obj80114B90* fn_80114B90(Obj80114B90* o, s16 flags)
{
	if (o != NULL) {
		o->vtable = lbl_80288DC0;
		if (o->handle11C != NULL) {
			fn_8015BBF8(lbl_8042C1D0->list7258, o->handle11C);
			fn_80150958(o->handle11C);
			o->handle11C = NULL;
		}
		if (o->handle120 != NULL) {
			fn_8015BBF8(lbl_8042C1D0->list72A0, o->handle120);
			fn_80150958(o->handle120);
			o->handle120 = NULL;
		}
		__dt__7C_COLLIFv(o->colli, 0);
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			lbl_8042C148->Free(o);
		}
	}
	return o;
}
}
