// Builds the Huffman tree for the 19 code-length codes of a dynamic block (HYPOTHESIS: zlib
// inflate_trees_bits) through fn_8017A2FC (huft_build) with a temporary work area from the stream's
// allocator, setting the stream message (lbl_8028D9A0 oversubscribed, lbl_8028D9C8 incomplete) on
// failure. Returns the zlib status (Z_MEM_ERROR -4, Z_DATA_ERROR -3, ...).
#include "types.h"

#define Z_DATA_ERROR (-3)
#define Z_MEM_ERROR  (-4)
#define Z_BUF_ERROR  (-5)

struct ZStream8017A848 {
	unsigned char pad0[0x18];
	char* msg; // 0x18
	void* state;
	void* (*zalloc)(void* opaque, unsigned int items, unsigned int size); // 0x20
	void (*zfree)(void* opaque, void* address);                           // 0x24
	void* opaque;                                                         // 0x28
};

extern "C" {
extern char lbl_8028D9A0[];
extern char lbl_8028D9C8[];
int fn_8017A2FC(unsigned int* b, unsigned int n, unsigned int s, const unsigned int* d,
    const unsigned int* e, void** t, unsigned int* m, void* hp, unsigned int* hn, unsigned int* v);

int fn_8017A848(unsigned int* c, unsigned int* bb, void** tb, void* hp, ZStream8017A848* z)
{
	int r;
	unsigned int hn = 0;
	unsigned int* v;
	if ((v = (unsigned int*)z->zalloc(z->opaque, 19, sizeof(unsigned int))) == 0) {
		return Z_MEM_ERROR;
	}
	r = fn_8017A2FC(c, 19, 19, 0, 0, tb, bb, hp, &hn, v);
	if (r == Z_DATA_ERROR) {
		z->msg = lbl_8028D9A0;
	} else if (r == Z_BUF_ERROR || *bb == 0) {
		z->msg = lbl_8028D9C8;
		r      = Z_DATA_ERROR;
	}
	z->zfree(z->opaque, v);
	return r;
}
}
