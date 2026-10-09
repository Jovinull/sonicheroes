// TObjS13Cloud1's destructor, out of line. It deletes the cloud's particles
// one by one until the list is empty; each particle's own destructor unlinks
// it, so the loop rereads topPtcl every time. The loop is the derived class's
// body and not a destructor of the TObjS13Cloud base: a base destructor would
// first test the base pointer for null, which the original does not. The
// class is shared through s13_cloud1_class.inc, where the destructor is
// declared after the class's first other virtual so this unit does not emit
// the vtable.

#define S13_CLOUD1_CTOR inline
#include "src/rel/s13_cloud1_class.inc"

TObjS13Cloud1::~TObjS13Cloud1()
{
	while (topPtcl != NULL) {
		delete topPtcl;
	}
}
