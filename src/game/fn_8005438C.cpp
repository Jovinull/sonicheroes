#include "types.h"

// The field order and left-associated arithmetic below preserve the retail
// coordinate loads, floating-point live ranges, and bounding comparisons.
// Compiling this carved TU alone still creates a private u16 conversion bias
// and different exception-atom metadata; fix_fn_8005438c_object.py removes
// that split-only atom and restores the combined-TU linker metadata.

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

static inline Fn8005438CNode* fn_8005438CNodes(Fn8005438CGrid* grid)
{
	return grid->nodes;
}

extern "C" Fn8005438CNode* fn_8005438C(Fn8005438CGrid* grid, const Fn8005438CVec* point)
{
	Fn8005438CNode* nodes = fn_8005438CNodes(grid);
	u32 child;
	if (nodes == 0)
		return 0;
	Fn8005438CNode* node = nodes;
	while (node->childIndex != 0) {
		f32 scale;
		f32 cellSize;
		cellSize = grid->cellSizes[node->level];
		scale    = grid->scaleX * grid->scaleZ;
		f32 maxZ = (f32)node->zIndex * scale + cellSize + grid->baseZ;
		f32 maxX = (f32)node->xIndex * scale + cellSize + grid->baseX;
		child    = (point->x >= maxX) ? 1 : 0;
		if (point->z >= maxZ)
			child |= 2;
		node = &nodes[node->childIndex + child];
	}
	return node;
}
