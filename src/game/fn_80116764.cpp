#include "types.h"

// BobsleighTime::~BobsleighTime() (CORROBORATED by the PS2 build: __dt__13BobsleighTimeFv sits
// right before the constructor and DestroyBobsleigh there too, and __vt__13BobsleighTime has the
// same 0x2C size), written out as the function MWCC makes of it: installs the class vtable,
// clears the global lbl_8042C690, releases the globals lbl_8042C698 (fn_80203998) and
// lbl_8042C694 (fn_801A46D0) and clears them, runs the TObject destructor and frees the object on
// the game heap when the delete flag is positive. Returns the object.

struct THeapCtrl {
	void Free(void* p);
};

struct Obj80116764 {
	u8 pad0[0x18];
	void* vtable; // 0x18
};

extern "C" {
extern THeapCtrl* lbl_8042C148;
extern u8 __vt__13BobsleighTime[];
extern void* lbl_8042C690;
extern void* lbl_8042C694;
extern void* lbl_8042C698;
void fn_80203998(void* p);
void fn_801A46D0(void* p);
void __dt__7TObjectFv(void* object, s16 flags);

Obj80116764* __dt__13BobsleighTimeFv(Obj80116764* o, s16 flags)
{
	if (o != NULL) {
		o->vtable = __vt__13BobsleighTime;
		if (lbl_8042C690 != NULL) {
			lbl_8042C690 = NULL;
		}
		if (lbl_8042C698 != NULL) {
			fn_80203998(lbl_8042C698);
			lbl_8042C698 = NULL;
		}
		if (lbl_8042C694 != NULL) {
			fn_801A46D0(lbl_8042C694);
			lbl_8042C694 = NULL;
		}
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			lbl_8042C148->Free(o);
		}
	}
	return o;
}
}
