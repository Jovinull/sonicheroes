// TObjS08BobRangeColli's destructor, out of line. Its body is empty: the vtable
// resets and the base destructors are the compiler's. The class is shared
// through s08_bob_range_colli_class.inc, where the destructor is declared after
// the class's first other virtual so this unit does not emit the vtable.

#define S08_BOB_RANGE_COLLI_CTOR inline
#include "src/rel/s08_bob_range_colli_class.inc"

TObjS08BobRangeColli::~TObjS08BobRangeColli() { }
