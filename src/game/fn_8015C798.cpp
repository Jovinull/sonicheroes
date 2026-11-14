// Allocates a 0x18-byte shared state block with the engine memory function and initializes it as
// fn_8015C728 does (that initializer is inlined here). Returns the block; the allocation is not
// checked.
#include "game/rw_engine.h"

struct State8015C798 {
	unsigned char f0[10];
	unsigned char fA;
	unsigned char fB;
	unsigned char fC;
	unsigned char fD;
	unsigned char fE[8];
	unsigned short refCount; // 0x16
};

// Same body as fn_8015C728.
static inline void StateInit(State8015C798* state)
{
	state->f0[0]    = 4;
	state->f0[1]    = 4;
	state->f0[2]    = 4;
	state->f0[3]    = 4;
	state->f0[4]    = 4;
	state->f0[5]    = 4;
	state->f0[6]    = 4;
	state->f0[7]    = 4;
	state->f0[8]    = 4;
	state->f0[9]    = 4;
	state->fA       = 5;
	state->fB       = 1;
	state->fC       = 0;
	state->fE[0]    = 0;
	state->fE[1]    = 0;
	state->fE[2]    = 0;
	state->fE[3]    = 0;
	state->fE[4]    = 0;
	state->fE[5]    = 0;
	state->fE[6]    = 0;
	state->fE[7]    = 0;
	state->fD       = 0;
	state->refCount = 1;
}

extern "C" {
State8015C798* fn_8015C798(void)
{
	State8015C798* state = (State8015C798*)lbl_8042C9A4->rwmalloc(sizeof(State8015C798));
	StateInit(state);
	return state;
}
}
