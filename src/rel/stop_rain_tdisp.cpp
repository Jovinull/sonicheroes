// TObjStopRain's TDisp, which only asks OnEdit and drops the answer (the
// editor-only drawing it guarded is not in the build). The class is shared
// through stop_rain_class.inc.

#define STOP_RAIN_CTOR inline
#include "src/rel/stop_rain_class.inc"

void TObjStopRain::TDisp()
{
	OnEdit();
}
