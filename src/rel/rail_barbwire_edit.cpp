// TObjRailBarbwire's EditOnChange: the object only turns about Y, so the X and
// Z angles of its placement are cleared. The class is shared through
// rail_barbwire_class.inc.

#define RAIL_BARBWIRE_CTOR inline
#include "src/rel/rail_barbwire_class.inc"

void TObjRailBarbwire::EditOnChange(SETDATA_PARAM* data)
{
	data->ang.x = 0;
	data->ang.z = 0;
}
