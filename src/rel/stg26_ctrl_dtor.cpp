#include "game/obj_stg26_ctrl.h"

// TStg26Ctrl's destructor (game/obj_stg26_ctrl.h): nothing of its own to
// release, so it only restores the vtable and runs the object base down, as
// rel/shield_splinter_dtor.cpp does in C form. Exec is the key function (declared first in the header),
// so this unit does not emit the vtable.

TStg26Ctrl::~TStg26Ctrl() { }
