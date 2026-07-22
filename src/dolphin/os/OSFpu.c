#include "types.h"
#include "dolphin/ppc.h"

// Zero sources for the two register files. Both live in .sbss, so they are
// already zero by the time this runs.
static f64 ZeroF;
static f32 ZeroPS[2];

// Clears every floating point register, and the paired single halves too when
// clang-format off
// the paired single unit is enabled in HID2.
asm void __OSFPRInit(void) {
#ifdef __MWERKS__
	nofralloc
	mfmsr   r3
	ori     r3,r3,0x2000
	mtmsr   r3

	mfspr   r3,SPR_HID2
	rlwinm. r3,r3,3,31,31
	beq     no_paired_single

	lis     r3,ZeroPS@ha
	addi    r3,r3,ZeroPS@l
	psq_l   fp0,0(r3),0,0
	ps_mr   fp1,fp0
	ps_mr   fp2,fp0
	ps_mr   fp3,fp0
	ps_mr   fp4,fp0
	ps_mr   fp5,fp0
	ps_mr   fp6,fp0
	ps_mr   fp7,fp0
	ps_mr   fp8,fp0
	ps_mr   fp9,fp0
	ps_mr   fp10,fp0
	ps_mr   fp11,fp0
	ps_mr   fp12,fp0
	ps_mr   fp13,fp0
	ps_mr   fp14,fp0
	ps_mr   fp15,fp0
	ps_mr   fp16,fp0
	ps_mr   fp17,fp0
	ps_mr   fp18,fp0
	ps_mr   fp19,fp0
	ps_mr   fp20,fp0
	ps_mr   fp21,fp0
	ps_mr   fp22,fp0
	ps_mr   fp23,fp0
	ps_mr   fp24,fp0
	ps_mr   fp25,fp0
	ps_mr   fp26,fp0
	ps_mr   fp27,fp0
	ps_mr   fp28,fp0
	ps_mr   fp29,fp0
	ps_mr   fp30,fp0
	ps_mr   fp31,fp0

no_paired_single:
	lfd     fp0,ZeroF
	fmr     fp1,fp0
	fmr     fp2,fp0
	fmr     fp3,fp0
	fmr     fp4,fp0
	fmr     fp5,fp0
	fmr     fp6,fp0
	fmr     fp7,fp0
	fmr     fp8,fp0
	fmr     fp9,fp0
	fmr     fp10,fp0
	fmr     fp11,fp0
	fmr     fp12,fp0
	fmr     fp13,fp0
	fmr     fp14,fp0
	fmr     fp15,fp0
	fmr     fp16,fp0
	fmr     fp17,fp0
	fmr     fp18,fp0
	fmr     fp19,fp0
	fmr     fp20,fp0
	fmr     fp21,fp0
	fmr     fp22,fp0
	fmr     fp23,fp0
	fmr     fp24,fp0
	fmr     fp25,fp0
	fmr     fp26,fp0
	fmr     fp27,fp0
	fmr     fp28,fp0
	fmr     fp29,fp0
	fmr     fp30,fp0
	fmr     fp31,fp0
	mtfsf   255,fp0
	blr
#endif
}
// clang-format on
