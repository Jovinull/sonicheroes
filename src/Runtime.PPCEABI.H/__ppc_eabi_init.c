#include "types.h"

typedef void (*funcptr_t)(void);

extern funcptr_t _ctors[];

extern void PPCHalt(void);

void __init_user(void);
static void __init_cpp(void);
void _ExitProcess(void);

void __init_user(void)
{
	__init_cpp();
}

// Written as asm rather than as the obvious for loop over _ctors. The original
// carries three chained branches through empty basic blocks between the loop
// setup and the condition test, and no plain C formulation reproduces them.
// clang-format off
// The same pattern shows up in __init_data over in dolphin/os/__start.c.
static asm void __init_cpp(void) {
#ifdef __MWERKS__
	nofralloc
	mflr    r0
	stw     r0,4(r1)
	stwu    r1,-16(r1)
	stw     r31,12(r1)
	lis     r3,_ctors@ha
	addi    r0,r3,_ctors@l
	mr      r31,r0
	b       pre1
pre1:
	b       pre2
pre2:
	b       cond
body:
	mtlr    r12
	blrl
	addi    r31,r31,4
cond:
	lwz     r12,0(r31)
	cmplwi  r12,0
	bne     body
	lwz     r0,20(r1)
	lwz     r31,12(r1)
	addi    r1,r1,16
	mtlr    r0
	blr
#endif
}
// clang-format on

void _ExitProcess(void)
{
	PPCHalt();
}
