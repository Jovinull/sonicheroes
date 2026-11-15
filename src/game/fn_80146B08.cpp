// Destroys the sub-object referenced by *(object + offset), where offset is word 2 of the
// 16-byte record lbl_803EC3F8[index]. The release body is the helper the original file
// shared with fn_80146020: release the children at +0x08 (count at +0x04) through
// fn_801A491C, the block at +0x30 through fn_80147288, free the entry, clear the slot.
#include "types.h"

struct Ent80146B08 {
	unsigned int unk0;        // 0x00
	unsigned int f4;          // 0x04
	unsigned char pad8[0x28]; // 0x08
	void* f30;                // 0x30
};

struct MemoryAllocator {
	unsigned char pad[0x134];
	void* (*Alloc)(u32 size);
	void (*Free)(void* address);
};

extern "C" {
extern MemoryAllocator* lbl_8042C9A4;
extern unsigned char lbl_803EC3F8[];
void fn_801A491C(void*);
void fn_80147288(void*);

static inline void Release80146B08(Ent80146B08* h)
{
	void** p;
	unsigned int i;

	i = 0;
	p = (void**)h;
	for (; i < h->f4; i++) {
		if (p[2] != 0) {
			fn_801A491C(p[2]);
			p[2] = 0;
		}
		p++;
	}
	if (h->f30 != 0) {
		fn_80147288(h->f30);
		h->f30 = 0;
	}
	lbl_8042C9A4->Free(h);
}

char* fn_80146B08(char* object, int index)
{
	int offset;
	Ent80146B08* h;

	offset = *(int*)(lbl_803EC3F8 + index * 0x10 + 8);
	h      = *(Ent80146B08**)(object + offset);
	if (h != 0) {
		Release80146B08(h);
		*(int*)(object + offset) = 0;
	}
	return object;
}
}
