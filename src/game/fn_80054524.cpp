#include "types.h"

struct Fn80054524Allocator { u8 padding[0x140]; void* (*allocate)(u32, u32); };

struct Fn80054524Definition {
    void* descriptor;
    u32 word0;
    u32 word1;
    u32 word2;
    f32 originX;
    f32 originY;
    f32 originZ;
    f32 extent;
    u16 depthX;
    u16 depthY;
    u16 depthZ;
    u16 depthW;
};

struct Fn80054524Grid {
    u32 word0;
    u32 word1;
    u32 word2;
    void* xNodes;
    s32 xNodeCount;
    void* zNodes;
    s32 zNodeCount;
    u32 xCursor;
    u32 zCursor;
    f32 originX;
    f32 originY;
    f32 originZ;
    f32 minX;
    f32 padding4;
    f32 minZ;
    f32 extent;
    s32 depthX;
    f32 inverseWidth;
    s32 depthY;
    s32 depthZ;
    s32 depthW;
    f32 cellExtents[1];
    u8 padding[0x3C];
    void* definitionData;
    u8 padding2[0xEC];
    const Fn80054524Definition* definition;
    s32 initialized;
};

extern "C" Fn80054524Allocator* lbl_8042C9A4;
extern "C" f32 lbl_8042D3A8;
extern "C" f32 lbl_8042D3AC;
extern "C" f64 lbl_8042D3B0;

extern "C" Fn80054524Grid* fn_80054524(Fn80054524Grid* grid, const Fn80054524Definition* definition)
{
    grid->definitionData = definition->descriptor;
    grid->word0 = definition->word0;
    grid->word1 = definition->word1;
    grid->word2 = definition->word2;
    grid->originX = definition->originX;
    grid->originY = definition->originY;
    grid->originZ = definition->originZ;
    grid->extent = definition->extent;
    grid->depthX = definition->depthX;
    grid->depthY = definition->depthY;
    grid->depthZ = definition->depthZ;
    grid->depthW = definition->depthW;
    ((u32*)&grid->extent)[0] &= ~0xFFF;
    f32 half = lbl_8042D3A8;
    grid->cellExtents[0] = half * grid->extent;
    grid->minX = grid->originX - grid->cellExtents[0];
    grid->minZ = grid->originZ - grid->cellExtents[0];
    grid->inverseWidth = lbl_8042D3AC / (f32)(1 << grid->depthX);
    for (s32 index = 1; index <= grid->depthX; index++) {
        grid->cellExtents[index] = half * grid->cellExtents[index - 1];
    }
    grid->xNodeCount = grid->depthY / 32 + 1;
    void* xNodes = lbl_8042C9A4->allocate(4, grid->xNodeCount);
    grid->xNodes = xNodes;
    if (xNodes == 0) return grid;
    grid->xCursor = 0;
    grid->zNodeCount = grid->depthW / 32 + 1;
    void* zNodes = lbl_8042C9A4->allocate(4, grid->zNodeCount);
    grid->zNodes = zNodes;
    if (zNodes == 0) return grid;
    grid->zCursor = 0;
    grid->definition = definition;
    grid->initialized = 1;
    return grid;
}
