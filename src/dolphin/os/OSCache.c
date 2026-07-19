#include "types.h"

#define SPR_HID0 1008
#define SPR_HID2 920

#define HID2_DCHERR 0x00800000
#define HID2_DNCERR 0x00400000
#define HID2_DCMERR 0x00200000
#define HID2_DQOERR 0x00100000
#define HID2_DMAQL  0x0F000000

// Only the fields up to srr1 matter here. srr1 sits at 0x19C.
//
// Note the two reads of srr1 in DMAErrorHandler are written differently on
// purpose. Writing both as context->srr1 makes the compiler hoist the address
// into a spare register and the function stops matching. This mix is what
// reproduces the original's two direct lwz 0x19C(rN) loads.
typedef struct OSContext {
	u32 gpr[32];
	u32 cr;
	u32 lr;
	u32 ctr;
	u32 xer;
	f64 fpr[32];
	u32 fpscr_pad;
	u32 fpscr;
	u32 srr0;
	u32 srr1;
} OSContext;

extern u32 PPCMfhid2(void);
extern void PPCMthid2(u32 newHID2);
extern u32 PPCMfl2cr(void);
extern void PPCMtl2cr(u32 newL2cr);
extern u32 PPCMfmsr(void);
extern void PPCMtmsr(u32 newMSR);
extern u32 PPCMfhid0(void);
extern void PPCHalt(void);
extern void DBPrintf(const char* msg, ...);
extern void OSReport(const char* msg, ...);
extern void OSDumpContext(OSContext* context);
extern void* OSSetErrorHandler(u16 error, void* handler);

void DCEnable(void);
void ICEnable(void);
void L2GlobalInvalidate(void);
static void DMAErrorHandler(u16 error, OSContext* context, ...);

asm void DCEnable(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	sync
	mfspr   r3,SPR_HID0
	ori     r3,r3,0x4000
	mtspr   SPR_HID0,r3
	blr
#endif // clang-format on
}

asm void DCInvalidateRange(register void* addr, register u32 nBytes) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	cmplwi  r4,0
	blelr
	clrlwi  r5,r3,27
	add     r4,r4,r5
	addi    r4,r4,31
	srwi    r4,r4,5
	mtctr   r4
inv_loop:
	dcbi    r0,r3
	addi    r3,r3,32
	bdnz    inv_loop
	blr
#endif // clang-format on
}

asm void DCFlushRange(register void* addr, register u32 nBytes) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	cmplwi  r4,0
	blelr
	clrlwi  r5,r3,27
	add     r4,r4,r5
	addi    r4,r4,31
	srwi    r4,r4,5
	mtctr   r4
flush_loop:
	dcbf    r0,r3
	addi    r3,r3,32
	bdnz    flush_loop
	sc
	blr
#endif // clang-format on
}

asm void DCStoreRange(register void* addr, register u32 nBytes) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	cmplwi  r4,0
	blelr
	clrlwi  r5,r3,27
	add     r4,r4,r5
	addi    r4,r4,31
	srwi    r4,r4,5
	mtctr   r4
store_loop:
	dcbst   r0,r3
	addi    r3,r3,32
	bdnz    store_loop
	sc
	blr
#endif // clang-format on
}

asm void DCFlushRangeNoSync(register void* addr, register u32 nBytes) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	cmplwi  r4,0
	blelr
	clrlwi  r5,r3,27
	add     r4,r4,r5
	addi    r4,r4,31
	srwi    r4,r4,5
	mtctr   r4
flushns_loop:
	dcbf    r0,r3
	addi    r3,r3,32
	bdnz    flushns_loop
	blr
#endif // clang-format on
}

asm void ICInvalidateRange(register void* addr, register u32 nBytes) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	cmplwi  r4,0
	blelr
	clrlwi  r5,r3,27
	add     r4,r4,r5
	addi    r4,r4,31
	srwi    r4,r4,5
	mtctr   r4
icinv_loop:
	icbi    r0,r3
	addi    r3,r3,32
	bdnz    icinv_loop
	sync
	isync
	blr
#endif // clang-format on
}

asm void ICFlashInvalidate(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mfspr   r3,SPR_HID0
	ori     r3,r3,0x0800
	mtspr   SPR_HID0,r3
	blr
#endif // clang-format on
}

asm void ICEnable(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	isync
	mfspr   r3,SPR_HID0
	ori     r3,r3,0x8000
	mtspr   SPR_HID0,r3
	blr
#endif // clang-format on
}

asm void LCDisable(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	lis     r3,0xE000
	li      r4,512
	mtctr   r4
lc_loop:
	dcbi    r0,r3
	addi    r3,r3,32
	bdnz    lc_loop
	mfspr   r4,SPR_HID2
	rlwinm  r4,r4,0,4,2
	mtspr   SPR_HID2,r4
	blr
#endif // clang-format on
}

// The original calls this rather than inlining it, so keep the compiler from
// folding it into __OSCacheInit.
#pragma dont_inline on
void L2GlobalInvalidate(void)
{
	__sync();
	PPCMtl2cr(PPCMfl2cr() & ~0x80000000);
	__sync();
	PPCMtl2cr(PPCMfl2cr() | 0x00200000);

	while (PPCMfl2cr() & 1) {
		;
	}

	PPCMtl2cr(PPCMfl2cr() & ~0x00200000);

	while (PPCMfl2cr() & 1) {
		DBPrintf(">>> L2 INVALIDATE : SHOULD NEVER HAPPEN\n");
	}
}
#pragma dont_inline off

static void DMAErrorHandler(u16 error, OSContext* context, ...)
{
	u32 hid2 = PPCMfhid2();

	OSReport("Machine check received\n");
	OSReport("HID2 = 0x%x   SRR1 = 0x%x\n", hid2, ((u32*)context)[0x67]);

	if (!(hid2 & (HID2_DCHERR | HID2_DNCERR | HID2_DCMERR | HID2_DQOERR))
	    || !(context->srr1 & 0x00200000)) {
		OSReport("Machine check was not DMA/locked cache related\n");
		OSDumpContext(context);
		PPCHalt();
	}

	OSReport("DMAErrorHandler(): An error occurred while processing DMA.\n");
	OSReport("The following errors have been detected and cleared :\n");

	if (hid2 & HID2_DCHERR) {
		OSReport("\t- Requested a locked cache tag that was already in the cache\n");
	}

	if (hid2 & HID2_DNCERR) {
		OSReport("\t- DMA attempted to access normal cache\n");
	}

	if (hid2 & HID2_DCMERR) {
		OSReport("\t- DMA missed in data cache\n");
	}

	if (hid2 & HID2_DQOERR) {
		OSReport("\t- DMA queue overflowed\n");
	}

	PPCMthid2(hid2);
}

void __OSCacheInit(void)
{
	if (!(PPCMfhid0() & 0x8000)) {
		ICEnable();
		DBPrintf("L1 i-caches initialized\n");
	}

	if (!(PPCMfhid0() & 0x4000)) {
		DCEnable();
		DBPrintf("L1 d-caches initialized\n");
	}

	if (!(PPCMfl2cr() & 0x80000000)) {
		u32 oldMsr = PPCMfmsr();
		__sync();
		PPCMtmsr(0x30);
		__sync();

		__sync();
		PPCMtl2cr(PPCMfl2cr() & ~0x80000000);
		__sync();

		L2GlobalInvalidate();
		PPCMtmsr(oldMsr);

		PPCMtl2cr((PPCMfl2cr() | 0x80000000) & ~0x00200000);
		DBPrintf("L2 cache initialized\n");
	}

	OSSetErrorHandler(1, DMAErrorHandler);
	DBPrintf("Locked cache machine check handler installed\n");
}
