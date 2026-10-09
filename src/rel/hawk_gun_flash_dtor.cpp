// TObjHawkGunFlash's destructor, out of line. Its body is empty: the vtable
// resets and the base destructors are the compiler's. The class is shared
// through hawk_gun_flash_class.inc, where the destructor is declared after the
// class's first other virtual so this unit does not emit the vtable.

#define HAWK_GUN_FLASH_CTOR inline
#include "src/rel/hawk_gun_flash_class.inc"

TObjHawkGunFlash::~TObjHawkGunFlash() { }
