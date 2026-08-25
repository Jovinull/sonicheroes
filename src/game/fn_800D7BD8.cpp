#include "types.h"

struct Fn800D7BD8Vec {
    f32 x;
    f32 y;
    f32 z;
};

struct Fn800D7BD8Segment {
    Fn800D7BD8Vec origin;
    Fn800D7BD8Vec direction;
};

extern "C" f32 sqrtf(f32);
extern "C" f32 fn_800D7044(const Fn800D7BD8Vec*, const Fn800D7BD8Segment*, Fn800D7BD8Vec*);

extern "C" f32 fn_800D7BD8(const Fn800D7BD8Vec* point, const Fn800D7BD8Vec* first,
    const Fn800D7BD8Vec* second, Fn800D7BD8Vec* closest)
{
    f32 x = point->x - first->x;
    f32 y = point->y - first->y;
    f32 z = point->z - first->z;
    f32 directionX = second->x - first->x;
    f32 directionY = second->y - first->y;
    f32 directionZ = second->z - first->z;

    if (x * directionX + y * directionY + z * directionZ < 0.0f) {
        if (closest != 0) {
            *closest = *first;
        }
        f32 distanceSquared = x * x + y * y + z * z;
        if (distanceSquared <= 0.025f) {
            return 0.0f;
        }
        return sqrtf(distanceSquared);
    }

    x = second->x - point->x;
    y = second->y - point->y;
    z = second->z - point->z;
    if (directionX * x + directionY * y + directionZ * z < 0.0f) {
        if (closest != 0) {
            *closest = *second;
        }
        f32 distanceSquared = x * x + y * y + z * z;
        if (distanceSquared <= 0.025f) {
            return 0.0f;
        }
        return sqrtf(distanceSquared);
    }

    Fn800D7BD8Segment segment;
    segment.origin = *first;
    segment.direction.x = directionX;
    segment.direction.y = directionY;
    segment.direction.z = directionZ;
    return fn_800D7044(point, &segment, closest);
}
