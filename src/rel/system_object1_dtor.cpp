// TObjSystem1's destructor, out of line. Its body is empty: the vtable resets
// and the base destructors are the compiler's. The class is shared through
// system_object1_class.inc, where the destructor is declared after the class's
// first other virtual so this unit does not emit the vtable.

#define SYSTEM_OBJECT1_CTOR inline
#include "src/rel/system_object1_class.inc"

TObjSystem1::~TObjSystem1() { }
