#include "types.h"

// Computes the oriented angle between two directions after projecting both on
// the plane normal to `planeNormal`.  A degenerate projected direction is
// reported as -1; the returned angle uses the engine's unsigned 16-bit turn
// convention.

struct Fn800D75CCVec { f32 x; f32 y; f32 z; };

extern "C" void fn_801990E0(Fn800D75CCVec*, Fn800D75CCVec*);
extern "C" double acos(double);

static f32 fn_800D75CCDot(const Fn800D75CCVec& left, const Fn800D75CCVec& right)
{
    return left.z * right.z + left.x * right.x + left.y * right.y;
}

static Fn800D75CCVec fn_800D75CCProject(const Fn800D75CCVec& value, const Fn800D75CCVec& planeNormal)
{
    f32 lengthSq = fn_800D75CCDot(planeNormal, planeNormal);
    f32 scale = -fn_800D75CCDot(planeNormal, value) / lengthSq;
    Fn800D75CCVec result;
    result.x = value.x + planeNormal.x * scale;
    result.y = value.y + planeNormal.y * scale;
    result.z = value.z + planeNormal.z * scale;
    return result;
}

extern "C" s32 fn_800D75CC(const Fn800D75CCVec* first, const Fn800D75CCVec* second,
    const Fn800D75CCVec* planeNormal)
{
    Fn800D75CCVec projectedFirst = fn_800D75CCProject(*first, *planeNormal);
    Fn800D75CCVec projectedSecond = fn_800D75CCProject(*second, *planeNormal);

    if (fn_800D75CCDot(projectedFirst, projectedFirst) <= 0.0001f ||
        fn_800D75CCDot(projectedSecond, projectedSecond) <= 0.0001f) {
        return -1;
    }

    fn_801990E0(&projectedFirst, &projectedFirst);
    fn_801990E0(&projectedSecond, &projectedSecond);

    f32 dot = fn_800D75CCDot(projectedFirst, projectedSecond);
    if (dot <= -1.0f) return 0x8000;
    if (dot >= 1.0f) return 0;

    s32 angle = (s32)(10430.381f * (f32)acos(dot));
    Fn800D75CCVec cross;
    cross.x = projectedFirst.y * projectedSecond.z - projectedFirst.z * projectedSecond.y;
    cross.y = projectedFirst.z * projectedSecond.x - projectedFirst.x * projectedSecond.z;
    cross.z = projectedFirst.x * projectedSecond.y - projectedFirst.y * projectedSecond.x;
    if (fn_800D75CCDot(*planeNormal, cross) > 0.0f) return 0x10000 - angle;
    return angle;
}
