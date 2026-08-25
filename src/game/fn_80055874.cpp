#include "types.h"

// Traversal, clipping, circle tests, layouts, and exception metadata match the
// retail unit. The remaining GC/1.3.2 delta is only floating-register choice.

struct Fn80055874Vec { f32 x; f32 y; f32 z; };
struct Fn80055874Result { u16 value; u16 padding; Fn80055874Result* previous; Fn80055874Result* next; };
struct Fn80055874Node {
    u16 value;
    u16 padding;
    u16 firstChild;
    u16 neighbours[4];
    u16 count;
    u8 padding2[8];
    u8 level;
    u8 padding3[7];
};
struct Fn80055874Grid {
    Fn80055874Node* root;
    u8 padding[16];
    u32* visited;
    u8 padding2[8];
    u32 visitedGroups;
    u8 padding3[48];
    f32 cellExtents[1];
};

extern "C" u32 lbl_80242B28[4];
extern "C" void fn_8005430C(Fn80055874Grid*, const Fn80055874Node*, Fn80055874Vec*);
extern "C" Fn80055874Result* fn_8005428C(Fn80055874Result*, u16);
extern "C" f64 __fabs(f64);

extern "C" Fn80055874Result* fn_80055874(Fn80055874Grid* grid, Fn80055874Result* result,
    Fn80055874Node* node, const Fn80055874Vec* point, f32 radius, const Fn80055874Vec* upper,
    const Fn80055874Vec* lower)
{
    u8 selection = 0;
    f32 extent = grid->cellExtents[node->level];
    Fn80055874Vec center;
    {
        u16 value = node->value;
        grid->visited[value >> 5] |= 1 << (value & 31);
        grid->visitedGroups |= 1 << (value >> 11);
    }
    fn_8005430C(grid, node, &center);

    if (node->firstChild != 0) {
        if (upper->x < center.x) selection = 0xA;
        else if (center.x < lower->x) selection = 5;
        if (upper->z < center.z) selection |= 0xC;
        else if (center.z < lower->z) selection |= 3;

        for (s32 index = 0; index < 4; index++) {
            s32 child = node->firstChild + index;
            u16 childIndex = child;
            if ((s32)(grid->visited[childIndex >> 5] & (1 << (childIndex & 31))) == 0 &&
                (s32)(selection & lbl_80242B28[index]) == 0) {
                result = fn_80055874(grid, result, &grid->root[child], point, radius, upper, lower);
            }
        }
    } else if (node->count != 0) {
        f32 leafExtent = grid->cellExtents[node->level];
        s32 region = 0;
        f32 deltaX;
        f32 deltaZ;
        deltaX = point->x - center.x;
        deltaZ = point->z - center.z;
        s32 intersects;

        if (leafExtent < deltaX) region = 1;
        else if (deltaX < -leafExtent) region = 2;
        if (leafExtent < deltaZ) region += 3;
        else if (deltaZ < -leafExtent) region += 6;

        switch (region) {
        case 0:
            intersects = true;
            break;
        case 1:
        case 2:
            intersects = (f32)__fabs(deltaX) <= leafExtent + radius;
            break;
        case 3:
        case 6:
            intersects = (f32)__fabs(deltaZ) <= leafExtent + radius;
            break;
        case 4:
        case 5:
        case 7:
        case 8:
            deltaX = (f32)__fabs(deltaX) - leafExtent;
            deltaZ = (f32)__fabs(deltaZ) - leafExtent;
            intersects = deltaX * deltaX + deltaZ * deltaZ <= radius * radius;
            break;
        default:
            intersects = false;
            break;
        }
        if (intersects) result = fn_8005428C(result, node->value);
    }

    for (s32 index = 0; index <= 3; index++) {
        u16 neighbour = node->neighbours[index];
        if ((s32)neighbour != 0 && (s32)(grid->visited[neighbour >> 5] & (1 << (neighbour & 31))) == 0) {
            switch (index) {
            case 0:
                if (upper->x < center.x + extent) continue;
                break;
            case 1:
                if (lower->x > center.x - extent) continue;
                break;
            case 2:
                if (upper->z < center.z + extent) continue;
                break;
            case 3:
                if (lower->z > center.z - extent) continue;
                break;
            }
            result = fn_80055874(grid, result, &grid->root[neighbour], point, radius, upper, lower);
        }
    }
    return result;
}
