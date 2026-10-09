// TObjSystem2's destructor, out of line. Its body is empty: the vtable resets
// and the base destructors are the compiler's. The class is shared through
// system_object2_class.inc, where the destructor is declared after the class's
// first other virtual so this unit does not emit the vtable.

#define SYSTEM_OBJECT2_CTOR inline
#include "src/rel/system_object2_class.inc"

TObjSystem2::~TObjSystem2() { }
