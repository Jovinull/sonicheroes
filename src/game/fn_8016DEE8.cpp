// Opens the 2D toolkit state lbl_803EC968 (HYPOTHESIS: Rt2dOpen): creates the 0x138-byte and
// 0xC-byte free lists (in place at lbl_803EC920 and lbl_803EC944), sets the font search path
// (fn_8016E054), builds the index table of 16 quads (two triangles each) at +0x80, clears the
// lists and counters at +0x1D0, +0xA0C and +0xA10 and installs fn_8016E32C (fn_8016E0AC).
// Returns 1. Names are inferred from this function only.
// NonMatching: retail stores the first free list before setting up the second call's arguments
// and indexes the quad table from r4; this source orders those differently and needs one more
// instruction (81 words). Index-loop forms and C mode do not reproduce it.
#include "game/rw_engine.h"

#define RT2D_NUM_BATCH_QUADS 16

struct Rt2dGlobals8016DEE8 {
	u8 pad0[0x80];
	u16 quadIndices[RT2D_NUM_BATCH_QUADS * 6]; // 0x80
	u8 pad140[0x148 - 0x140];
	RwFreeList* freeList148; // 0x148
	u8 pad14C[0x1CC - 0x14C];
	RwFreeList* freeList1CC; // 0x1CC
	void* list1D0;           // 0x1D0
	u8 pad1D4[0xA0C - 0x1D4];
	s32 valueA0C; // 0xA0C
	s32 valueA10; // 0xA10
};

extern "C" {
extern Rt2dGlobals8016DEE8 lbl_803EC968;
extern u8 lbl_803EC920[];
extern u8 lbl_803EC944[];
extern s32 lbl_8042BD74;
extern s32 lbl_8042BD78;
extern s32 lbl_8042BD7C;
extern s32 lbl_8042BD80;
extern char lbl_8042BD84[];
// HYPOTHESIS: RwFreeListCreate(entrySize, entriesPerBlock, alignment, numBlocks, inPlace).
RwFreeList* fn_801966CC(
    s32 entrySize, s32 entriesPerBlock, s32 alignment, s32 numBlocks, void* inPlace);
void fn_8016E054(const char* path);
void fn_8016E0AC(void* callback);
void fn_8016E32C(void);

s32 fn_8016DEE8(void)
{
	u16* index;
	s32 i;

	lbl_803EC968.freeList148 = fn_801966CC(0x138, lbl_8042BD74, 4, lbl_8042BD78, lbl_803EC920);
	lbl_803EC968.freeList1CC = fn_801966CC(0xC, lbl_8042BD7C, 4, lbl_8042BD80, lbl_803EC944);
	fn_8016E054(lbl_8042BD84);

	index = lbl_803EC968.quadIndices;
	for (i = 0; i < RT2D_NUM_BATCH_QUADS * 4; i += 4) {
		u16 base = i;
		index[0] = i;
		index[1] = base + 2;
		index[2] = base + 3;
		index[3] = i;
		index[4] = base + 3;
		index[5] = base + 1;
		index += 6;
	}

	lbl_803EC968.list1D0  = 0;
	lbl_803EC968.valueA0C = 0;
	lbl_803EC968.valueA10 = 0;
	fn_8016E0AC((void*)fn_8016E32C);
	return 1;
}
}
