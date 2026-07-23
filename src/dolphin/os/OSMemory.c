#include "types.h"

#define NULL  0
#define FALSE 0
#define TRUE  1

typedef int BOOL;
typedef struct OSContext OSContext;
typedef void (*OSErrorHandler)(u16 error, OSContext* context, ...);

typedef struct OSResetFunctionInfo {
	BOOL (*func)(BOOL final);
	u32 priority;
	struct OSResetFunctionInfo* next;
	struct OSResetFunctionInfo* prev;
} OSResetFunctionInfo;

#define OSPhysicalToCached(paddr) ((void*)((u32)(paddr) + 0x80000000))

#ifdef __MWERKS__
volatile u16 __MEMRegs[] : 0xCC004000;
#else
extern volatile u16 __MEMRegs[];
#endif

#define OS_ERROR_PROTECTION 15

extern OSErrorHandler __OSErrorTable[];

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u32 __OSMaskInterrupts(u32 mask);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern void (*__OSSetInterruptHandler(s16 interrupt, void (*handler)(s16, OSContext*)))(
    s16, OSContext*);
extern void OSRegisterResetFunction(OSResetFunctionInfo* info);
extern void DCInvalidateRange(void* addr, u32 nBytes);
extern void __OSUnhandledException(u8 exception, OSContext* context, u32 dsisr, u32 dar);

static BOOL OnReset(BOOL final);
static void MEMIntrruptHandler(s16 interrupt, OSContext* context);
static ASM void Config24MB(void);
static ASM void Config48MB(void);
static ASM void RealMode(register u32 config);

static OSResetFunctionInfo ResetFunctionInfo = {
	OnReset,
	127,
};

static BOOL OnReset(BOOL final)
{
	if (final != FALSE) {
		__MEMRegs[8] = 0xFF;
		__OSMaskInterrupts(0xF0000000);
	}
	return TRUE;
}

static void MEMIntrruptHandler(s16 interrupt, OSContext* context)
{
	u32 addr;
	u32 cause;

	cause         = __MEMRegs[15];
	addr          = (((u32)__MEMRegs[18] & 0x3FF) << 16) | __MEMRegs[17];
	__MEMRegs[16] = 0;

	if (__OSErrorTable[OS_ERROR_PROTECTION]) {
		__OSErrorTable[OS_ERROR_PROTECTION](OS_ERROR_PROTECTION, context, cause, addr);
		return;
	}
	__OSUnhandledException(OS_ERROR_PROTECTION, context, cause, addr);
}

static ASM void Config24MB(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	li      r7, 0x0
	lis     r4, 0x0
	addi    r4, r4, 0x2
	lis     r3, 0x8000
	addi    r3, r3, 0x1FF
	lis     r6, 0x100
	addi    r6, r6, 0x2
	lis     r5, 0x8100
	addi    r5, r5, 0xFF
	isync
	mtdbatu 0, r7
	mtdbatl 0, r4
	mtdbatu 0, r3
	isync
	mtibatu 0, r7
	mtibatl 0, r4
	mtibatu 0, r3
	isync
	mtdbatu 2, r7
	mtdbatl 2, r6
	mtdbatu 2, r5
	isync
	mtibatu 2, r7
	mtibatl 2, r6
	mtibatu 2, r5
	isync
	mfmsr   r3
	ori     r3, r3, 0x30
	mtsrr1  r3
	mflr    r3
	mtsrr0  r3
	rfi
#endif // clang-format on
}

static ASM void Config48MB(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	li      r7, 0x0
	lis     r4, 0x0
	addi    r4, r4, 0x2
	lis     r3, 0x8000
	addi    r3, r3, 0x3FF
	lis     r6, 0x200
	addi    r6, r6, 0x2
	lis     r5, 0x8200
	addi    r5, r5, 0x1FF
	isync
	mtdbatu 0, r7
	mtdbatl 0, r4
	mtdbatu 0, r3
	isync
	mtibatu 0, r7
	mtibatl 0, r4
	mtibatu 0, r3
	isync
	mtdbatu 2, r7
	mtdbatl 2, r6
	mtdbatu 2, r5
	isync
	mtibatu 2, r7
	mtibatl 2, r6
	mtibatu 2, r5
	isync
	mfmsr   r3
	ori     r3, r3, 0x30
	mtsrr1  r3
	mflr    r3
	mtsrr0  r3
	rfi
#endif // clang-format on
}

static ASM void RealMode(register u32 config)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	clrlwi  r3, r3, 2
	mtsrr0  r3
	mfmsr   r3
	rlwinm  r3, r3, 0, 28, 25
	mtsrr1  r3
	rfi
#endif // clang-format on
}

void __OSInitMemoryProtection(void)
{
	u32 physMem;
	BOOL enabled;
	u32 pad[12];

	physMem = *(u32*)OSPhysicalToCached(0xF0);
	enabled = OSDisableInterrupts();

	__MEMRegs[16] = 0;
	__MEMRegs[8]  = 0xFF;
	__OSMaskInterrupts(0xF0000000);
	__OSSetInterruptHandler(0, MEMIntrruptHandler);
	__OSSetInterruptHandler(1, MEMIntrruptHandler);
	__OSSetInterruptHandler(2, MEMIntrruptHandler);
	__OSSetInterruptHandler(3, MEMIntrruptHandler);
	__OSSetInterruptHandler(4, MEMIntrruptHandler);
	OSRegisterResetFunction(&ResetFunctionInfo);

	if (*(u32*)OSPhysicalToCached(0xF0) < *(u32*)OSPhysicalToCached(0x28)
	    && *(u32*)OSPhysicalToCached(0xF0) == 0x01800000) {
		DCInvalidateRange((void*)0x81800000, 0x01800000);
		__MEMRegs[20] = 2;
	}
	if (physMem <= 0x01800000) {
		RealMode((u32)Config24MB);
	} else if (physMem <= 0x03000000) {
		RealMode((u32)Config48MB);
	}
	__OSUnmaskInterrupts(0x08000000);
	OSRestoreInterrupts(enabled);
}
