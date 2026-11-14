// Initializes a 0x18-byte shared state block: bytes 0-9 to 4, byte 10 to 5, byte 11 to 1, bytes
// 12-21 to 0 and the reference count at +0x16 to 1. Field roles are UNKNOWN.
struct State8015C728 {
	unsigned char f0[10];
	unsigned char fA;
	unsigned char fB;
	unsigned char fC;
	unsigned char fD;
	unsigned char fE[8];
	unsigned short refCount; // 0x16
};

extern "C" {
void fn_8015C728(State8015C728* state)
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
}
