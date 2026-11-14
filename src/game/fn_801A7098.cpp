// Returns the palette index stored in the leaf reached by walking a palette-quantizer tree
// `depth` levels down, taking the child selected by the next 4-bit digit of `key` at each
// level (HYPOTHESIS: RenderWare palquant octree lookup). The retail code is the recursion
// expanded eight levels into itself by the compiler's inliner.
#include "game/rw_palquant.h"

extern "C" {
u8 fn_801A7098(RwPalQuantNode* node, u32 key, s32 depth)
{
	if (depth == 0) {
		return node->leaf.paletteIndex;
	}
	return fn_801A7098(node->child[key & 0xF], key >> 4, depth - 1);
}
}
