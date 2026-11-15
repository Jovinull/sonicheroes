// Destructor of the base class whose vtable is lbl_80254594 (a TObject with only its destructor
// overridden; the class name is UNKNOWN). It drops the object from the five per-channel tables,
// indexed by the signed byte at 0x28, and from the six current-object globals, runs the TObject
// destructor and frees the object when flags > 0. Returns the object. fn_800C0080 (a derived
// destructor) inlines the same body.
#include "types.h"

struct Obj800C497C {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x28 - 0x1C];
	s8 channel; // 0x28
};

struct THeapCtrl;

extern "C" {
extern void* lbl_80254594[];
extern Obj800C497C* lbl_803043D8[];
extern Obj800C497C* lbl_803043C8[];
extern Obj800C497C* lbl_803043E8[];
extern Obj800C497C* lbl_803043F8[];
extern Obj800C497C* lbl_80304408[];
extern Obj800C497C* lbl_8042C40C;
extern Obj800C497C* lbl_8042C400;
extern Obj800C497C* lbl_8042C414;
extern Obj800C497C* lbl_8042C41C;
extern Obj800C497C* lbl_8042C424;
extern Obj800C497C* lbl_8042C42C;
extern THeapCtrl* lbl_8042C148;
void __dt__7TObjectFv(void* o, s32 flags);
void Free__9THeapCtrlFPv(THeapCtrl* heap, void* p);

Obj800C497C* dtor_800C497C(Obj800C497C* o, s16 flags)
{
	if (o != NULL) {
		s32 c;

		o->vtable = lbl_80254594;
		c         = o->channel;
		if (lbl_803043D8[c] == o) {
			lbl_803043D8[c] = NULL;
		}
		if (lbl_803043C8[c] == o) {
			lbl_803043C8[c] = NULL;
		}
		if (lbl_803043E8[c] == o) {
			lbl_803043E8[c] = NULL;
		}
		if (lbl_803043F8[c] == o) {
			lbl_803043F8[c] = NULL;
		}
		if (lbl_80304408[c] == o) {
			lbl_80304408[c] = NULL;
		}
		if (lbl_8042C40C == o) {
			lbl_8042C40C = NULL;
		}
		if (lbl_8042C400 == o) {
			lbl_8042C400 = NULL;
		}
		if (lbl_8042C414 == o) {
			lbl_8042C414 = NULL;
		}
		if (lbl_8042C41C == o) {
			lbl_8042C41C = NULL;
		}
		if (lbl_8042C424 == o) {
			lbl_8042C424 = NULL;
		}
		if (lbl_8042C42C == o) {
			lbl_8042C42C = NULL;
		}
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
