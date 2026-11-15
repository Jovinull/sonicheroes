#include "types.h"

// Same declaration as src/game/Memory.cpp: the RenderWare engine instance's memory callbacks.
struct MemoryAllocator {
	u8 pad[308];
	void* (*Alloc)(u32 size);
	void (*Free)(void* address);
};

extern MemoryAllocator* lbl_8042C9A4;

struct Object8014D8A4 {
	u8 pad[0x10];
	void* unk10;
	void* unk14;
};

// Frees the two owned pointers, then the object itself; the caller (fn_8004CD24) clears its slot.
extern "C" s32 fn_8014D8A4(Object8014D8A4* self)
{
	if (self->unk14 != 0) {
		lbl_8042C9A4->Free(self->unk14);
		self->unk14 = 0;
	}
	if (self->unk10 != 0) {
		lbl_8042C9A4->Free(self->unk10);
		self->unk10 = 0;
	}
	lbl_8042C9A4->Free(self);
	return 1;
}
