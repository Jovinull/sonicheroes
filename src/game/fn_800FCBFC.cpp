// Destructor of an object (vtable lbl_8025A2E0; the class name is UNKNOWN) that owns shared
// models: destroys the two clumps of lbl_8042B708 (fn_80150958), clears lbl_8042C570, releases the
// seven entries of lbl_803E7198 (fn_8020C2D8) and the resource lbl_8042C574 (fn_801A46D0),
// clearing them, then destroys the C_COLLI (+0x28) and TObject bases and frees the object when
// flags > 0. Returns the object.
#include "types.h"

struct Obj800FCBFC {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x28 - 0x1C];
	u8 colli[0x88]; // 0x28 (C_COLLI base)
};

struct THeapCtrl;

extern "C" {
extern void* lbl_8025A2E0[];
extern void* lbl_8042B708[2];
extern s32 lbl_8042C570;
extern void* lbl_803E7198[7];
extern void* lbl_8042C574;
extern THeapCtrl* lbl_8042C148;
void fn_80150958(void* clump);
void fn_8020C2D8(void* object);
void fn_801A46D0(void* resource);
void __dt__7C_COLLIFv(void* colli, s32 flags);
void __dt__7TObjectFv(void* o, s32 flags);
void Free__9THeapCtrlFPv(THeapCtrl* heap, void* p);
}

extern "C" Obj800FCBFC* fn_800FCBFC(Obj800FCBFC* o, s16 flags)
{
	if (o != NULL) {
		int i;

		o->vtable = lbl_8025A2E0;
		for (i = 0; i < 2; i++) {
			fn_80150958(lbl_8042B708[i]);
			lbl_8042B708[i] = NULL;
		}
		lbl_8042C570 = 0;
		for (i = 0; i < 7; i++) {
			if (lbl_803E7198[i] != NULL) {
				fn_8020C2D8(lbl_803E7198[i]);
				lbl_803E7198[i] = NULL;
			}
		}
		fn_801A46D0(lbl_8042C574);
		lbl_8042C574 = NULL;
		__dt__7C_COLLIFv(o->colli, 0);
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
