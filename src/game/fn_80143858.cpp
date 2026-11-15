// Creates a block holding five optional arrays after a 0x8C-byte header (HYPOTHESIS: a plugin
// 0x120 mesh/definition constructor): the size sums each array (element sizes 0x18, 0x64, 0x14,
// 0x3C and 0x28) rounded up to 4 bytes, the block is allocated (error 0x80000013 of plugin 0x120
// on failure), cleared and initialised by fn_80146E24 with 6, the five counts are stored twice
// (+0x34 and +0x39), and each non-empty array gets its pointer (+0x70 to +0x80) in the order
// 0x3C, 0x18, 0x28, 0x14, 0x64. Returns the block, or null. Names are inferred from this function.
// NonMatching: registers and instruction set match; retail schedules each multiply next to its
// rounding step and loads the allocator first, while this source computes the products earlier
// (22 words). Interleaved and nested size expressions give the same schedule.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

#define ALIGN4_80143858(x) (((x) + 3) & ~3)
#define PLUGIN_ID_80143858 0x120

struct Counts80143858 {
	u8 b; // 0x0: 0x18-byte elements
	u8 a; // 0x1: 0x64-byte elements
	u8 c; // 0x2: 0x3C-byte elements
	u8 d; // 0x3: 0x14-byte elements
	u8 e; // 0x4: 0x28-byte elements
};

struct Block80143858 {
	u8 pad0[0x34];
	Counts80143858 counts;  // 0x34
	Counts80143858 counts2; // 0x39
	u8 pad3E[0x70 - 0x3E];
	u8* arrayC; // 0x70
	u8* arrayB; // 0x74
	u8* arrayE; // 0x78
	u8* arrayD; // 0x7C
	u8* arrayA; // 0x80
	u8 pad84[0x8C - 0x84];
};

extern "C" {
void fn_80146E24(Block80143858* block, s32 value);

Block80143858* fn_80143858(u32 a, u32 b, u32 c, u32 d, u32 e)
{
	u32 sizeC;
	u32 sizeB;
	u32 sizeE;
	u32 sizeD;
	u32 size;
	Block80143858* block;
	u8* data;

	sizeB = b * 0x18;
	sizeD = d * 0x14;
	sizeC = c * 0x3C;
	sizeE = e * 0x28;

	size  = ALIGN4_80143858(sizeof(Block80143858) + sizeB);
	size  = ALIGN4_80143858(size + a * 0x64);
	size  = ALIGN4_80143858(size + sizeD);
	size  = ALIGN4_80143858(size + sizeC);
	size  = ALIGN4_80143858(size + sizeE);
	block = (Block80143858*)lbl_8042C9A4->rwmalloc(size);
	if (block == 0) {
		RwError error;
		error.pluginID  = PLUGIN_ID_80143858;
		error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, size);
		fn_80193FE8(&error);
		return 0;
	}
	memset(block, 0, size);
	fn_80146E24(block, 6);

	block->counts.a  = a;
	block->counts.b  = b;
	block->counts.d  = d;
	block->counts.c  = c;
	block->counts.e  = e;
	block->counts2.a = block->counts.a;
	block->counts2.b = block->counts.b;
	block->counts2.d = block->counts.d;
	block->counts2.c = block->counts.c;
	block->counts2.e = block->counts.e;

	data = (u8*)(block + 1);
	if (c != 0) {
		block->arrayC = data;
		data += sizeC;
	}
	if (b != 0) {
		block->arrayB = data;
		data += sizeB;
	}
	if (e != 0) {
		block->arrayE = data;
		data += sizeE;
	}
	if (d != 0) {
		block->arrayD = data;
		data += sizeD;
	}
	if (a != 0) {
		block->arrayA = data;
	}
	return block;
}
}
