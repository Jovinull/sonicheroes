// Returns the palette index stored in the leaf reached by walking a palette-quantizer tree
// `depth` levels down, taking the child selected by the next 4-bit digit of `key` at each
// level (HYPOTHESIS: RenderWare palquant octree lookup). The retail code is the recursion
// expanded eight levels into itself by the compiler's inliner.
#include "types.h"

// Palette-quantizer tree node (HYPOTHESIS). Interior nodes use the child table; leaves keep
// their palette index at 0x18, overlapping it.
union RwPalQuantNode {
	RwPalQuantNode* child[16];
	struct {
		u8 pad0[0x18];
		u8 paletteIndex; // 0x18
	} leaf;
};

extern "C" {
u8 fn_801A7098(RwPalQuantNode* node, u32 key, s32 depth)
{
	if (depth == 0) {
		return node->leaf.paletteIndex;
	}
	return fn_801A7098(node->child[key & 0xF], key >> 4, depth - 1);
}
}
