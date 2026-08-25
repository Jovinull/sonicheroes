#include "types.h"

// The control flow, data layout, arithmetic, exception metadata, and source
// range are exact. GC/1.3.2 retains a register-allocation-only residual:
// root/child use r7/r8 and the two live float values use f5/f4 in retail,
// while the independently reconstructed source swaps each pair.

struct Fn8005438CVec { f32 x; f32 y; f32 z; };
struct Fn8005438CNode {
    u8 padding[4]; u16 childIndex; u8 padding2[0xE]; u16 zIndex; u16 xIndex; u8 level; u8 padding3[7];
};
struct Fn8005438CGrid {
    Fn8005438CNode* nodes; u8 padding[0x2C]; f32 baseZ; f32 padding2; f32 baseX; f32 scaleX;
    f32 padding3; f32 scaleZ; u8 padding4[0xC]; f32 cellSizes[1];
};

extern "C" Fn8005438CNode* fn_8005438C(Fn8005438CGrid* grid, const Fn8005438CVec* point)
{
    Fn8005438CNode* nodes = grid->nodes;
    if (nodes == 0) return 0;
    Fn8005438CNode* node = nodes;
    while (node->childIndex != 0) {
        f32 cellSize = grid->cellSizes[node->level];
        f32 scale = grid->scaleX * grid->scaleZ;
        f32 maxZ = grid->baseZ + (f32)node->zIndex * scale + cellSize;
        f32 maxX = grid->baseX + (f32)node->xIndex * scale + cellSize;
        u32 child = (point->x >= maxX) ? 1 : 0;
        if (point->z >= maxZ) child |= 2;
        node = &nodes[node->childIndex + child];
    }
    return node;
}
