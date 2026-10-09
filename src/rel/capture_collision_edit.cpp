// TObjCaptureCollision's EditOnChange: the number in the placement's
// parameters is held between the module's two limits, through the
// nVariable::Limit template the PS2 build names (Limit<i>), which returns a
// reference to the value or to the limit it crossed. The class is shared
// through capture_collision_class.inc.

#define CAPTURE_COLLISION_CTOR inline
#include "src/rel/capture_collision_class.inc"

namespace nVariable
{

template <class T> inline const T& Limit(const T& value, const T& min, const T& max)
{
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}
	return value;
}

} // namespace nVariable

extern "C" s32 captureCollisionMin;
extern "C" s32 captureCollisionMax;

void TObjCaptureCollision::EditOnChange(SETDATA_PARAM* data)
{
	s32* value = data->setBuffer;

	*value = nVariable::Limit(*value, captureCollisionMin, captureCollisionMax);
}
