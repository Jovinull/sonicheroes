// TObjS03Train's destructor, out of line. It ends the set object when its
// condition has bit 0x10000 set; the vtable resets and the base destructors are
// the compiler's. The class is shared through s03_train_class.inc, where the
// destructor is declared after the class's first other virtual so this unit
// does not emit the vtable.

#define S03_TRAIN_CTOR inline
#include "src/rel/s03_train_class.inc"

TObjS03Train::~TObjS03Train()
{
	if (TstConditionBit(0x10000)) {
		SetEnd();
	}
}
