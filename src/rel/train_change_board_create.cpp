// trainchangeboardCreate, the factory the editor record for
// TObjTrainChangeBoard points at, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The third base is TrainSwitchManager, the PS2 build's
// empty class with an out of line constructor (a lone blr at 0x95704 in this
// module): it takes no room, so the position starts at 0x30 where the base is
// constructed.
//
// It is rel/rail_cap_ex_create.cpp for seven models, starting with
// "obj07_ChangeBoard.dff": each is cloned into its own part and added once to
// the world slot its file names.

#define TRAIN_CHANGE_BOARD_CTOR inline
#include "src/rel/train_change_board_class.inc"

extern "C" void trainchangeboardCreate(void)
{
	new TObjTrainChangeBoard(lbl_8042C110);
}
