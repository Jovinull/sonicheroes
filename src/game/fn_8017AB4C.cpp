// Allocates the state of the inflate code decoder (HYPOTHESIS: zlib inflate_codes_new) through the
// stream's allocator and records the literal/length and distance tables and their bit counts.
// Returns the state, or null when the allocation fails.
#include "types.h"

struct InflateCodes8017AB4C {
	int mode; // 0x0
	unsigned char pad4[0x10 - 0x4];
	unsigned char lbits; // 0x10
	unsigned char dbits; // 0x11
	unsigned char pad12[2];
	void* ltree; // 0x14
	void* dtree; // 0x18
};

struct ZStream8017AB4C {
	unsigned char pad0[0x20];
	void* (*zalloc)(void* opaque, unsigned int items, unsigned int size); // 0x20
	void* zfree;                                                          // 0x24
	void* opaque;                                                         // 0x28
};

extern "C" {
InflateCodes8017AB4C* fn_8017AB4C(
    unsigned int bl, unsigned int bd, void* tl, void* td, ZStream8017AB4C* z)
{
	InflateCodes8017AB4C* c
	    = (InflateCodes8017AB4C*)z->zalloc(z->opaque, 1, sizeof(InflateCodes8017AB4C));
	if (c != 0) {
		c->mode  = 0;
		c->lbits = (unsigned char)bl;
		c->dbits = (unsigned char)bd;
		c->ltree = tl;
		c->dtree = td;
	}
	return c;
}
}
