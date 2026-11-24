#include "types.h"

// Destructor (HYPOTHESIS; the class name is UNKNOWN): installs the class vtable lbl_80289FB4,
// releases the four handles at 0xD8..0xE4 (fn_80150958) and clears them, runs the C_COLLI
// destructor of the member at 0x28 and the TObject destructor, and frees the object on the game
// heap when the delete flag is positive. Returns the object.

struct THeapCtrl {
	void Free(void* p);
};

struct Obj801289A4 {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x28 - 0x1C];
	u8 colli[0xD8 - 0x28]; // 0x28: C_COLLI
	void* handles[4];      // 0xD8
};

extern "C" {
extern THeapCtrl* lbl_8042C148;
extern u8 lbl_80289FB4[];
void fn_80150958(void* handle);
void __dt__7C_COLLIFv(void* colli, s16 flags);
void __dt__7TObjectFv(void* object, s16 flags);

Obj801289A4* fn_801289A4(Obj801289A4* o, s16 flags)
{
	if (o != NULL) {
		o->vtable = lbl_80289FB4;
		for (int i = 0; i < 4; i++) {
			if (o->handles[i] != NULL) {
				fn_80150958(o->handles[i]);
				o->handles[i] = NULL;
			}
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
