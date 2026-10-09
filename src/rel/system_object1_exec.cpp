// TObjSystem1's Disp (empty) and Exec, which only raises the kill bit when the
// object is out of range or due to be killed: in stage13D, where the other
// modules' C-style rel/system_object1_object.cpp is not linked (this module
// has the class's constructor and destructor as C++ units). The class is
// shared through system_object1_class.inc.

#define SYSTEM_OBJECT1_CTOR inline
#define SYSTEM_OBJECT_DTOR_FIRST
#include "src/rel/system_object1_class.inc"

void TObjSystem1::Disp() { }

void TObjSystem1::Exec()
{
	if (CheckRangeOut() || CheckMustKill()) {
		Signal |= 1;
	}
}
