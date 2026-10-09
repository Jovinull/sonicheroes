// TObjS23WarpPos's destructor, out of line. It takes the warp point out of
// the chain the constructor linked it into (LinkChain in s23_warppos_class.inc):
// the head moves on when it is the first, otherwise the walk finds the one
// before it. The head is loaded into the walk's pointer inside the test:
// assigned on its own line, or tested through pTopWarp, it costs an extra
// register move. The class is shared through s23_warppos_class.inc, where the
// destructor is declared after the class's first other virtual so this unit
// does not emit the vtable.

#define S23_WARPPOS_CTOR inline
#include "src/rel/s23_warppos_class.inc"

TObjS23WarpPos::~TObjS23WarpPos()
{
	TObjS23WarpPos* prev;

	if ((prev = pTopWarp) == this) {
		pTopWarp = next;
	} else {
		while (prev->next != this) {
			prev = prev->next;
		}
		prev->next = next;
	}
	next = NULL;
}
