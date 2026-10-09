// TObjSystem3's destructor, out of line. Its body is empty: the vtable resets
// and the base destructors are the compiler's. The class is shared through
// system_object3_class.inc, where the destructor is declared after the class's
// first other virtual so this unit does not emit the vtable.

#define SYSTEM_OBJECT3_CTOR inline
#include "src/rel/system_object3_class.inc"

TObjSystem3::~TObjSystem3() { }
