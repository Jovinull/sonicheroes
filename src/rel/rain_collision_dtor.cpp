// TObjRainCollision's destructor, out of line. Its body is empty: the vtable resets and the
// base destructors are the compiler's. The class is shared through
// rain_collision_class.inc, where the destructor is declared after the class's first
// other virtual so this unit does not emit the vtable.

#define RAIN_COLLISION_CTOR inline
#include "src/rel/rain_collision_class.inc"

TObjRainCollision::~TObjRainCollision() { }
