// TObjWarp's EditOnChange: the radius in the placement's parameters is held
// to at least 1 and becomes the collision shape's radius, and the collision
// range is recomputed. The 1 is a literal: the unit owns the constant, which
// nothing else uses, and a load from a named constant swaps the compare's
// registers. The class is shared through warp_class.inc.

#define WARP_CTOR inline
#include "src/rel/warp_class.inc"

struct WarpParam {
	f32 radius; // 0x00
};

void TObjWarp::EditOnChange(SETDATA_PARAM* data)
{
	WarpParam* param = (WarpParam*)data->setBuffer;

	if (param->radius < 1.0f) {
		param->radius = 1.0f;
	}
	info->a = param->radius;
	CalcRange();
}
