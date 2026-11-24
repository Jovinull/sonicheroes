#include "types.h"

// Destructor (HYPOTHESIS; the class name is UNKNOWN): installs the class vtable lbl_80289538;
// each of the two objects at 0xD0 and 0xD4 that is still valid (fn_80017800) is destroyed with
// fn_8005FD8C (delete flag -1) and the pointer cleared; then runs the C_COLLI destructor of the
// member at 0x28 and the TObject destructor, and frees the object on the game heap when the
// delete flag is positive. Returns the object.

struct THeapCtrl {
	void Free(void* p);
};

struct Obj8011DBEC {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x28 - 0x1C];
	u8 colli[0xD0 - 0x28]; // 0x28: C_COLLI
	void* objD0;           // 0xD0
	void* objD4;           // 0xD4
};

extern "C" {
extern THeapCtrl* lbl_8042C148;
extern u8 lbl_80289538[];
s32 fn_80017800(void* object);
void fn_8005FD8C(void* object, s16 flags);
void __dt__7C_COLLIFv(void* colli, s16 flags);
void __dt__7TObjectFv(void* object, s16 flags);

Obj8011DBEC* fn_8011DBEC(Obj8011DBEC* o, s16 flags)
{
	if (o != NULL) {
		o->vtable = lbl_80289538;
		if (o->objD0 != NULL && fn_80017800(o->objD0) != 0) {
			fn_8005FD8C(o->objD0, -1);
			o->objD0 = NULL;
		}
		if (o->objD4 != NULL && fn_80017800(o->objD4) != 0) {
			fn_8005FD8C(o->objD4, -1);
			o->objD4 = NULL;
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
