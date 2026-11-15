// Initialises a palette quantizer (HYPOTHESIS: RenderWare _rwPalQuantInit). Fills the bit-spread
// table at lbl_803ED718, which maps each value below 1 << depth (lbl_8042BE60) to the word holding
// bit j of the value in nibble depth - 1 - j, allocates the two 0x100-entry work buffers (8 and 4
// bytes per entry), creates the tree-node free list and an empty root node. Returns 1.
#include "game/rw_palquant.h"

#define PAL_QUANT_NODE_SIZE       0x40
#define PAL_QUANT_NODES_PER_BLOCK 0x40

extern "C" {
// Bit-spread table indexed by a depth-bit value (HYPOTHESIS: splice).
extern u32 lbl_803ED718[];
// HYPOTHESIS: RwFreeListCreate(entrySize, entriesPerBlock, alignment).
RwFreeList* RwFreeListCreate(s32 entrySize, s32 entriesPerBlock, s32 alignment);

s32 fn_801A75BC(RwPalQuant* quant)
{
	s32 last;
	RwPalQuantNode* root;
	s32 depth;
	s32 i;
	s32 j;
	s32 count;

	depth = lbl_8042BE60;
	last  = depth - 1;
	count = 1 << depth;

	for (i = 0; i < count; i++) {
		u32 mask = 0;
		for (j = 0; j < depth; j++) {
			mask |= (i & (1 << j)) ? (1 << ((last - j) * 4)) : 0;
		}
		lbl_803ED718[i] = mask;
	}

	quant->buffer0      = lbl_8042C9A4->rwcalloc(8, 0x100);
	quant->buffer4      = lbl_8042C9A4->rwcalloc(4, 0x100);
	quant->nodeFreeList = RwFreeListCreate(PAL_QUANT_NODE_SIZE, PAL_QUANT_NODES_PER_BLOCK, 4);
	quant->root         = (RwPalQuantNode*)lbl_8042C9A4->freeListAlloc(quant->nodeFreeList);
	root                = quant->root;
	for (i = 0; i < 16; i++) {
		root->child[i] = 0;
	}
	return 1;
}
}
