// TObjS12ThunderRangeColli's destructor, out of line. Its body is empty: the
// vtable resets and the base destructors are the compiler's. The class is
// shared through s12_thunder_range_colli_class.inc, where the destructor is
// declared after the class's first other virtual so this unit does not emit the
// vtable.

#define S12_THUNDER_RANGE_COLLI_CTOR inline
#include "src/rel/s12_thunder_range_colli_class.inc"

TObjS12ThunderRangeColli::~TObjS12ThunderRangeColli() { }
