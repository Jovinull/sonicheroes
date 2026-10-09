// TObjRailChangeRail's EditOnChange: the object only turns about Y, so the X
// and Z angles of its placement are cleared. The class is shared through
// rail_change_rail_class.inc.

#define RAIL_CHANGE_RAIL_CTOR inline
#include "src/rel/rail_change_rail_class.inc"

void TObjRailChangeRail::EditOnChange(SETDATA_PARAM* data)
{
	data->ang.x = 0;
	data->ang.z = 0;
}
