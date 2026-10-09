// TObjSystem3's Disp (empty) and Exec, which only raises the kill bit when the
// object is out of range or due to be killed: in stage13D, where the other
// modules' C-style rel/system_object3_object.cpp is not linked (this module
// has the class's constructor and destructor as C++ units). The class is
// shared through system_object3_class.inc.

#define SYSTEM_OBJECT3_CTOR inline
#define SYSTEM_OBJECT_DTOR_FIRST
#include "src/rel/system_object3_class.inc"

void TObjSystem3::Disp() { }

void TObjSystem3::Exec()
{
	if (CheckRangeOut() || CheckMustKill()) {
		Signal |= 1;
	}
}
