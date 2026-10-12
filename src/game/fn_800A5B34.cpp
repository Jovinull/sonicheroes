#include "types.h"

struct Fn800A5B34Data {
	u8 pad[0x140];
	f32 input[3];
	u8 pad14C[0x98];
	f32 output[3];
};

extern "C" void fn_800A5B34(Fn800A5B34Data* arg0)
{
	arg0->output[0] = arg0->input[0];
	arg0->output[1] = arg0->input[1];
	arg0->output[2] = arg0->input[2];
}
