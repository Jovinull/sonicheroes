// TObjS14Eggman's destructor, out of line. It destroys its clump through
// fn_9_75888, which takes the pointer's address
// (stage13D/o_s13_antenna.cpp calls it the same way), then ends the set
// object when its condition has bit 0x10000 set. The class is shared through
// s14d_eggman_class.inc, where the destructor is declared after the class's
// first other virtual so this unit does not emit the vtable.

#define S14D_EGGMAN_CTOR inline
#include "src/rel/s14d_eggman_class.inc"

extern "C" void fn_9_75888(RpClump** clump);

TObjS14Eggman::~TObjS14Eggman()
{
	fn_9_75888(&clump);
	if (TstConditionBit(0x10000)) {
		SetEnd();
	}
}
