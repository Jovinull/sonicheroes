// Assigns a palette index to every colour-tree leaf inside a colour box (HYPOTHESIS: the palette
// quantizer's box assignment). The node covers the cube at origin with side 1 << depth; nodes
// outside the box are skipped, a depth-0 node fully inside it takes the index, and any other node
// recurses into its 16 children (one bit of each RGBA offset per child index).
// NonMatching: retail interleaves each child-origin byte (load, shift, add, store) with the next
// bit extraction, while this source's schedule extracts all four bits first (23 words, same
// instructions). A shift local, an outer origin buffer, an unsigned index and an RwRGBA origin
// do not change it.
#include "game/rw_palquant.h"

// Colour box: inclusive low corner and exclusive high corner, RGBA.
struct RwPalQuantBox801A5B1C {
	u8 lo[4]; // 0x0
	u8 hi[4]; // 0x4
};

extern "C" {
void fn_801A5B1C(
    RwPalQuantNode* node, const u8* origin, s32 depth, const RwPalQuantBox801A5B1C* box, u8 index)
{
	s32 size;
	s32 d0, d1, d2, d3;
	s32 e0, e1, e2, e3;

	if (node == 0) {
		return;
	}
	size = 1 << depth;
	d0   = origin[0] - box->hi[0];
	d1   = origin[1] - box->hi[1];
	d2   = origin[2] - box->hi[2];
	d3   = origin[3] - box->hi[3];
	if (!(d0 < 0 && d1 < 0 && d2 < 0 && d3 < 0)) {
		return;
	}
	e0 = box->lo[0] - origin[0];
	e1 = box->lo[1] - origin[1];
	e2 = box->lo[2] - origin[2];
	e3 = box->lo[3] - origin[3];
	if (!(e0 < size && e1 < size && e2 < size && e3 < size)) {
		return;
	}
	if (d0 <= -size && d1 <= -size && d2 <= -size && d3 <= -size && e0 <= 0 && e1 <= 0 && e2 <= 0
	    && e3 <= 0 && depth == 0) {
		node->leaf.paletteIndex = index;
	} else {
		s32 i;
		for (i = 0; i < 16; i++) {
			u8 childOrigin[4];
			childOrigin[0] = origin[0] + (((i >> 3) & 1) << (depth - 1));
			childOrigin[1] = origin[1] + (((i >> 2) & 1) << (depth - 1));
			childOrigin[2] = origin[2] + (((i >> 1) & 1) << (depth - 1));
			childOrigin[3] = origin[3] + ((i & 1) << (depth - 1));
			fn_801A5B1C(node->child[i], childOrigin, depth - 1, box, index);
		}
	}
}
}
