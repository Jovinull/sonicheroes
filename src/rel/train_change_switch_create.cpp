// trainchangeswitchCreate, the factory the editor record for
// TObjTrainChangeSwitch points at, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp, and
// the empty TrainSwitchManager of rel/train_change_board_create.cpp the fourth.
//
// The switch clones the three models the module keeps, starting with
// "obj07_changeswitch_base.dff", into three parts, adds only the first to the
// world slot its file names, takes the module's shape through InitShare, as
// rel/key_object_create.cpp does, and clears the word at 0xD4.

#define TRAIN_CHANGE_SWITCH_CTOR inline
#include "src/rel/train_change_switch_class.inc"

extern "C" void trainchangeswitchCreate(void)
{
	new TObjTrainChangeSwitch(lbl_8042C110);
}
