// Builds the literal/length and distance Huffman trees of a dynamic block (HYPOTHESIS: zlib
// inflate_trees_dynamic) through fn_8017A2FC (huft_build) with a temporary 288-entry work area from
// the stream's allocator. On failure sets the stream message and returns the zlib status
// (Z_MEM_ERROR -4, Z_DATA_ERROR -3); returns Z_OK (0) on success.
//
// The original unit pools its messages in one .data block (lbl_8028D9A0) and its base/extra-bit
// tables in one .rodata block (lbl_8023C1E0); the retail code addresses both as base + offset.
// NonMatching: the retail prologue loads the stack-passed stream pointer before clearing hn and
// addressing the message pool; this source loads it after them (4 words differ, same
// instructions).
#include "types.h"

#define Z_OK         0
#define Z_DATA_ERROR (-3)
#define Z_MEM_ERROR  (-4)
#define Z_BUF_ERROR  (-5)

// Message offsets inside lbl_8028D9A0.
#define MSG_LITERAL_OVERSUBSCRIBED  0x4C
#define MSG_LITERAL_INCOMPLETE      0x70
#define MSG_DISTANCE_OVERSUBSCRIBED 0x90
#define MSG_DISTANCE_INCOMPLETE     0xB0
#define MSG_DISTANCE_EMPTY          0xCC
// Table offsets inside lbl_8023C1E0 (HYPOTHESIS: cplens, cplext, cpdist, cpdext).
#define TABLE_CPLENS 0x30
#define TABLE_CPLEXT 0xAC
#define TABLE_CPDIST 0x128
#define TABLE_CPDEXT 0x1A0

struct ZStream8017A940 {
	unsigned char pad0[0x18];
	char* msg; // 0x18
	void* state;
	void* (*zalloc)(void* opaque, unsigned int items, unsigned int size); // 0x20
	void (*zfree)(void* opaque, void* address);                           // 0x24
	void* opaque;                                                         // 0x28
};

extern "C" {
extern char lbl_8028D9A0[];
extern const unsigned char lbl_8023C1E0[];
int fn_8017A2FC(unsigned int* b, unsigned int n, unsigned int s, const unsigned int* d,
    const unsigned int* e, void** t, unsigned int* m, void* hp, unsigned int* hn, unsigned int* v);

int fn_8017A940(unsigned int nl, unsigned int nd, unsigned int* c, unsigned int* bl,
    unsigned int* bd, void** tl, void** td, void* hp, ZStream8017A940* z)
{
	int r;
	unsigned int hn = 0;
	unsigned int* v;
	char* messages            = lbl_8028D9A0;
	const unsigned char* base = lbl_8023C1E0;
	if ((v = (unsigned int*)z->zalloc(z->opaque, 288, sizeof(unsigned int))) == 0) {
		return Z_MEM_ERROR;
	}
	r = fn_8017A2FC(c, nl, 257, (const unsigned int*)(base + TABLE_CPLENS),
	    (const unsigned int*)(base + TABLE_CPLEXT), tl, bl, hp, &hn, v);
	if (r != Z_OK || *bl == 0) {
		if (r == Z_DATA_ERROR) {
			z->msg = messages + MSG_LITERAL_OVERSUBSCRIBED;
		} else if (r != Z_MEM_ERROR) {
			z->msg = messages + MSG_LITERAL_INCOMPLETE;
			r      = Z_DATA_ERROR;
		}
		z->zfree(z->opaque, v);
		return r;
	}
	r = fn_8017A2FC(c + nl, nd, 0, (const unsigned int*)(base + TABLE_CPDIST),
	    (const unsigned int*)(base + TABLE_CPDEXT), td, bd, hp, &hn, v);
	if (r != Z_OK || (*bd == 0 && nl > 257)) {
		if (r == Z_DATA_ERROR) {
			z->msg = messages + MSG_DISTANCE_OVERSUBSCRIBED;
		} else if (r == Z_BUF_ERROR) {
			z->msg = messages + MSG_DISTANCE_INCOMPLETE;
			r      = Z_DATA_ERROR;
		} else if (r != Z_MEM_ERROR) {
			z->msg = messages + MSG_DISTANCE_EMPTY;
			r      = Z_DATA_ERROR;
		}
		z->zfree(z->opaque, v);
		return r;
	}
	z->zfree(z->opaque, v);
	return Z_OK;
}
}
