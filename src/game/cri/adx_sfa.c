// adx_sfa: SFA init counter.
// .text 0x80213A5C-0x80213A8C (2 functions), .bss 0x804117A0-0x804117A4.
// Boundary: MKD adx_sfa.o (SFA_Finish, SFA_Init); adx_sje starts at 0x80213A8C.

#include "types.h"

static s32 sfa_init_cnt;

void SFA_Init(void)
{
	sfa_init_cnt++;
}

void SFA_Finish(void)
{
	sfa_init_cnt--;
}
