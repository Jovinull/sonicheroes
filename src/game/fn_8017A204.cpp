// Frees an inflate block decoder (HYPOTHESIS: zlib inflate_blocks_free): resets it as
// inflate_blocks_reset (fn_801791D8) does without reporting the check value, then frees its window,
// its Huffman table space (+0x24) and the decoder itself through the stream's zfree. Returns Z_OK.
#include "types.h"

enum InflateBlockMode8017A204 {
	TYPE_8017A204  = 0,
	BTREE_8017A204 = 4,
	DTREE_8017A204 = 5,
	CODES_8017A204 = 6
};

typedef unsigned int (*CheckFunc8017A204)(
    unsigned int check, const unsigned char* buffer, unsigned int length);

// Fields used here (HYPOTHESIS: inflate_blocks_state layout).
struct InflateBlocks8017A204 {
	int mode;    // 0x0
	void* codes; // 0x4, sub.decode.codes
	unsigned char pad8[0xC - 0x8];
	void* blens; // 0xC, sub.trees.blens
	unsigned char pad10[0x1C - 0x10];
	unsigned int bitk;     // 0x1C
	unsigned int bitb;     // 0x20
	void* hufts;           // 0x24
	unsigned char* window; // 0x28
	unsigned char pad2C[0x30 - 0x2C];
	unsigned char* read;       // 0x30
	unsigned char* write;      // 0x34
	CheckFunc8017A204 checkfn; // 0x38
	unsigned int check;        // 0x3C
};

struct ZStream8017A204 {
	unsigned char pad0[0x24];
	void (*zfree)(void* opaque, void* address); // 0x24
	void* opaque;                               // 0x28
	unsigned char pad2C[0x30 - 0x2C];
	unsigned int adler; // 0x30
};

extern "C" {
void fn_8017B50C(void* codes, ZStream8017A204* z);
}

// Same body as fn_801791D8 (inflate_blocks_reset).
static inline void InflateBlocksReset(InflateBlocks8017A204* s, ZStream8017A204* z, unsigned int* c)
{
	if (c != 0) {
		*c = s->check;
	}
	if (s->mode == BTREE_8017A204 || s->mode == DTREE_8017A204) {
		z->zfree(z->opaque, s->blens);
	}
	if (s->mode == CODES_8017A204) {
		fn_8017B50C(s->codes, z);
	}
	s->mode = TYPE_8017A204;
	s->bitk = 0;
	s->bitb = 0;
	s->read = s->write = s->window;
	if (s->checkfn != 0) {
		z->adler = s->check = s->checkfn(0, 0, 0);
	}
}

extern "C" {
int fn_8017A204(InflateBlocks8017A204* s, ZStream8017A204* z)
{
	InflateBlocksReset(s, z, 0);
	z->zfree(z->opaque, s->window);
	z->zfree(z->opaque, s->hufts);
	z->zfree(z->opaque, s);
	return 0;
}
}
