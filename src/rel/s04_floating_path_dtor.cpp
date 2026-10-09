// TObjS04FloatWay's destructor, out of line. Its body is empty: the vtable
// resets and the base destructors are the compiler's. The class is shared
// through s04_floating_path_class.inc, where the destructor is declared after
// the class's first other virtual so this unit does not emit the vtable.

#define S04_FLOATING_PATH_CTOR inline
#include "src/rel/s04_floating_path_class.inc"

TObjS04FloatWay::~TObjS04FloatWay() { }
