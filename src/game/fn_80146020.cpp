#include "types.h"

// The entry released here is the same growable array as game/fn_80146214.cpp: the item
// count is at +0x04, the child pointers start at +0x08 and the optional extra block hangs
// off +0x30. lbl_8042C9A4 is the RenderWare engine memory callback table (game/Memory.cpp),
// whose free function is the pointer at +0x138.
struct Ent80146020 {
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
void fn_801A491C(void*);
void fn_80147288(void*);

// Releases the entry's children, its optional extra block and the entry itself, then clears
// the slot it came from. The original file shared this body between its release helpers, so
// it is written as a helper that is fully inlined into fn_80146020.
static inline void Release80146020(Ent80146020* h)
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

int fn_80146020(int a, int b)
{
	Ent80146020* h = *(Ent80146020**)(a + b);
	if (h != 0) {
		Release80146020(h);
		*(int*)(a + b) = 0;
	}
	return a;
}
}
