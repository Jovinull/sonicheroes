// TObjS14ThunderSet's destructor, out of line. It takes the set out of the
// module's chain of thunder sets through s14ThunderUnlink, the out-of-line partner of
// the s14ThunderLink link the constructor calls; the vtable resets and the base
// destructors are the compiler's. The class is shared through
// s14_thunder_class.inc, where the destructor is declared after the class's
// first other virtual so this unit does not emit the vtable.

#define S14_THUNDER_CTOR inline
#include "src/rel/s14_thunder_class.inc"

extern "C" void s14ThunderUnlink(TObjS14ThunderSet* set);

TObjS14ThunderSet::~TObjS14ThunderSet()
{
	s14ThunderUnlink(this);
}
