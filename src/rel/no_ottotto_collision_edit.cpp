// TObjSetNoOttottoCollision's EditOnChange: the shape number in the
// placement's parameters is held to 0 or 1 and, if the collision block has
// shapes, they are freed and rebuilt from the module's shape of that number
// with the parameters' sizes. The class is shared through
// no_ottotto_collision_class.inc.

#define NO_OTTOTTO_COLLISION_CTOR inline
#include "src/rel/no_ottotto_collision_class.inc"

void TObjSetNoOttottoCollision::EditOnChange(SETDATA_PARAM* data)
{
	NoOttottoParam* param = (NoOttottoParam*)data->setBuffer;

	if (param->shape < 0) {
		param->shape = 0;
	}
	if (param->shape > 1) {
		param->shape = 1;
	}
	if (info != NULL) {
		delete info;
		noOttottoCclInfo[param->shape].a = param->a;
		noOttottoCclInfo[param->shape].b = param->b;
		noOttottoCclInfo[param->shape].c = param->c;
		Init(&noOttottoCclInfo[param->shape], 1, 4);
	}
}
