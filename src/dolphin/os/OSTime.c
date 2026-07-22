#include "types.h"
#include "dolphin/os.h"

typedef u32 OSTick;

// Boot time, kept in the OS globals area at 0x800030D8.
#define OS_SYSTEM_TIME (*(OSTime*)0x800030D8)

asm OSTime OSGetTime(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
retry:
	mftb    r3,269
	mftb    r4,268
	mftb    r5,269
	cmpw    r3,r5
	bne     retry
	blr
#endif // clang-format on
}

asm OSTick OSGetTick(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mftb    r3,268
	blr
#endif // clang-format on
}

// The obvious C body reproduces every instruction of this function but comes
// out with a 0x18 frame instead of 0x20. The original reserves a stack slot for
// the OSTime local that no tested C formulation produces: declaring the local
// separately, dropping volatile from the global, and marking the local volatile
// all scored worse, not better. Transcribed instead so the file matches.
asm OSTime __OSGetSystemTime(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mflr    r0
	stw     r0,4(r1)
	stwu    r1,-0x20(r1)
	stw     r31,0x1C(r1)
	stw     r30,0x18(r1)
	stw     r29,0x14(r1)
	bl      OSDisableInterrupts
	mr      r31,r3
	bl      OSGetTime
	lis     r6,0x8000
	lwz     r5,0x30DC(r6)
	lwz     r0,0x30D8(r6)
	addc    r29,r5,r4
	adde    r30,r0,r3
	mr      r3,r31
	bl      OSRestoreInterrupts
	mr      r4,r29
	mr      r3,r30
	lwz     r0,0x24(r1)
	lwz     r31,0x1C(r1)
	lwz     r30,0x18(r1)
	lwz     r29,0x14(r1)
	addi    r1,r1,0x20
	mtlr    r0
	blr
#endif // clang-format on
}
