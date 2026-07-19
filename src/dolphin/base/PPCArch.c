#include "types.h"

// Special purpose register numbers, spelled out so the asm blocks below do not
// depend on the assembler knowing the mnemonic names.
#define SPR_HID0  1008
#define SPR_HID2  920
#define SPR_WPAR  921
#define SPR_L2CR  1017
#define SPR_MMCR0 952
#define SPR_MMCR1 956
#define SPR_PMC1  953
#define SPR_PMC2  954
#define SPR_PMC3  957
#define SPR_PMC4  958

asm u32 PPCMfmsr(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mfmsr   r3
	blr
#endif // clang-format on
}

asm void PPCMtmsr(register u32 newMSR) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mtmsr   r3
	blr
#endif // clang-format on
}

asm u32 PPCMfhid0(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mfspr   r3,SPR_HID0
	blr
#endif // clang-format on
}

asm void PPCMthid0(register u32 newHID0) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mtspr   SPR_HID0,r3
	blr
#endif // clang-format on
}

asm u32 PPCMfl2cr(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mfspr   r3,SPR_L2CR
	blr
#endif // clang-format on
}

asm void PPCMtl2cr(register u32 newL2cr) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mtspr   SPR_L2CR,r3
	blr
#endif // clang-format on
}

asm void PPCMtdec(register u32 newDec) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mtdec   r3
	blr
#endif // clang-format on
}

asm void PPCSync(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	sc
	blr
#endif // clang-format on
}

asm void PPCHalt(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	sync
halt_loop:
	nop
	li      r3,0
	nop
	b       halt_loop
#endif // clang-format on
}

asm void PPCMtmmcr0(register u32 newMmcr0) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mtspr   SPR_MMCR0,r3
	blr
#endif // clang-format on
}

asm void PPCMtmmcr1(register u32 newMmcr1) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mtspr   SPR_MMCR1,r3
	blr
#endif // clang-format on
}

asm void PPCMtpmc1(register u32 newPmc1) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mtspr   SPR_PMC1,r3
	blr
#endif // clang-format on
}

asm void PPCMtpmc2(register u32 newPmc2) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mtspr   SPR_PMC2,r3
	blr
#endif // clang-format on
}

asm void PPCMtpmc3(register u32 newPmc3) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mtspr   SPR_PMC3,r3
	blr
#endif // clang-format on
}

asm void PPCMtpmc4(register u32 newPmc4) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mtspr   SPR_PMC4,r3
	blr
#endif // clang-format on
}

asm u32 PPCMffpscr(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	stwu    r1,-0x18(r1)
	stfd    fp31,0x10(r1)
	mffs    fp31
	stfd    fp31,0x8(r1)
	lwz     r3,0xC(r1)
	lfd     fp31,0x10(r1)
	addi    r1,r1,0x18
	blr
#endif // clang-format on
}

asm void PPCMtfpscr(register u32 newFpscr) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	stwu    r1,-0x20(r1)
	stfd    fp31,0x18(r1)
	li      r4,0
	stw     r4,0x10(r1)
	stw     r3,0x14(r1)
	lfd     fp31,0x10(r1)
	mtfsf   255,fp31
	lfd     fp31,0x18(r1)
	addi    r1,r1,0x20
	blr
#endif // clang-format on
}

asm u32 PPCMfhid2(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mfspr   r3,SPR_HID2
	blr
#endif // clang-format on
}

asm void PPCMthid2(register u32 newHID2) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mtspr   SPR_HID2,r3
	blr
#endif // clang-format on
}

asm void PPCMtwpar(register u32 newWPAR) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mtspr   SPR_WPAR,r3
	blr
#endif // clang-format on
}

asm void PPCDisableSpeculation(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mflr    r0
	stw     r0,4(r1)
	stwu    r1,-8(r1)
	bl      PPCMfhid0
	ori     r3,r3,0x0200
	bl      PPCMthid0
	lwz     r0,12(r1)
	addi    r1,r1,8
	mtlr    r0
	blr
#endif // clang-format on
}

asm void PPCSetFpNonIEEEMode(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mtfsb1  29
	blr
#endif // clang-format on
}
