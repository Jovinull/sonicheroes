#include "types.h"

struct Fn800D67D4Vec {
    f32 x;
    f32 y;
    f32 z;
};

extern "C" double floor(double);
extern "C" void fn_801991B4(Fn800D67D4Vec*);

extern "C" f32 fn_800D67D4(f32 value)
{
    if (value < 0.0f) {
        return -(f32)floor(-value);
    }
    return (f32)floor(value);
}

extern "C" void fn_800D6818(const Fn800D67D4Vec* first, const Fn800D67D4Vec* second,
    Fn800D67D4Vec* result)
{
    result->x = first->y * second->z - first->z * second->y;
    result->y = first->z * second->x - first->x * second->z;
    result->z = first->x * second->y - first->y * second->x;
    fn_801991B4(result);
}
