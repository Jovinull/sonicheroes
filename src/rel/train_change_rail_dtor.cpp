// TObjTrainChangeRail's destructor, out of line. For each of the two rails it
// calls fn_6_908D0 and frees the rail's buffer with the global operator
// delete; then it marks the placement's original work (a halfword flag at
// +2). The pointer to that work is read before the loop, as the original
// keeps it in r30 across the calls. The vtable resets and the base destructors
// are the compiler's, TrainSwitchManager's out of line. The class is shared
// through train_change_rail_class.inc, where the destructor is declared after
// the class's first other virtual so this unit does not emit the vtable.

#define TRAIN_CHANGE_RAIL_CTOR inline
#include "src/rel/train_change_rail_class.inc"

TObjTrainChangeRail::~TObjTrainChangeRail()
{
	u16* original = (u16*)ObjParam->originalWork;

	for (int i = 0; i < 2; i++) {
		fn_6_908D0(this, i, 0);
		delete work[i].buf;
	}
	original[1] = 1;
}
