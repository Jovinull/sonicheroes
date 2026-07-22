#include "types.h"
#include "dolphin/ppc.h"

// Speculative access disable, bit 22 of HID0.
#define HID0_SPD 0x0200

// Special purpose register numbers, spelled out so the asm blocks below do not
// depend on the assembler knowing the mnemonic names.
// clang-format off

asm u32 PPCMfmsr(void) {
#ifdef __MWERKS__
	nofralloc
	mfmsr   r3
	blr
#endif
}
// clang-format on
// clang-format off

asm void PPCMtmsr(register u32 newMSR) {
#ifdef __MWERKS__
	nofralloc
	mtmsr   r3
	blr
#endif
}
// clang-format on
// clang-format off

asm u32 PPCMfhid0(void) {
#ifdef __MWERKS__
	nofralloc
	mfspr   r3,SPR_HID0
	blr
#endif
}
// clang-format on
// clang-format off

asm void PPCMthid0(register u32 newHID0) {
#ifdef __MWERKS__
	nofralloc
	mtspr   SPR_HID0,r3
	blr
#endif
}
// clang-format on
// clang-format off

asm u32 PPCMfl2cr(void) {
#ifdef __MWERKS__
	nofralloc
	mfspr   r3,SPR_L2CR
	blr
#endif
}
// clang-format on
// clang-format off

asm void PPCMtl2cr(register u32 newL2cr) {
#ifdef __MWERKS__
	nofralloc
	mtspr   SPR_L2CR,r3
	blr
#endif
}
// clang-format on
// clang-format off

asm void PPCMtdec(register u32 newDec) {
#ifdef __MWERKS__
	nofralloc
	mtdec   r3
	blr
#endif
}
// clang-format on
// clang-format off

asm void PPCSync(void) {
#ifdef __MWERKS__
	nofralloc
	sc
	blr
#endif
}
// clang-format on
// clang-format off

asm void PPCHalt(void) {
#ifdef __MWERKS__
	nofralloc
	sync
halt_loop:
	nop
	li      r3,0
	nop
	b       halt_loop
#endif
}
// clang-format on
// clang-format off

asm void PPCMtmmcr0(register u32 newMmcr0) {
#ifdef __MWERKS__
	nofralloc
	mtspr   SPR_MMCR0,r3
	blr
#endif
}
// clang-format on
// clang-format off

asm void PPCMtmmcr1(register u32 newMmcr1) {
#ifdef __MWERKS__
	nofralloc
	mtspr   SPR_MMCR1,r3
	blr
#endif
}
// clang-format on
// clang-format off

asm void PPCMtpmc1(register u32 newPmc1) {
#ifdef __MWERKS__
	nofralloc
	mtspr   SPR_PMC1,r3
	blr
#endif
}
// clang-format on
// clang-format off

asm void PPCMtpmc2(register u32 newPmc2) {
#ifdef __MWERKS__
	nofralloc
	mtspr   SPR_PMC2,r3
	blr
#endif
}
// clang-format on
// clang-format off

asm void PPCMtpmc3(register u32 newPmc3) {
#ifdef __MWERKS__
	nofralloc
	mtspr   SPR_PMC3,r3
	blr
#endif
}
// clang-format on
// clang-format off

asm void PPCMtpmc4(register u32 newPmc4) {
#ifdef __MWERKS__
	nofralloc
	mtspr   SPR_PMC4,r3
	blr
#endif
}
// clang-format on
// clang-format off

asm u32 PPCMffpscr(void) {
#ifdef __MWERKS__
	nofralloc
	stwu    r1,-0x18(r1)
	stfd    fp31,0x10(r1)
	mffs    fp31
	stfd    fp31,0x8(r1)
	lwz     r3,0xC(r1)
	lfd     fp31,0x10(r1)
	addi    r1,r1,0x18
	blr
#endif
}
// clang-format on
// clang-format off

asm void PPCMtfpscr(register u32 newFpscr) {
#ifdef __MWERKS__
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
#endif
}
// clang-format on
// clang-format off

asm u32 PPCMfhid2(void) {
#ifdef __MWERKS__
	nofralloc
	mfspr   r3,SPR_HID2
	blr
#endif
}
// clang-format on
// clang-format off

asm void PPCMthid2(register u32 newHID2) {
#ifdef __MWERKS__
	nofralloc
	mtspr   SPR_HID2,r3
	blr
#endif
}
// clang-format on
// clang-format off

asm void PPCMtwpar(register u32 newWPAR) {
#ifdef __MWERKS__
	nofralloc
	mtspr   SPR_WPAR,r3
	blr
#endif
}
// clang-format on

// Plain C, unlike its neighbours. It touches no special purpose register
// directly, so there was never a reason for it to be assembly.
void PPCDisableSpeculation(void)
{
	PPCMthid0(PPCMfhid0() | HID0_SPD);
}
// clang-format off

asm void PPCSetFpNonIEEEMode(void) {
#ifdef __MWERKS__
	nofralloc
	mtfsb1  29
	blr
#endif
}
// clang-format on
