// Assigns palette entries to the leaves of a colour subtree (HYPOTHESIS: the palette quantizer's
// palette fill): walks the 16 children of every interior node down to depth 0 and, for each leaf
// met, writes its mean colour (the RGBA sums divided by its weight, or black for an empty leaf)
// into palette[index], records the index in the leaf and moves to the next entry. Returns the
// next free palette index. The compiler inlines the recursion two levels deep.
// NonMatching: retail keeps the weight in f2 and the scale in f1, this source the reverse (28
// words, same instructions). An if/else scale, a weight local and a scale-based compare move the
// constant load or add instructions.
#include "game/rw_palquant.h"

// Leaf statistics (HYPOTHESIS: weight and weighted RGBA sums; overlaps the child table).
struct RwPalQuantLeaf801A68E4 {
	f32 weight; // 0x0
	f32 red;    // 0x4
	f32 green;  // 0x8
	f32 blue;   // 0xC
	f32 alpha;  // 0x10
	u8 pad14[0x18 - 0x14];
	u8 paletteIndex; // 0x18
};

extern "C" {
// .sdata2 constants 0.0f and 1.0f (HYPOTHESIS).
extern f32 lbl_8042F750;
extern f32 lbl_8042F760;

s32 fn_801A68E4(RwPalQuantNode* node, RwRGBA* palette, s32 index, s32 depth)
{
	if (node != 0) {
		if (depth > 0) {
			s32 i;
			for (i = 0; i < 16; i++) {
				index = fn_801A68E4(node->child[i], palette, index, depth - 1);
			}
		} else {
			RwPalQuantLeaf801A68E4* leaf = (RwPalQuantLeaf801A68E4*)node;
			f32 scale = (leaf->weight > lbl_8042F750) ? lbl_8042F760 / leaf->weight : lbl_8042F750;
			palette[index].red   = leaf->red * scale;
			palette[index].green = leaf->green * scale;
			palette[index].blue  = leaf->blue * scale;
			palette[index].alpha = leaf->alpha * scale;
			leaf->paletteIndex   = index++;
		}
	}
	return index;
}
}
