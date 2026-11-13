#include "types.h"

// HYPOTHESIS: stages state words for fn_801B11A4; volatile keeps the observed store order.
extern "C" {
struct State801B15AC {
	u8 pad[0x0C];
	s32 fieldC;
	s32 field10;
};
extern State801B15AC* volatile lbl_8042CA58;
void fn_801B11A4(State801B15AC*, s32*);
void fn_801B15AC()
{
	volatile s32 values[4];
	State801B15AC* state;
	values[0] = 0;
	values[1] = 0;
	state     = lbl_8042CA58;
	values[2] = state->fieldC;
	values[3] = state->field10;
	fn_801B11A4(state, (s32*)values);
}
}
