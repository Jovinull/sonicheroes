#include "types.h"

// The audio interface driver, 0x801DF6E4 to 0x801DFFC8. Identified by the
// AI version string in .data, the 0xCC006C00 audio interface registers and
// the 0xCC005000 DSP-interface AID DMA registers. The original linker
// smart-stripped the unused stream-callback/sample-count/trigger accessors,
// so only the functions present in the DOL are defined here.

#define NULL  0
#define FALSE 0
#define TRUE  1

typedef int BOOL;
typedef s64 OSTime;

typedef void (*AIDCallback)(void);
typedef void (*AISCallback)(u32 count);

typedef struct OSContext {
	u8 pad[0x2C8];
} OSContext;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void (*__OSSetInterruptHandler(s16 interrupt, void (*handler)(s16, OSContext*)))(
    s16, OSContext*);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern void OSClearContext(OSContext* context);
extern void OSSetCurrentContext(OSContext* context);
extern OSTime OSGetTime(void);
extern void OSRegisterVersion(const char* version);

// Bus clock in low memory; the timer clock is a quarter of it. Declared as
// a CW absolute-address variable so the load has symbol identity and CSEs
// across the five conversions.
#ifdef __MWERKS__
u32 __OSBusClock : 0x800000F8;
#else
extern u32 __OSBusClock;
#endif
#define OS_BUS_CLOCK               __OSBusClock
#define OS_TIMER_CLOCK             (OS_BUS_CLOCK / 4)
#define OSNanosecondsToTicks(nsec) (((nsec) * (OS_TIMER_CLOCK / 125000)) / 8000)

#define AI_SAMPLERATE_32KHZ 0
#define AI_SAMPLERATE_48KHZ 1
#define AI_STREAM_STOP      0
#define AI_STREAM_START     1

// The audio interface register block and the DSP interface register block,
// as CW absolute-address arrays.
#ifdef __MWERKS__
volatile u32 __AIRegs[] : 0xCC006C00;
volatile u16 __DSPRegs[] : 0xCC005000;
#else
extern volatile u32 __AIRegs[];
extern volatile u16 __DSPRegs[];
#endif

AIDCallback AIRegisterDMACallback(AIDCallback callback);
void AIInitDMA(u32 start_addr, u32 length);
void AIStartDMA(void);
void AIStopDMA(void);
void AISetStreamPlayState(u32 state);
u32 AIGetStreamPlayState(void);
void AISetDSPSampleRate(u32 rate);
u32 AIGetDSPSampleRate(void);
void AISetStreamSampleRate(u32 rate);
u32 AIGetStreamSampleRate(void);
void AISetStreamVolLeft(u8 volume);
u8 AIGetStreamVolLeft(void);
void AISetStreamVolRight(u8 volume);
u8 AIGetStreamVolRight(void);
void AIInit(u8* stack);

// Stripped accessors: AIInit calls these and the compiler inlines every
// call, so the original object's out-of-line bodies had no incoming
// relocations and the linker smart-stripped them. static inline reproduces
// the expansion without emitting a body.
static inline void AIResetStreamSampleCount(void)
{
	__AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
}

static inline void AISetStreamTrigger(u32 trigger)
{
	__AIRegs[3] = trigger;
}

static void __AISHandler(s16 interrupt, OSContext* context);
static void __AIDHandler(s16 interrupt, OSContext* context);
static void __AICallbackStackSwitch(register AIDCallback cb);
static void __AI_SRC_INIT(void);

// The SDK version banner; the string literal is the unit's only .data.
static char VersionString[]
    = "<< Dolphin SDK - AI\trelease build: Apr 17 2003 12:33:54 (0x2301) >>";
char* __AIVersion = VersionString;

static AISCallback __AIS_Callback;
static AIDCallback __AID_Callback;
static u8* __CallbackStack;
static u8* __OldStack;
static BOOL __AI_init_flag = FALSE;
static volatile BOOL __AID_Active;

static OSTime bound_32KHz;
static OSTime bound_48KHz;
static OSTime min_wait;
static OSTime max_wait;
static OSTime buffer;

AIDCallback AIRegisterDMACallback(AIDCallback callback)
{
	AIDCallback oldCallback;
	BOOL enabled;

	oldCallback    = __AID_Callback;
	enabled        = OSDisableInterrupts();
	__AID_Callback = callback;
	OSRestoreInterrupts(enabled);
	return oldCallback;
}

void AIInitDMA(u32 start_addr, u32 length)
{
	BOOL enabled;

	enabled       = OSDisableInterrupts();
	__DSPRegs[24] = (u16)((__DSPRegs[24] & ~0x3FF) | (start_addr >> 16));
	__DSPRegs[25] = (u16)((__DSPRegs[25] & ~0xFFE0) | (start_addr & 0xFFFF));
	__DSPRegs[27] = (u16)((__DSPRegs[27] & ~0x7FFF) | ((length >> 5) & 0xFFFF));
	OSRestoreInterrupts(enabled);
}

void AIStartDMA(void)
{
	__DSPRegs[27] |= 0x8000;
}

void AIStopDMA(void)
{
	__DSPRegs[27] &= ~0x8000;
}

void AISetStreamPlayState(u32 state)
{
	BOOL enabled;
	u8 volRight;
	u8 volLeft;

	if (state == AIGetStreamPlayState()) {
		return;
	}

	if ((AIGetStreamSampleRate() == AI_SAMPLERATE_32KHZ) && (state == AI_STREAM_START)) {
		volRight = AIGetStreamVolRight();
		volLeft  = AIGetStreamVolLeft();
		AISetStreamVolRight(0);
		AISetStreamVolLeft(0);
		enabled = OSDisableInterrupts();
		__AI_SRC_INIT();
		__AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
		__AIRegs[0] = (__AIRegs[0] & ~0x01) | 0x01;
		OSRestoreInterrupts(enabled);
		// The original restores the right volume into the left channel and
		// vice versa; kept as-is.
		AISetStreamVolLeft(volRight);
		AISetStreamVolRight(volLeft);
	} else {
		__AIRegs[0] = (__AIRegs[0] & ~0x01) | state;
	}
}

u32 AIGetStreamPlayState(void)
{
	return __AIRegs[0] & 0x01;
}

void AISetDSPSampleRate(u32 rate)
{
	u32 playState;
	u8 volLeft;
	u8 volRight;
	BOOL enabled;
	u32 streamRate;

	if (rate == AIGetDSPSampleRate()) {
		return;
	}

	__AIRegs[0] &= ~0x40;

	if (rate == AI_SAMPLERATE_32KHZ) {
		volLeft    = AIGetStreamVolLeft();
		volRight   = AIGetStreamVolRight();
		playState  = __AIRegs[0] & 0x01;
		streamRate = AIGetStreamSampleRate();
		AISetStreamVolLeft(0);
		AISetStreamVolRight(0);
		enabled = OSDisableInterrupts();
		__AI_SRC_INIT();
		__AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
		__AIRegs[0] = (__AIRegs[0] & ~0x02) | (streamRate << 1);
		__AIRegs[0] = (__AIRegs[0] & ~0x01) | playState;
		__AIRegs[0] |= 0x40;
		OSRestoreInterrupts(enabled);
		AISetStreamVolLeft(volLeft);
		AISetStreamVolRight(volRight);
	}
}

u32 AIGetDSPSampleRate(void)
{
	return ((__AIRegs[0] >> 6) & 0x01) ^ 1;
}

void AISetStreamSampleRate(u32 rate)
{
	BOOL enabled;
	u32 playState;
	u8 volLeft;
	u8 volRight;
	u32 dspRateBit;

	if (rate == AIGetStreamSampleRate()) {
		return;
	}

	playState = AIGetStreamPlayState();
	volLeft   = AIGetStreamVolLeft();
	volRight  = AIGetStreamVolRight();
	AISetStreamVolRight(0);
	AISetStreamVolLeft(0);
	dspRateBit = __AIRegs[0] & 0x40;
	__AIRegs[0] &= ~0x40;
	enabled = OSDisableInterrupts();
	__AI_SRC_INIT();
	__AIRegs[0] |= dspRateBit;
	__AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
	__AIRegs[0] = (__AIRegs[0] & ~0x02) | (rate << 1);
	OSRestoreInterrupts(enabled);
	AISetStreamPlayState(playState);
	AISetStreamVolLeft(volLeft);
	AISetStreamVolRight(volRight);
}

u32 AIGetStreamSampleRate(void)
{
	return (__AIRegs[0] >> 1) & 0x01;
}

void AISetStreamVolLeft(u8 volume)
{
	__AIRegs[1] = (__AIRegs[1] & ~0x000000FF) | (volume & 0xFF);
}

u8 AIGetStreamVolLeft(void)
{
	return (u8)(__AIRegs[1] & 0xFF);
}

void AISetStreamVolRight(u8 volume)
{
	__AIRegs[1] = (__AIRegs[1] & ~0x0000FF00) | ((volume & 0xFF) << 8);
}

u8 AIGetStreamVolRight(void)
{
	return (u8)((__AIRegs[1] >> 8) & 0xFF);
}

void AIInit(u8* stack)
{
	if (__AI_init_flag == TRUE) {
		return;
	}

	OSRegisterVersion(__AIVersion);

	bound_32KHz = OSNanosecondsToTicks(31524);
	bound_48KHz = OSNanosecondsToTicks(42024);
	min_wait    = OSNanosecondsToTicks(42000);
	max_wait    = OSNanosecondsToTicks(63000);
	buffer      = OSNanosecondsToTicks(3000);

	AISetStreamVolRight(0);
	AISetStreamVolLeft(0);
	AISetStreamTrigger(0);
	AIResetStreamSampleCount();

	AISetStreamSampleRate(AI_SAMPLERATE_48KHZ);
	AISetDSPSampleRate(AI_SAMPLERATE_32KHZ);

	__AIS_Callback  = NULL;
	__AID_Callback  = NULL;
	__CallbackStack = stack;

	__OSSetInterruptHandler(5, __AIDHandler);
	__OSUnmaskInterrupts(0x04000000);
	__OSSetInterruptHandler(8, __AISHandler);
	__OSUnmaskInterrupts(0x00800000);

	__AI_init_flag = TRUE;
}

static void __AISHandler(s16 interrupt, OSContext* context)
{
	OSContext exceptionContext;

	__AIRegs[0] |= 0x08;
	OSClearContext(&exceptionContext);
	OSSetCurrentContext(&exceptionContext);
	if (__AIS_Callback) {
		(*__AIS_Callback)(__AIRegs[2]);
	}
	OSClearContext(&exceptionContext);
	OSSetCurrentContext(context);
}

static void __AIDHandler(s16 interrupt, OSContext* context)
{
	OSContext exceptionContext;
	u16 tmp;

	tmp          = __DSPRegs[5];
	tmp          = (u16)((tmp & ~0xA0) | 0x08);
	__DSPRegs[5] = tmp;
	OSClearContext(&exceptionContext);
	OSSetCurrentContext(&exceptionContext);
	if (__AID_Callback) {
		if (!__AID_Active) {
			__AID_Active = TRUE;
			if (__CallbackStack) {
				__AICallbackStackSwitch(__AID_Callback);
			} else {
				(*__AID_Callback)();
			}
			__AID_Active = FALSE;
		}
	}
	OSClearContext(&exceptionContext);
	OSSetCurrentContext(context);
}

#ifdef __MWERKS__
// Runs the DMA callback on the dedicated callback stack. Pure register and
// stack-pointer surgery; C cannot express the stack switch.
// clang-format off
static asm void __AICallbackStackSwitch(register AIDCallback cb)
{
	nofralloc
	mflr  r0
	stw   r0, 4(r1)
	stwu  r1, -0x18(r1)
	stw   r31, 0x14(r1)
	mr    r31, r3
	lis   r5, __OldStack@ha
	addi  r5, r5, __OldStack@l
	stw   r1, 0(r5)
	lis   r5, __CallbackStack@ha
	addi  r5, r5, __CallbackStack@l
	lwz   r1, 0(r5)
	subi  r1, r1, 8
	mtlr  r31
	blrl
	lis   r5, __OldStack@ha
	addi  r5, r5, __OldStack@l
	lwz   r1, 0(r5)
	lwz   r0, 0x1C(r1)
	lwz   r31, 0x14(r1)
	addi  r1, r1, 0x18
	mtlr  r0
	blr
}
// clang-format on
#else
static void __AICallbackStackSwitch(AIDCallback cb)
{
	(*cb)();
}
#endif

// Walks the stream sample rate converter into a known state: run one
// 32 kHz-to-48 kHz counter step, time it, and retry until the step lands
// inside the expected window, then hold off for the measured wait.
static void __AI_SRC_INIT(void)
{
	OSTime t1;
	OSTime t2 = 0;
	OSTime diff;
	unsigned long done = 0;
	unsigned long sampleCount;
	OSTime wait = 0;
	// Dead stack: the original frame is 16 bytes wider.
	u32 pad[4];

	while (!done) {
		__AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
		__AIRegs[0] = __AIRegs[0] & ~0x02;
		__AIRegs[0] = (__AIRegs[0] & ~0x01) | 0x01;

		sampleCount = __AIRegs[2];
		while (sampleCount == __AIRegs[2]) {
		}
		t1 = OSGetTime();

		__AIRegs[0] = (__AIRegs[0] & ~0x02) | 0x02;
		__AIRegs[0] = (__AIRegs[0] & ~0x01) | 0x01;

		sampleCount = __AIRegs[2];
		while (sampleCount == __AIRegs[2]) {
		}
		t2          = OSGetTime();
		diff        = t2 - t1;
		__AIRegs[0] = __AIRegs[0] & ~0x02;
		__AIRegs[0] = __AIRegs[0] & ~0x01;

		if (diff < (bound_32KHz - buffer)) {
			wait = min_wait;
			done = 1;
		} else if ((diff >= (bound_32KHz + buffer)) && (diff < (bound_48KHz - buffer))) {
			wait = max_wait;
			done = 1;
		} else {
			done = 0;
		}
	}

	t1 = t2 + wait;
	while (OSGetTime() < t1) {
	}
}
