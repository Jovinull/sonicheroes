// TObjStopRain's destructor, out of line. Its body is empty: the vtable resets
// and the base destructors are the compiler's. The class is shared through
// stop_rain_class.inc, where the destructor is declared after the class's first
// other virtual so this unit does not emit the vtable.

#define STOP_RAIN_CTOR inline
#include "src/rel/stop_rain_class.inc"

TObjStopRain::~TObjStopRain() { }
