// TObjSystem2's Disp (empty) and Exec, which only raises the kill bit when the
// object is out of range or due to be killed: in stage13D, where the other
// modules' C-style rel/system_object2_object.cpp is not linked (this module
// has the class's constructor and destructor as C++ units). The class is
// shared through system_object2_class.inc.

#define SYSTEM_OBJECT2_CTOR inline
#define SYSTEM_OBJECT_DTOR_FIRST
#include "src/rel/system_object2_class.inc"

void TObjSystem2::Disp() { }

void TObjSystem2::Exec()
{
	if (CheckRangeOut() || CheckMustKill()) {
		Signal |= 1;
	}
}
