// Tears down the matrix stack of the record lbl_803EC968: destroys every allocated slot of the
// 32-entry stack (+0x234) through fn_80196434 (RwMatrixDestroy), resets the depth (+0x2B4) and frees
// the buffer at +0x9B4 with the engine memory function, clearing it and the word at +0x9B8.
#include "game/rw_engine.h"

struct Rec8016F0C8 {
	u8 pad0[0x234];
	RwMatrix* stack[0x20]; // 0x234
	s32 count;             // 0x2B4
	u8 pad2B8[0x9B4 - 0x2B8];
	void* buffer; // 0x9B4
	s32 f9B8;     // 0x9B8
};

extern "C" {
extern Rec8016F0C8 lbl_803EC968;
s32 fn_80196434(RwMatrix* matrix);

void fn_8016F0C8(void)
{
	s32 i;
	for (i = 0; i < 0x20; i++) {
		if (lbl_803EC968.stack[i] != 0) {
			fn_80196434(lbl_803EC968.stack[i]);
			lbl_803EC968.stack[i] = 0;
		}
	}
	lbl_803EC968.count = 0;
	if (lbl_803EC968.buffer != 0) {
		lbl_8042C9A4->rwfree(lbl_803EC968.buffer);
		lbl_803EC968.buffer = 0;
		lbl_803EC968.f9B8   = 0;
	}
}
}
