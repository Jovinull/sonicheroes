// trainchangerailCreate, the factory the editor record for TObjTrainChangeRail
// points at, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The third base is the empty TrainSwitchManager, as in
// rel/train_change_board_create.cpp.
//
// The constructor copies the placement and clears two vectors with memset and
// the word at 0x80.

#define TRAIN_CHANGE_RAIL_CTOR inline
#include "src/rel/train_change_rail_class.inc"

extern "C" void trainchangerailCreate(void)
{
	new TObjTrainChangeRail(lbl_8042C110);
}
