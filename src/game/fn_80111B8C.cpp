#include "game/rw_engine.h"

// Destructor (HYPOTHESIS; the class name is UNKNOWN): installs the class vtable lbl_802634F8,
// frees the RenderWare buffer at 0x80, destroys and frees the MESSAGE at 0x7C, runs the TObject
// destructor and frees the object on the game heap when the delete flag is positive. Returns the
// object.

struct THeapCtrl {
	void Free(void* p);
};

struct Obj80111B8C {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x7C - 0x1C];
	void* message; // 0x7C: MESSAGE
	void* buffer;  // 0x80
};

extern "C" {
extern THeapCtrl* lbl_8042C148;
extern u8 lbl_802634F8[];
void __dt__7MESSAGEFv(void* message, s16 flags);
void __dt__7TObjectFv(void* object, s16 flags);

Obj80111B8C* fn_80111B8C(Obj80111B8C* o, s16 flags)
{
	if (o != NULL) {
		o->vtable = lbl_802634F8;
		lbl_8042C9A4->rwfree(o->buffer);
		if (o->message != NULL) {
			__dt__7MESSAGEFv(o->message, 1);
		}
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			lbl_8042C148->Free(o);
		}
	}
	return o;
}
}
