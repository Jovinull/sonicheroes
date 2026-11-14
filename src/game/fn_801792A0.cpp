// Allocates an inflate block decoder (HYPOTHESIS: zlib inflate_blocks_new): the 0x40-byte state,
// 1440 eight-byte Huffman table entries and a w-byte window through the stream's allocator (freeing
// what was already allocated when a step fails), records the window end and the check function and
// resets it as inflate_blocks_reset (fn_801791D8) does without reporting the check value. Returns
// the decoder, or null.
#include "types.h"

enum InflateBlockMode801792A0 {
	TYPE_801792A0  = 0,
	BTREE_801792A0 = 4,
	DTREE_801792A0 = 5,
	CODES_801792A0 = 6
};

typedef unsigned int (*CheckFunc801792A0)(
    unsigned int check, const unsigned char* buffer, unsigned int length);

// Fields used here (HYPOTHESIS: inflate_blocks_state layout).
struct InflateBlocks801792A0 {
	int mode;    // 0x0
	void* codes; // 0x4, sub.decode.codes
	unsigned char pad8[0xC - 0x8];
	void* blens; // 0xC, sub.trees.blens
	unsigned char pad10[0x1C - 0x10];
	unsigned int bitk;         // 0x1C
	unsigned int bitb;         // 0x20
	void* hufts;               // 0x24
	unsigned char* window;     // 0x28
	unsigned char* end;        // 0x2C
	unsigned char* read;       // 0x30
	unsigned char* write;      // 0x34
	CheckFunc801792A0 checkfn; // 0x38
	unsigned int check;        // 0x3C
};

struct ZStream801792A0 {
	unsigned char pad0[0x20];
	void* (*zalloc)(void* opaque, unsigned int items, unsigned int size); // 0x20
	void (*zfree)(void* opaque, void* address);                           // 0x24
	void* opaque;                                                         // 0x28
	unsigned char pad2C[0x30 - 0x2C];
	unsigned int adler; // 0x30
};

extern "C" {
void fn_8017B50C(void* codes, ZStream801792A0* z);
}

// Same body as fn_801791D8 (inflate_blocks_reset).
static inline void InflateBlocksReset(InflateBlocks801792A0* s, ZStream801792A0* z, unsigned int* c)
{
	if (c != 0) {
		*c = s->check;
	}
	if (s->mode == BTREE_801792A0 || s->mode == DTREE_801792A0) {
		z->zfree(z->opaque, s->blens);
	}
	if (s->mode == CODES_801792A0) {
		fn_8017B50C(s->codes, z);
	}
	s->mode = TYPE_801792A0;
	s->bitk = 0;
	s->bitb = 0;
	s->read = s->write = s->window;
	if (s->checkfn != 0) {
		z->adler = s->check = s->checkfn(0, 0, 0);
	}
}

extern "C" {
InflateBlocks801792A0* fn_801792A0(ZStream801792A0* z, CheckFunc801792A0 c, unsigned int w)
{
	InflateBlocks801792A0* s;
	if ((s = (InflateBlocks801792A0*)z->zalloc(z->opaque, 1, sizeof(InflateBlocks801792A0))) == 0) {
		return s;
	}
	if ((s->hufts = z->zalloc(z->opaque, 8, 1440)) == 0) {
		z->zfree(z->opaque, s);
		return 0;
	}
	if ((s->window = (unsigned char*)z->zalloc(z->opaque, 1, w)) == 0) {
		z->zfree(z->opaque, s->hufts);
		z->zfree(z->opaque, s);
		return 0;
	}
	s->end     = s->window + w;
	s->checkfn = c;
	s->mode    = TYPE_801792A0;
	InflateBlocksReset(s, z, 0);
	return s;
}
}
