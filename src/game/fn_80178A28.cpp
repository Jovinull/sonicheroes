// Initializes an inflate stream (HYPOTHESIS: zlib inflateInit_ with inflateInit2_, inflateEnd and
// inflateReset inlined): checks the library version (first character of lbl_8042BDC0) and the
// stream size, installs the default allocator fn_801788D4 / deallocator fn_801788FC when none is
// given, allocates the 0x18-byte state with a 15-bit window and a block decoder (fn_801792A0,
// inflate_blocks_new, with adler32 fn_80178738 as check), and resets the stream. Returns the zlib
// status: Z_VERSION_ERROR (-6), Z_STREAM_ERROR (-2), Z_MEM_ERROR (-4) or Z_OK (0).
#include "types.h"

#define Z_OK            0
#define Z_STREAM_ERROR  (-2)
#define Z_MEM_ERROR     (-4)
#define Z_VERSION_ERROR (-6)
#define DEF_WBITS       15

enum InflateMode80178A28 { INFLATE_METHOD = 0, INFLATE_BLOCKS = 7 };

typedef unsigned int (*CheckFunc80178A28)(
    unsigned int check, const unsigned char* buffer, unsigned int length);

struct InflateState80178A28 {
	InflateMode80178A28 mode; // 0x0
	unsigned char pad4[0xC - 0x4];
	int nowrap;         // 0xC
	unsigned int wbits; // 0x10
	void* blocks;       // 0x14
};

struct ZStream80178A28 {
	unsigned char pad0[0x8];
	unsigned int totalIn; // 0x8
	unsigned char padC[0x14 - 0xC];
	unsigned int totalOut;                                                // 0x14
	char* msg;                                                            // 0x18
	InflateState80178A28* state;                                          // 0x1C
	void* (*zalloc)(void* opaque, unsigned int items, unsigned int size); // 0x20
	void (*zfree)(void* opaque, void* address);                           // 0x24
	void* opaque;                                                         // 0x28
	unsigned char pad2C[0x38 - 0x2C];
};

extern "C" {
// First character of ZLIB_VERSION (HYPOTHESIS).
extern const char lbl_8042BDC0[8];
void* fn_801788D4(void* opaque, unsigned int items, unsigned int size);
void fn_801788FC(void* opaque, void* address);
unsigned int fn_80178738(unsigned int adler, const unsigned char* buffer, unsigned int length);
void* fn_801792A0(ZStream80178A28* z, CheckFunc80178A28 c, unsigned int w);
void fn_801791D8(void* blocks, ZStream80178A28* z, unsigned int* c);
void fn_8017A204(void* blocks, ZStream80178A28* z);
}

// Same body as fn_801789A8 (inflateEnd).
static inline int InflateEnd(ZStream80178A28* z)
{
	if (z == 0 || z->state == 0 || z->zfree == 0) {
		return Z_STREAM_ERROR;
	}
	if (z->state->blocks != 0) {
		fn_8017A204(z->state->blocks, z);
	}
	z->zfree(z->opaque, z->state);
	z->state = 0;
	return Z_OK;
}

// Same body as fn_80178930 (inflateReset).
static inline int InflateReset(ZStream80178A28* z)
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

// HYPOTHESIS: inflateInit2_ (window size fixed by the caller).
static inline int InflateInit2(ZStream80178A28* z, int w, const char* version, int streamSize)
{
	if (version == 0 || version[0] != lbl_8042BDC0[0] || streamSize != sizeof(ZStream80178A28)) {
		return Z_VERSION_ERROR;
	}
	if (z == 0) {
		return Z_STREAM_ERROR;
	}
	z->msg = 0;
	if (z->zalloc == 0) {
		z->zalloc = fn_801788D4;
		z->opaque = 0;
	}
	if (z->zfree == 0) {
		z->zfree = fn_801788FC;
	}
	if ((z->state = (InflateState80178A28*)z->zalloc(z->opaque, 1, sizeof(InflateState80178A28)))
	    == 0) {
		return Z_MEM_ERROR;
	}
	z->state->blocks = 0;
	z->state->nowrap = 0;
	z->state->wbits  = (unsigned int)w;
	if ((z->state->blocks
	        = fn_801792A0(z, z->state->nowrap ? 0 : fn_80178738, (unsigned int)1 << w))
	    == 0) {
		InflateEnd(z);
		return Z_MEM_ERROR;
	}
	InflateReset(z);
	return Z_OK;
}

extern "C" {
int fn_80178A28(ZStream80178A28* z, const char* version, int streamSize)
{
	return InflateInit2(z, DEF_WBITS, version, streamSize);
}
}
