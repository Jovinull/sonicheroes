#include "types.h"

// Destructor (HYPOTHESIS; the class name is UNKNOWN): installs the class vtable lbl_8028A078.
// When this is the registered instance (lbl_8042C738) it clears that, releases lbl_8042C744
// (fn_80203998), clears lbl_8042C740 and releases lbl_8042C73C (fn_801A46D0). It then asks the
// task objects lbl_8042C748, lbl_8042C754 and lbl_8042C758 to die (bit 0 of their signal word),
// releases lbl_8042C74C and lbl_8042C750 (fn_801A46D0), clearing every global, calls
// fn_80120060, runs the base destructor dtor_800C497C and frees the object on the game heap when
// the delete flag is positive. Returns the object.

struct THeapCtrl {
	void Free(void* p);
};

struct Task8012BFCC {
	u8 pad0[0x4];
	u16 signal; // 0x4
};

struct Obj8012BFCC {
	u8 pad0[0x18];
	void* vtable; // 0x18
};

extern "C" {
extern THeapCtrl* lbl_8042C148;
extern u8 lbl_8028A078[];
extern Obj8012BFCC* lbl_8042C738;
extern void* lbl_8042C73C;
extern s32 lbl_8042C740;
extern void* lbl_8042C744;
extern Task8012BFCC* lbl_8042C748;
extern void* lbl_8042C74C;
extern void* lbl_8042C750;
extern Task8012BFCC* lbl_8042C754;
extern Task8012BFCC* lbl_8042C758;
void fn_80203998(void* p);
void fn_801A46D0(void* p);
void fn_80120060(void);
void dtor_800C497C(void* object, s16 flags);

Obj8012BFCC* fn_8012BFCC(Obj8012BFCC* o, s16 flags)
{
	if (o != NULL) {
		o->vtable = lbl_8028A078;
		if (lbl_8042C738 == o) {
			lbl_8042C738 = NULL;
			if (lbl_8042C744 != NULL) {
				fn_80203998(lbl_8042C744);
				lbl_8042C744 = NULL;
			}
			lbl_8042C740 = 0;
			if (lbl_8042C73C != NULL) {
				fn_801A46D0(lbl_8042C73C);
				lbl_8042C73C = NULL;
			}
		}
		if (lbl_8042C748 != NULL) {
			lbl_8042C748->signal |= 1;
			lbl_8042C748 = NULL;
		}
		if (lbl_8042C74C != NULL) {
			fn_801A46D0(lbl_8042C74C);
			lbl_8042C74C = NULL;
		}
		if (lbl_8042C750 != NULL) {
			fn_801A46D0(lbl_8042C750);
			lbl_8042C750 = NULL;
		}
		if (lbl_8042C754 != NULL) {
			lbl_8042C754->signal |= 1;
			lbl_8042C754 = NULL;
		}
		if (lbl_8042C758 != NULL) {
			lbl_8042C758->signal |= 1;
			lbl_8042C758 = NULL;
		}
		fn_80120060();
		dtor_800C497C(o, 0);
		if (flags > 0) {
			lbl_8042C148->Free(o);
		}
	}
	return o;
}
}
