#include "types.h"

// TObjPtclCore::~TObjPtclCore() (CORROBORATED by PS2 metadata): uses the vtable TObjPtclCore's constructor
// stores, detaches every material and destroys the texture dictionary, like the PS2 destructor.
// Names are from PS2; the symbol keeps its address-based name.

extern "C" {
void __dt__7TObjectFv(void* o, s32 flags);
void Free__9THeapCtrlFPv(void* heap, void* p);
void fn_80064CA8(void* p);
void fn_801A46D0(void* p);

extern u8 lbl_80243C18[];
extern void* lbl_8042C148;
extern void* lbl_8042C9A4;

struct Particle65E84 {
	u8 pad0[0x18];
	void* vptr; // 0x18
	u8 pad1[0x28 - 0x1C];
	void* f28;     // 0x28
	void* f2c;     // 0x2c
	void* f30;     // 0x30
	void* f34[16]; // 0x34
};

Particle65E84* fn_80065E84(Particle65E84* o, s16 flags)
{
	u8 i;

	if (o != NULL) {
		o->vptr = lbl_80243C18;
		while (o->f28 != NULL) {
			fn_80064CA8(o->f28);
		}
		if (o->f2c != NULL) {
			fn_801A46D0(o->f2c);
			o->f2c = NULL;
		}
		if (o->f30 != NULL) {
			((void (*)(void*))((void**)lbl_8042C9A4)[0x138 / 4])(o->f30);
			o->f30 = NULL;
		}
		for (i = 0; i < 16; i++) {
			if (o->f34[i] != NULL) {
				((void (*)(void*))((void**)lbl_8042C9A4)[0x138 / 4])(o->f34[i]);
				o->f34[i] = NULL;
			}
		}
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
