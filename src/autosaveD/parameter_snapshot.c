#include "types.h"

struct AutosaveState {
	u8 padding[0x810];
	s32 parameters[10];
};

extern "C" void fn_80194234(s32 id, s32 value);
extern "C" void fn_80194294(s32 id, s32* value);

extern "C" void fn_2_25A8(AutosaveState* state)
{
	fn_80194294(6, &state->parameters[0]);
	fn_80194294(8, &state->parameters[1]);
	fn_80194294(12, &state->parameters[2]);
	fn_80194294(10, &state->parameters[3]);
	fn_80194294(11, &state->parameters[4]);
	fn_80194294(9, &state->parameters[5]);
	fn_80194294(20, &state->parameters[6]);
	fn_80194294(3, &state->parameters[7]);
	fn_80194294(4, &state->parameters[8]);
	fn_80194294(14, &state->parameters[9]);

	fn_80194234(6, 0);
	fn_80194234(8, 0);
	fn_80194234(12, 1);
	fn_80194234(10, 5);
	fn_80194234(11, 6);
	fn_80194234(9, 1);
	fn_80194234(20, 1);
	fn_80194234(3, 3);
	fn_80194234(4, 3);
	fn_80194234(14, 0);
}
