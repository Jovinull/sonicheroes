// TObjRailWaterSupply's EditOnChange: the object only turns about Y, so the X
// and Z angles of its placement are cleared. The class is shared through
// rail_water_supply_class.inc.

#define RAIL_WATER_SUPPLY_CTOR inline
#include "src/rel/rail_water_supply_class.inc"

void TObjRailWaterSupply::EditOnChange(SETDATA_PARAM* data)
{
	data->ang.x = 0;
	data->ang.z = 0;
}
