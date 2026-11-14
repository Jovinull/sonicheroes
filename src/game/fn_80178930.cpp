// Resets an inflate stream (HYPOTHESIS: zlib inflateReset): clears the byte totals and the message,
// restarts in BLOCKS mode for raw streams (nowrap) or METHOD mode otherwise and resets the block
// decoder through fn_801791D8 (inflate_blocks_reset). Returns Z_STREAM_ERROR (-2) for a stream
// without state, otherwise Z_OK (0).
#include "types.h"

#define Z_OK           0
#define Z_STREAM_ERROR (-2)
enum InflateMode80178930 { INFLATE_METHOD = 0, INFLATE_BLOCKS = 7 };

struct InflateState80178930 {
	InflateMode80178930 mode; // 0x0
	unsigned char pad4[0xC - 0x4];
	int nowrap; // 0xC
	unsigned char pad10[0x14 - 0x10];
	void* blocks; // 0x14
};

struct ZStream80178930 {
	unsigned char pad0[0x8];
	unsigned int totalIn; // 0x8
	unsigned char padC[0x14 - 0xC];
	unsigned int totalOut;       // 0x14
	char* msg;                   // 0x18
	InflateState80178930* state; // 0x1C
};

extern "C" {
void fn_801791D8(void* blocks, ZStream80178930* z, unsigned int* c);

int fn_80178930(ZStream80178930* z)
{
	if (z == 0 || z->state == 0) {
		return Z_STREAM_ERROR;
	}
	z->totalIn = z->totalOut = 0;
	z->msg                   = 0;
	z->state->mode           = z->state->nowrap ? INFLATE_BLOCKS : INFLATE_METHOD;
	fn_801791D8(z->state->blocks, z, 0);
	return Z_OK;
}
}
