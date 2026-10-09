// TObjEggHorn's EditOnChange: the object only turns about Y, so the X and Z
// angles of its placement are cleared. The class is shared through
// egg_horn_class.inc.

#define EGG_HORN_CTOR inline
#include "src/rel/egg_horn_class.inc"

void TObjEggHorn::EditOnChange(SETDATA_PARAM* data)
{
	data->ang.x = 0;
	data->ang.z = 0;
}
