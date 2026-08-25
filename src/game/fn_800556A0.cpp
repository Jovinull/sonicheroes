#include "types.h"

struct Fn800556A0Vec { f32 x; f32 y; f32 z; };
struct Fn800556A0Node { u8 padding[4]; u16 firstChild; u8 padding2[26]; };
struct Fn800556A0Grid {
    Fn800556A0Node* root;
    u8 padding[0x20];
    f32 centerX;
    u8 padding2[4];
    f32 centerZ;
    u8 padding3[12];
    f32 extent;
};

extern "C" volatile f32 lbl_8042D3C0;
extern "C" f32 lbl_8042D3C8;
extern "C" u32 lbl_80242B28[4];
extern "C" void* fn_80055470(Fn800556A0Grid*, void*, Fn800556A0Node*, const Fn800556A0Vec*, const Fn800556A0Vec*);

extern "C" void* fn_800556A0(Fn800556A0Grid* grid, const Fn800556A0Vec* point,
    const Fn800556A0Vec* direction, f32 radius)
{
    Fn800556A0Vec upper;
    Fn800556A0Vec lower;
    u8 selection = 0;
    f32 halfExtent = lbl_8042D3C8 * grid->extent;
    void* result = 0;

    if (direction->x >= lbl_8042D3C0) {
        upper.x = point->x + direction->x + radius;
        lower.x = point->x - radius;
    } else {
        upper.x = point->x + radius;
        lower.x = point->x + direction->x - radius;
    }
    if (direction->z >= lbl_8042D3C0) {
        upper.z = point->z + direction->z + radius;
        lower.z = point->z - radius;
    } else {
        upper.z = point->z + radius;
        lower.z = point->z + direction->z - radius;
    }

    if (upper.x < grid->centerX - halfExtent || grid->centerX + halfExtent < lower.x ||
        upper.z < grid->centerZ - halfExtent || grid->centerZ + halfExtent < lower.z) {
        return 0;
    }

    if (upper.x < grid->centerX) selection = 0xA;
    else if (grid->centerX < lower.x) selection = 5;
    if (upper.z < grid->centerZ) selection |= 0xC;
    else if (grid->centerZ < lower.z) selection |= 3;

    for (s32 index = 0; index < 4; index++) {
        if ((s32)(selection & lbl_80242B28[index]) == 0) {
            result = fn_80055470(grid, result, &grid->root[grid->root->firstChild + index], &upper, &lower);
        }
    }
    return result;
}
