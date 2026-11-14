// Resets an inflate block decoder (HYPOTHESIS: zlib inflate_blocks_reset): reports the running
// check value, frees the bit-length table (BTREE/DTREE modes) or the code decoder (CODES mode,
// through fn_8017B50C, inflate_codes_free), returns to the TYPE mode with an empty bit buffer and
// window, and restarts the check value through the check function when there is one.
#include "types.h"

enum InflateBlockMode801791D8 {
	TYPE_801791D8  = 0,
	BTREE_801791D8 = 4,
	DTREE_801791D8 = 5,
	CODES_801791D8 = 6
};

typedef unsigned int (*CheckFunc801791D8)(
    unsigned int check, const unsigned char* buffer, unsigned int length);

// Fields used here (HYPOTHESIS: inflate_blocks_state layout).
struct InflateBlocks801791D8 {
	int mode;    // 0x0
	void* codes; // 0x4, sub.decode.codes
	unsigned char pad8[0xC - 0x8];
	void* blens; // 0xC, sub.trees.blens
	unsigned char pad10[0x1C - 0x10];
	unsigned int bitk; // 0x1C
	unsigned int bitb; // 0x20
	unsigned char pad24[0x28 - 0x24];
	unsigned char* window; // 0x28
	unsigned char pad2C[0x30 - 0x2C];
	unsigned char* read;       // 0x30
	unsigned char* write;      // 0x34
	CheckFunc801791D8 checkfn; // 0x38
	unsigned int check;        // 0x3C
};

struct ZStream801791D8 {
	unsigned char pad0[0x24];
	void (*zfree)(void* opaque, void* address); // 0x24
	void* opaque;                               // 0x28
	unsigned char pad2C[0x30 - 0x2C];
	unsigned int adler; // 0x30
};

extern "C" {
void fn_8017B50C(void* codes, ZStream801791D8* z);

void fn_801791D8(InflateBlocks801791D8* s, ZStream801791D8* z, unsigned int* c)
{
	if (c != 0) {
		*c = s->check;
	}
	if (s->mode == BTREE_801791D8 || s->mode == DTREE_801791D8) {
		z->zfree(z->opaque, s->blens);
	}
	if (s->mode == CODES_801791D8) {
		fn_8017B50C(s->codes, z);
	}
	s->mode = TYPE_801791D8;
	s->bitk = 0;
	s->bitb = 0;
	s->read = s->write = s->window;
	if (s->checkfn != 0) {
		z->adler = s->check = s->checkfn(0, 0, 0);
	}
}
}
