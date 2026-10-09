// TObjSetNoOttottoCollision's destructor, out of line. Its body is empty: the vtable resets and the
// base destructors are the compiler's. The class is shared through
// no_ottotto_collision_class.inc, where the destructor is declared after the class's first
// other virtual so this unit does not emit the vtable.

#define NO_OTTOTTO_COLLISION_CTOR inline
#include "src/rel/no_ottotto_collision_class.inc"

TObjSetNoOttottoCollision::~TObjSetNoOttottoCollision() { }
