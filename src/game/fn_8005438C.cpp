#include "types.h"

// Spatial-list traversal split from the original game translation unit.

struct Fn8005438CVec {
	f32 x;
	f32 y;
	f32 z;
};
struct Fn8005438CNode {
	u8 padding[4];
	u16 childIndex;
	u8 padding2[0xE];
	u16 xIndex;
	u16 zIndex;
	u8 level;
	u8 padding3[7];
};
struct Fn8005438CGrid {
	Fn8005438CNode* nodes;
	u8 padding[0x2C];
	f32 baseX;
	f32 padding2;
	f32 baseZ;
	f32 scaleX;
	f32 padding3;
	f32 scaleZ;
	u8 padding4[0xC];
	f32 cellSizes[1];
};

extern "C" const f64 lbl_8042D3A0;
// Retained only until the post-compile step retargets MWCC's private conversion
// bias atom to the shared symbol used by the original translation unit.
extern "C" const f64* fn_8005438C_bias_anchor = &lbl_8042D3A0;

extern "C" Fn8005438CNode* fn_8005438C(Fn8005438CGrid* grid, const Fn8005438CVec* point)
{
	Fn8005438CNode* nodes = grid->nodes;
	if (nodes == 0)
		return 0;
	u16 childIndex;
	Fn8005438CNode* node = nodes;
	while ((childIndex = node->childIndex) != 0) {
		f32 scale;
		f32 cellSize = grid->cellSizes[node->level];
		scale        = grid->scaleX * grid->scaleZ;
		f32 maxZ     = grid->baseZ + ((f32)node->zIndex * scale + cellSize);
		f32 maxX     = grid->baseX + ((f32)node->xIndex * scale + cellSize);
		u32 child    = (point->x >= maxX) ? 1 : 0;
		if (point->z >= maxZ)
			child |= 2;
		node = &nodes[childIndex + child];
	}
	return node;
}
