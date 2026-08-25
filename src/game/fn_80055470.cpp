#include "types.h"

// The recursive traversal, control flow, data layout, and exception metadata
// are reconstructed exactly. GC/1.3.2 retains only floating-register choices,
// so this unit remains NonMatching despite matching object and data sizes.

struct Fn80055470Vec { f32 x; f32 y; f32 z; };
struct Fn80055470Result { u16 value; u16 padding; Fn80055470Result* previous; Fn80055470Result* next; };
struct Fn80055470Node {
    u16 value;
    u8 padding[2];
    u16 firstChild;
    u8 padding2[8];
    u16 count;
    u8 padding3[8];
    u8 level;
    u8 padding4[7];
};
struct Fn80055470Grid { Fn80055470Node* root; u8 padding[80]; f32 cellExtents[1]; };

extern "C" u32 lbl_80242B28[4];
extern "C" void fn_8005430C(Fn80055470Grid*, const Fn80055470Node*, Fn80055470Vec*);
extern "C" Fn80055470Result* fn_8005428C(Fn80055470Result*, u16);

extern "C" Fn80055470Result* fn_80055470(Fn80055470Grid* grid, Fn80055470Result* result,
    Fn80055470Node* node, const Fn80055470Vec* upper, const Fn80055470Vec* lower)
{
    f32 extent = grid->cellExtents[node->level];
    f32 maxX;
    f32 maxZ;
    f32 minX;
    f32 minZ;
    Fn80055470Vec center;
    fn_8005430C(grid, node, &center);
    maxX = center.x + extent;
    maxZ = center.z + extent;
    minX = center.x - extent;
    minZ = center.z - extent;

    if (lower->x <= minX && maxX <= upper->x && lower->z <= minZ && maxZ <= upper->z) {
        if (node->count != 0) result = fn_8005428C(result, node->value);
        return result;
    }
    if (node->firstChild != 0) {
        u8 selection = 0;
        if (upper->x < center.x) selection = 0xA;
        else if (center.x < lower->x) selection = 5;
        if (upper->z < center.z) selection |= 0xC;
        else if (center.z < lower->z) selection |= 3;
        for (s32 index = 0; index < 4; index++) {
            if ((s32)(selection & lbl_80242B28[index]) == 0)
                result = fn_80055470(grid, result, &grid->root[node->firstChild + index], upper, lower);
        }
    } else if (node->count != 0) {
        if (((lower->x <= minX && minX <= upper->x) || (minX <= lower->x && lower->x <= maxX)) &&
            ((lower->z <= minZ && minZ <= upper->z) || (minZ <= lower->z && lower->z <= maxZ)))
            result = fn_8005428C(result, node->value);
    }
    return result;
}
