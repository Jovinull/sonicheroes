// Copies as much decoded data as possible from the sliding window to the output buffer (HYPOTHESIS:
// zlib inflate_flush), wrapping at the end of the window and updating the running check value.
// Returns r, with Z_BUF_ERROR turned into Z_OK when anything was copied.
#include "types.h"
#include "MSL_C/string.h"

#define Z_OK        0
#define Z_BUF_ERROR (-5)

typedef unsigned int (*CheckFunc8017B540)(
    unsigned int check, const unsigned char* buffer, unsigned int length);

// Fields used here (HYPOTHESIS: inflate_blocks_state layout).
struct InflateBlocks8017B540 {
	unsigned char pad0[0x28];
	unsigned char* window;     // 0x28
	unsigned char* end;        // 0x2C
	unsigned char* read;       // 0x30
	unsigned char* write;      // 0x34
	CheckFunc8017B540 checkfn; // 0x38
	unsigned int check;        // 0x3C
};

struct ZStream8017B540 {
	unsigned char pad0[0xC];
	unsigned char* nextOut; // 0xC
	unsigned int availOut;  // 0x10
	unsigned int totalOut;  // 0x14
	unsigned char pad18[0x30 - 0x18];
	unsigned int adler; // 0x30
};

extern "C" {
int fn_8017B540(InflateBlocks8017B540* s, ZStream8017B540* z, int r)
{
	unsigned int n;
	unsigned char* p;
	unsigned char* q;

	p = z->nextOut;
	q = s->read;
	n = (unsigned int)((q <= s->write ? s->write : s->end) - q);
	if (n > z->availOut) {
		n = z->availOut;
	}
	if (n && r == Z_BUF_ERROR) {
		r = Z_OK;
	}
	z->availOut -= n;
	z->totalOut += n;
	if (s->checkfn != 0) {
		z->adler = s->check = s->checkfn(s->check, q, n);
	}
	memcpy(p, q, n);
	p += n;
	q += n;
	if (q == s->end) {
		q = s->window;
		if (s->write == s->end) {
			s->write = s->window;
		}
		n = (unsigned int)(s->write - q);
		if (n > z->availOut) {
			n = z->availOut;
		}
		if (n && r == Z_BUF_ERROR) {
			r = Z_OK;
		}
		z->availOut -= n;
		z->totalOut += n;
		if (s->checkfn != 0) {
			z->adler = s->check = s->checkfn(s->check, q, n);
		}
		memcpy(p, q, n);
		p += n;
		q += n;
	}
	z->nextOut = p;
	s->read    = q;
	return r;
}
}
