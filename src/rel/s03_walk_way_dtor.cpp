// TObjS03WalkWay's destructor, out of line. Its body is empty: the vtable
// resets and the base destructors are the compiler's. The class is shared
// through s03_walk_way_class.inc, where the destructor is declared after the
// class's first other virtual so this unit does not emit the vtable.

#define S03_WALK_WAY_CTOR inline
#include "src/rel/s03_walk_way_class.inc"

TObjS03WalkWay::~TObjS03WalkWay() { }
