#include "types.h"

// Converts the angle between two normalized vectors to the engine's unsigned
// 16-bit turn representation. The optional orientation vector selects the
// winding direction.

struct Fn800D7920Vec { f32 x; f32 y; f32 z; };

extern "C" double acos(double);

extern "C" s32 fn_800D7920(const Fn800D7920Vec* first, const Fn800D7920Vec* second,
    const Fn800D7920Vec* orientation)
{
    f32 dot = first->z * second->z + first->x * second->x + first->y * second->y;
    if (dot <= -1.0f) return 0x8000;
    if (dot >= 1.0f) return 0;

    s32 angle = (s32)(10430.381f * (f32)acos(dot));
    Fn800D7920Vec cross;
    cross.x = first->y * second->z - first->z * second->y;
    cross.y = first->z * second->x - first->x * second->z;
    cross.z = first->x * second->y - first->y * second->x;
    if (orientation != 0 &&
        orientation->z * cross.z + orientation->x * cross.x + orientation->y * cross.y < 0.0f) {
        return 0x10000 - angle;
    }
    return angle;
}
