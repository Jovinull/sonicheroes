// Destructor of the particle core (TObjPtclCore; vtable lbl_80243C18): destroys every material
// of its list (+0x28; fn_80064CA8 unlinks the head), releases the resource +0x2C (fn_801A46D0),
// frees the buffer +0x30 and the sixteen buffers from +0x34 (RwFree), clearing them, destroys the
// TObject base and frees the object when flags > 0. Returns the object.
#include "types.h"

struct RwEngine80065E84 {
	u8 pad0[0x138];
	void (*rwfree)(void* block); // 0x138
};

struct Core80065E84 {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x28 - 0x1C];
	void* materials;   // 0x28
	void* resource;    // 0x2C
	void* buffer;      // 0x30
	void* buffers[16]; // 0x34
};

struct THeapCtrl;

extern "C" {
extern void* lbl_80243C18[];
extern RwEngine80065E84* lbl_8042C9A4;
extern THeapCtrl* lbl_8042C148;
void fn_80064CA8(void* material);
void fn_801A46D0(void* resource);
void __dt__7TObjectFv(void* o, s32 flags);
void Free__9THeapCtrlFPv(THeapCtrl* heap, void* p);

Core80065E84* fn_80065E84(Core80065E84* core, s16 flags)
{
	if (core != NULL) {
		u8 i;

		core->vtable = lbl_80243C18;
		while (core->materials != NULL) {
			fn_80064CA8(core->materials);
		}
		if (core->resource != NULL) {
			fn_801A46D0(core->resource);
			core->resource = NULL;
		}
		if (core->buffer != NULL) {
			lbl_8042C9A4->rwfree(core->buffer);
			core->buffer = NULL;
		}
		for (i = 0; i < 16; i++) {
			if (core->buffers[i] != NULL) {
				lbl_8042C9A4->rwfree(core->buffers[i]);
				core->buffers[i] = NULL;
			}
		}
		__dt__7TObjectFv(core, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, core);
		}
	}
	return core;
}
}
