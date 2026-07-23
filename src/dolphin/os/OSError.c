#include "dolphin/os.h"
#include "dolphin/ppc.h"

typedef u16 OSError;
typedef void (*OSErrorHandler)(OSError, OSContext*, ...);

typedef struct OSThread OSThread;
typedef struct OSThreadLink {
	OSThread* next;
	OSThread* prev;
} OSThreadLink;

struct OSThread {
	OSContext context;       // 0x000
	u8 unk_0x2C8[0x34];      // 0x2C8
	OSThreadLink linkActive; // 0x2FC
};

typedef struct OSThreadQueue {
	OSThread* head;
	OSThread* tail;
} OSThreadQueue;

#define OS_ACTIVE_THREAD_QUEUE (*(OSThreadQueue*)0x800000DC)
#define OS_FPU_CONTEXT         (*(OSContext**)0x800000D8)

#define MSR_FP  0x2000
#define MSR_FE0 0x0800
#define MSR_FE1 0x0100
#define MSR_RI  0x0002

#define FPSCR_ENABLE 0xF8
#define FPSCR_NI     0x04
#define FPSCR_CLEAR  0x6005F8FF

typedef struct {
	char gpr;
	char fpr;
	char reserved[2];
	char* input_arg_area;
	char* reg_save_area;
} va_list[1];

extern void __builtin_va_info(void*);
extern int vprintf(const char* format, va_list args);
extern void PPCHalt(void);
extern u32 PPCMfmsr(void);
extern void PPCMtmsr(u32 msr);
extern u32 PPCMffpscr(void);
extern void PPCMtfpscr(u32 fpscr);
extern u32 fn_801D2770(void);
extern void OSSaveFPUContext(OSContext* context);
extern void OSLoadContext(OSContext* context);
extern s32 OSDisableScheduler(void);
extern s32 OSEnableScheduler(void);
extern void __OSReschedule(void);

extern volatile OSTime __OSLastInterruptTime;
extern volatile s16 __OSLastInterrupt;
extern volatile u32 __OSLastInterruptSrr0;

#ifdef __MWERKS__
extern volatile u16 __DSPRegs[] : 0xCC005000;
extern volatile u32 __DIRegs[] : 0xCC006000;
#else
extern volatile u16 __DSPRegs[];
extern volatile u32 __DIRegs[];
#endif

OSErrorHandler __OSErrorTable[17];
u32 __OSFpscrEnableBits = FPSCR_ENABLE;

void OSReport(const char* msg, ...)
{
	va_list args;
	__builtin_va_info(&args);
	vprintf(msg, args);
}

void OSPanic(const char* file, int line, const char* msg, ...)
{
	va_list args;
	u32 i;
	u32* p;

	OSDisableInterrupts();
	__builtin_va_info(&args);
	vprintf(msg, args);
	OSReport(" in \"%s\" on line %d.\n", file, line);
	OSReport("\nAddress:      Back Chain    LR Save\n");
	for (i = 0, p = (u32*)fn_801D2770(); p != NULL && (u32)p != 0xFFFFFFFF && i++ < 16;
	    p = (u32*)*p) {
		OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
	}
	PPCHalt();
}

OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler)
{
	OSErrorHandler oldHandler;
	BOOL enabled;

	enabled               = OSDisableInterrupts();
	oldHandler            = __OSErrorTable[error];
	__OSErrorTable[error] = handler;
	if (error == 16) {
		u32 msr = PPCMfmsr();
		u32 fpscr;
		OSThread* thread;
		PPCMtmsr(msr | MSR_FP);
		fpscr = PPCMffpscr();
		if (handler != NULL) {
			for (thread = OS_ACTIVE_THREAD_QUEUE.head; thread != NULL;
			    thread  = thread->linkActive.next) {
				thread->context.srr1 |= MSR_FE0 | MSR_FE1;
				if ((thread->context.state & 1) == 0) {
					s32 i;
					thread->context.state |= 1;
					for (i = 0; i < 32; i++) {
						*(u64*)&thread->context.fpr[i] = (u64)-1;
						*(u64*)&thread->context.psf[i] = (u64)-1;
					}
					thread->context.fpscr = FPSCR_NI;
				}
				thread->context.fpscr |= __OSFpscrEnableBits & FPSCR_ENABLE;
				thread->context.fpscr &= FPSCR_CLEAR;
			}
			fpscr |= __OSFpscrEnableBits & FPSCR_ENABLE;
			msr |= MSR_FE0 | MSR_FE1;
		} else {
			for (thread = OS_ACTIVE_THREAD_QUEUE.head; thread != NULL;
			    thread  = thread->linkActive.next) {
				thread->context.srr1 &= ~(MSR_FE0 | MSR_FE1);
				thread->context.fpscr &= ~FPSCR_ENABLE;
				thread->context.fpscr &= FPSCR_CLEAR;
			}
			fpscr &= ~FPSCR_ENABLE;
			msr &= ~(MSR_FE0 | MSR_FE1);
		}
		fpscr &= FPSCR_CLEAR;
		PPCMtfpscr(fpscr);
		PPCMtmsr(msr);
	}
	OSRestoreInterrupts(enabled);
	return oldHandler;
}

void __OSUnhandledException(u8 exception, OSContext* context, u32 dsisr, u32 dar)
{
	OSTime now = OSGetTime();

	if (!(context->srr1 & MSR_RI)) {
		OSReport("Non-recoverable Exception %d", exception);
	} else {
		if (exception == 6 && (context->srr1 & 0x100000) && __OSErrorTable[16]) {
			u32 msr;
			u32 fpscr;
			exception = 16;
			msr       = PPCMfmsr();
			PPCMtmsr(msr | MSR_FP);
			if (OS_FPU_CONTEXT != NULL) {
				OSSaveFPUContext(OS_FPU_CONTEXT);
			}
			fpscr = PPCMffpscr() & FPSCR_CLEAR;
			PPCMtfpscr(fpscr);
			PPCMtmsr(msr);
			if (OS_FPU_CONTEXT == context) {
				OSDisableScheduler();
				__OSErrorTable[exception](exception, context, dsisr, dar);
				context->srr1 &= ~MSR_FP;
				OS_FPU_CONTEXT = NULL;
				context->fpscr &= FPSCR_CLEAR;
				OSEnableScheduler();
				__OSReschedule();
			} else {
				context->srr1 &= ~MSR_FP;
				OS_FPU_CONTEXT = NULL;
			}
			OSLoadContext(context);
		}
		if (__OSErrorTable[exception] != NULL) {
			OSDisableScheduler();
			__OSErrorTable[exception](exception, context, dsisr, dar);
			OSEnableScheduler();
			__OSReschedule();
			OSLoadContext(context);
		}
		if (exception == 8) {
			OSLoadContext(context);
		}
		OSReport("Unhandled Exception %d", exception);
	}

	OSReport("\n");
	OSDumpContext(context);
	OSReport("\nDSISR = 0x%08x                   DAR  = 0x%08x\n", dsisr, dar);
	OSReport("TB = 0x%016llx\n", now);
	switch (exception) {
		case 2:
			OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
			         "invalid address 0x%x (read from DAR)\n",
			    context->srr0, dar);
			break;
		case 3:
			OSReport("\nAttempted to fetch instruction from invalid address 0x%x "
			         "(read from SRR0)\n",
			    context->srr0);
			break;
		case 5:
			OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
			         "unaligned address 0x%x (read from DAR)\n",
			    context->srr0, dar);
			break;
		case 6:
			OSReport("\nProgram exception : Possible illegal instruction/operation "
			         "at or around 0x%x (read from SRR0)\n",
			    context->srr0, dar);
			break;
		case 15:
			OSReport("\n");
			OSReport("AI DMA Address =   0x%04x%04x\n", __DSPRegs[0x18], __DSPRegs[0x19]);
			OSReport("ARAM DMA Address = 0x%04x%04x\n", __DSPRegs[0x10], __DSPRegs[0x11]);
			OSReport("DI DMA Address =   0x%08x\n", __DIRegs[5]);
			break;
	}
	OSReport("\nLast interrupt (%d): SRR0 = 0x%08x  TB = 0x%016llx\n", __OSLastInterrupt,
	    __OSLastInterruptSrr0, __OSLastInterruptTime);
	PPCHalt();
}
