#include "types.h"

// Destructor (HYPOTHESIS; the class name is UNKNOWN): installs the class vtable lbl_8028AD0C,
// clears the global lbl_8042C760 when it points to this object, releases the handles at 0x34 and
// 0x30 (fn_80203998) and 0x38 (fn_801A173C) and the global lbl_8042C764 (fn_801A46D0), clearing
// each, runs the base destructor dtor_800C497C and frees the object on the game heap when the
// delete flag is positive. Returns the object.

struct THeapCtrl {
	void Free(void* p);
};

struct Obj8012E164 {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x30 - 0x1C];
	void* f30; // 0x30
	void* f34; // 0x34
	void* f38; // 0x38
};

extern "C" {
extern THeapCtrl* lbl_8042C148;
extern u8 lbl_8028AD0C[];
extern Obj8012E164* lbl_8042C760;
extern void* lbl_8042C764;
void fn_80203998(void* p);
void fn_801A173C(void* p);
void fn_801A46D0(void* p);
void dtor_800C497C(void* object, s16 flags);

Obj8012E164* fn_8012E164(Obj8012E164* o, s16 flags)
{
	if (o != NULL) {
		o->vtable = lbl_8028AD0C;
		if (lbl_8042C760 == o) {
			lbl_8042C760 = NULL;
		}
		if (o->f34 != NULL) {
			fn_80203998(o->f34);
			o->f34 = NULL;
		}
		if (o->f30 != NULL) {
			fn_80203998(o->f30);
			o->f30 = NULL;
		}
		if (o->f38 != NULL) {
			fn_801A173C(o->f38);
			o->f38 = NULL;
		}
		if (lbl_8042C764 != NULL) {
			fn_801A46D0(lbl_8042C764);
			lbl_8042C764 = NULL;
		}
		dtor_800C497C(o, 0);
		if (flags > 0) {
			lbl_8042C148->Free(o);
		}
	}
	return o;
}
}
