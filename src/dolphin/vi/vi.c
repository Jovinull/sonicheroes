#include "types.h"

// The video interface driver, 0x801DBD0C to 0x801DDB58. Identified by the
// VI version string leading the unit's .data, the 0xCC002000 register
// window, the SDK timing tables and the retrace machinery that feeds
// SIRefreshSamplingRate. The original linker smart-stripped the unused
// entry points (VIConfigurePan, VIGetRetraceCount, VIGetCurrentTvMode,
// VISetTeletextEnable and friends); only the functions present in the DOL
// are defined here.

#define NULL  0
#define FALSE 0
#define TRUE  1

typedef int BOOL;
typedef s64 OSTime;
typedef volatile u32 vu32;

typedef struct OSContext {
	u8 pad[0x2C8];
} OSContext;

typedef struct OSThreadQueue {
	void* head;
	void* tail;
} OSThreadQueue;

typedef void (*VIRetraceCallback)(u32 retraceCount);
typedef void (*VIPositionCallback)(s16 displayX, s16 displayY);

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void (*__OSSetInterruptHandler(s16 interrupt, void (*handler)(s16, OSContext*)))(
    s16, OSContext*);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern void OSClearContext(OSContext* context);
extern void OSSetCurrentContext(OSContext* context);
extern void OSRegisterVersion(const char* version);
extern void OSInitThreadQueue(OSThreadQueue* queue);
extern void OSSleepThread(OSThreadQueue* queue);
extern void OSWakeupThread(OSThreadQueue* queue);
extern void OSReport(const char* msg, ...);
extern void OSPanic(const char* file, int line, const char* msg, ...);
extern void SIRefreshSamplingRate(void);

// SRAM control: only the display offset byte is wanted here.
typedef struct OSSram {
	u16 checkSum;      // 0x00
	u16 checkSumInv;   // 0x02
	u32 ead0;          // 0x04
	u32 ead1;          // 0x08
	u32 counterBias;   // 0x0C
	s8 displayOffsetH; // 0x10
	u8 ntd;            // 0x11
	u8 language;       // 0x12
	u8 flags;          // 0x13
} OSSram;
extern OSSram* __OSLockSram(void);
extern BOOL __OSUnlockSram(BOOL commit);

// The video interface register block as a CW absolute-address array.
#ifdef __MWERKS__
volatile u16 __VIRegs[] : 0xCC002000;
#else
extern volatile u16 __VIRegs[];
#endif

// TV format in low memory, as a CW absolute-address variable (symbol
// identity lets loads hoist across unrelated stores).
#ifdef __MWERKS__
u32 __OSTvFormat : 0x800000CC;
#else
extern u32 __OSTvFormat;
#endif
#define OS_TV_FORMAT __OSTvFormat

typedef struct VITiming {
	u8 equ;         // 0x00
	u16 acv;        // 0x02
	u16 prbOdd;     // 0x04
	u16 prbEven;    // 0x06
	u16 psbOdd;     // 0x08
	u16 psbEven;    // 0x0A
	u8 bs1;         // 0x0C
	u8 bs2;         // 0x0D
	u8 bs3;         // 0x0E
	u8 bs4;         // 0x0F
	u16 be1;        // 0x10
	u16 be2;        // 0x12
	u16 be3;        // 0x14
	u16 be4;        // 0x16
	u16 nhlines;    // 0x18
	u16 hlw;        // 0x1A
	u8 hsy;         // 0x1C
	u8 hcs;         // 0x1D
	u8 hce;         // 0x1E
	u8 hbe640;      // 0x1F
	u16 hbs640;     // 0x20
	u8 hbeCCIR656;  // 0x22
	u16 hbsCCIR656; // 0x24
} VITiming;

#define VI_TVMODE(format, mode) (((format) << 2) + (mode))

// GX render mode object; only the fields VIConfigure reads are typed.
typedef struct GXRenderModeObj {
	long viTVmode; // 0x00
	u16 fbWidth;   // 0x04
	u16 efbHeight; // 0x06
	u16 xfbHeight; // 0x08
	u16 viXOrigin; // 0x0A
	u16 viYOrigin; // 0x0C
	u16 viWidth;   // 0x0E
	u16 viHeight;  // 0x10
	long xFBmode;  // 0x14
} GXRenderModeObj;

typedef struct HorVerTyp HorVerTyp;

static inline u32 getEncoderType(void);
static void __VIRetraceHandler(s16 interrupt, OSContext* context);
static VITiming* getTiming(u32 mode);
static void __VIInit(long mode);
static void setFbbRegs(HorVerTyp* hv_, u32* tfbb, u32* bfbb, u32* rtfbb, u32* rbfbb);
static void setVerticalRegs(u16 dispPosY, u16 dispSizeY, u8 equ, u16 acv, u16 prbOdd, u16 prbEven,
    u16 psbOdd, u16 psbEven, BOOL black);
void __VIDisplayPositionToXY(u32 hct, u32 vct, s16* x, s16* y);
void __VIGetCurrentPosition(s16* x, s16* y);
static void getCurrentHalfLine(u32* hcount, u32* vcount);
static u32 getCurrentFieldEvenOdd(void);
u32 VIGetTvFormat(void);
u32 VIGetDTVStatus(void);
BOOL VIGetNextField(void);
u32 VIGetCurrentLine(void);
void VIFlush(void);
void VISetNextFrameBuffer(void* fb);
void VISetBlack(BOOL black);

// The SDK version banner; the string literal anchors the unit's .data.
static char VersionString[]
    = "<< Dolphin SDK - VI\trelease build: Apr 17 2003 12:33:22 (0x2301) >>";
char* __VIVersion = VersionString;

// Timing sets, one per TV standard and scan mode, followed by the filter
// taps VIInit programs and the getTiming dispatch table (emitted by the
// compiler).
static VITiming timing[10] = {
	{ 6, 240, 24, 25, 3, 2, 12, 13, 12, 13, 520, 519, 520, 519, 525, 429, 64, 71, 105, 162, 373,
	    122, 412 },
	{ 6, 240, 24, 24, 4, 4, 12, 12, 12, 12, 520, 520, 520, 520, 526, 429, 64, 71, 105, 162, 373,
	    122, 412 },
	{ 5, 287, 35, 36, 1, 0, 13, 12, 11, 10, 619, 618, 617, 620, 625, 432, 64, 75, 106, 172, 380,
	    133, 420 },
	{ 5, 287, 33, 33, 2, 2, 13, 11, 13, 11, 619, 621, 619, 621, 624, 432, 64, 75, 106, 172, 380,
	    133, 420 },
	{ 6, 240, 24, 25, 3, 2, 16, 15, 14, 13, 518, 517, 516, 519, 525, 429, 64, 78, 112, 162, 373,
	    122, 412 },
	{ 6, 240, 24, 24, 4, 4, 16, 14, 16, 14, 518, 520, 518, 520, 526, 429, 64, 78, 112, 162, 373,
	    122, 412 },
	{ 12, 480, 48, 48, 6, 6, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 162,
	    373, 122, 412 },
	{ 12, 480, 44, 44, 10, 10, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 168,
	    379, 122, 412 },
	{ 6, 241, 24, 25, 1, 0, 12, 13, 12, 13, 520, 519, 520, 519, 525, 429, 64, 71, 105, 159, 370,
	    122, 412 },
	{ 12, 480, 48, 48, 6, 6, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 180,
	    391, 122, 412 },
};

static u16 taps[25] = {
	0x01F0,
	0x01DC,
	0x01AE,
	0x0174,
	0x0129,
	0x00DB,
	0x008E,
	0x0046,
	0x000C,
	0x00E2,
	0x00CB,
	0x00C0,
	0x00C4,
	0x00CF,
	0x00DE,
	0x00EC,
	0x00FC,
	0x0008,
	0x000F,
	0x0013,
	0x0013,
	0x000F,
	0x000C,
	0x0008,
	0x0001,
};

// Register block image, its shadow, and the current configuration.
static u16 regs[59];
static u16 shdwRegs[59];
struct HorVerTyp {
	u16 DispPosX;          // 0x00
	u16 DispPosY;          // 0x02
	u16 DispSizeX;         // 0x04
	u16 DispSizeY;         // 0x06
	u16 AdjustedDispPosX;  // 0x08
	u16 AdjustedDispPosY;  // 0x0A
	u16 AdjustedDispSizeY; // 0x0C
	u16 AdjustedPanPosY;   // 0x0E
	u16 AdjustedPanSizeY;  // 0x10
	u16 FBSizeX;           // 0x12
	u16 FBSizeY;           // 0x14
	u16 PanPosX;           // 0x16
	u16 PanPosY;           // 0x18
	u16 PanSizeX;          // 0x1A
	u16 PanSizeY;          // 0x1C
	u16 pad1E;             // 0x1E
	long FBMode;           // 0x20
	u32 nonInter;          // 0x24
	u32 tv;                // 0x28
	u8 wordPerLine;        // 0x2C
	u8 std;                // 0x2D
	u8 wpl;                // 0x2E
	u8 pad2F;              // 0x2F
	u32 bufAddr;           // 0x30
	u32 tfbb;              // 0x34
	u32 bfbb;              // 0x38
	u8 xof;                // 0x3C
	u8 pad3D[3];           // 0x3D
	BOOL black;            // 0x40
	BOOL threeD;           // 0x44
	u32 rbufAddr;          // 0x48
	u32 rtfbb;             // 0x4C
	u32 rbfbb;             // 0x50
	VITiming* timing;      // 0x54
};

static HorVerTyp HorVer;

// File-local state, in declaration (= .sbss) order.
static BOOL IsInited; // guessed name: VIInit run-once latch
static volatile u32 retraceCount;
static u32 FlushFlag;
static OSThreadQueue retraceQueue;
static VIRetraceCallback PreCB;
static VIRetraceCallback PostCB;
static VIPositionCallback PositionCallback;
static u32 encoderType;
static s16 displayOffsetH;
static s16 displayOffsetV;
static volatile u32 changeMode;
static volatile u64 changed;
static volatile u32 shdwChangeMode;
static volatile u64 shdwChanged;
static VITiming* CurrTiming;
static u32 CurrTvMode;
static u32 NextBufAddr;
static u32 CurrBufAddr;
static u32 FBSet;        // guessed name: set once a frame buffer is registered
static u32 unk_8042CCD4; // referenced only by VIConfigure; identity unknown

#define VI_BITMASK(index) ((u64)1 << (63 - (index)))

#define SET_REG(index, value)                                                                      \
	do {                                                                                           \
		regs[(index)] = (value);                                                                   \
		changed |= VI_BITMASK(index);                                                              \
	} while (0)

#define MARK_CHANGED(index) (changed |= VI_BITMASK(index))

#ifdef __MWERKS__
#define CNTLZW(x) __cntlzw(x)
#else
#define CNTLZW(x) __builtin_clz(x)
#endif

static inline u32 cntlzd(u64 bit)
{
	u32 hi     = (u32)(bit >> 32);
	u32 lo     = (u32)(bit & 0xFFFFFFFF);
	long value = CNTLZW(hi);

	if (value < 32) {
		return value;
	}
	return 32 + CNTLZW(lo);
}

static inline u32 getEncoderType(void)
{
	return 1;
}

static void __VIRetraceHandler(s16 interrupt, OSContext* context)
{
	OSContext exceptionContext;
	s16 displayX;
	s16 displayY;
	u16 reg;
	u32 inter = 0;
	u32 index;

	reg = __VIRegs[24];
	if (reg & 0x8000) {
		__VIRegs[24] = (u16)(reg & ~0x8000);
		inter |= 1;
	}
	reg = __VIRegs[26];
	if (reg & 0x8000) {
		__VIRegs[26] = (u16)(reg & ~0x8000);
		inter |= 2;
	}
	reg = __VIRegs[28];
	if (reg & 0x8000) {
		__VIRegs[28] = (u16)(reg & ~0x8000);
		inter |= 4;
	}
	reg = __VIRegs[30];
	if (reg & 0x8000) {
		__VIRegs[30] = (u16)(reg & ~0x8000);
		inter |= 8;
	}

	if ((inter & 4) || (inter & 8)) {
		OSClearContext(&exceptionContext);
		OSSetCurrentContext(&exceptionContext);
		if (PositionCallback) {
			__VIGetCurrentPosition(&displayX, &displayY);
			(*PositionCallback)(displayX, displayY);
		}
		OSClearContext(&exceptionContext);
		OSSetCurrentContext(context);
		return;
	}

	retraceCount++;
	OSClearContext(&exceptionContext);
	OSSetCurrentContext(&exceptionContext);
	if (PreCB) {
		(*PreCB)(retraceCount);
	}

	if (FlushFlag) {
		BOOL flushDone;
		if (shdwChangeMode != 1 || getCurrentFieldEvenOdd()) {
			while (shdwChanged) {
				index           = cntlzd(shdwChanged);
				__VIRegs[index] = shdwRegs[index];
				shdwChanged &= ~VI_BITMASK(index);
			}
			shdwChangeMode = 0;
			CurrTiming     = HorVer.timing;
			CurrTvMode     = HorVer.tv;
			CurrBufAddr    = NextBufAddr;
			flushDone      = TRUE;
		} else {
			flushDone = FALSE;
		}
		if (flushDone) {
			FlushFlag = 0;
			SIRefreshSamplingRate();
		}
	}

	if (PostCB) {
		OSClearContext(&exceptionContext);
		(*PostCB)(retraceCount);
	}

	OSWakeupThread(&retraceQueue);
	OSClearContext(&exceptionContext);
	OSSetCurrentContext(context);
}

VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback callback)
{
	VIRetraceCallback oldCallback;
	BOOL enabled;

	oldCallback = PreCB;
	enabled     = OSDisableInterrupts();
	PreCB       = callback;
	OSRestoreInterrupts(enabled);
	return oldCallback;
}

VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback callback)
{
	VIRetraceCallback oldCallback;
	BOOL enabled;

	oldCallback = PostCB;
	enabled     = OSDisableInterrupts();
	PostCB      = callback;
	OSRestoreInterrupts(enabled);
	return oldCallback;
}

static VITiming* getTiming(u32 mode)
{
	switch (mode) {
		case VI_TVMODE(0, 0): // NTSC interlace
			return &timing[0];
		case VI_TVMODE(0, 1): // NTSC double strike
			return &timing[1];
		case VI_TVMODE(1, 0): // PAL interlace
			return &timing[2];
		case VI_TVMODE(1, 1): // PAL double strike
			return &timing[3];
		case VI_TVMODE(5, 0): // EURGB60 interlace
			return &timing[0];
		case VI_TVMODE(5, 1): // EURGB60 double strike
			return &timing[1];
		case VI_TVMODE(2, 0): // MPAL interlace
			return &timing[4];
		case VI_TVMODE(2, 1): // MPAL double strike
			return &timing[5];
		case VI_TVMODE(0, 2): // NTSC progressive
			return &timing[6];
		case VI_TVMODE(0, 3): // NTSC 3D
			return &timing[7];

		case VI_TVMODE(4, 0): // DEBUG PAL interlace
			return &timing[2];
		case VI_TVMODE(4, 1): // DEBUG PAL double strike
			return &timing[3];
		case VI_TVMODE(6, 0):
			return &timing[8];
		case VI_TVMODE(6, 2):
			return &timing[9];
		default:
			return NULL;
	}
}

static void __VIInit(long mode)
{
	VITiming* tm;
	u32 nonInter;
	u32 tv;
	vu32 a;
	// Dead stack: the original locals sit higher in the frame.
	u32 pad[3];

	nonInter = mode & 2;
	tv       = (u32)mode >> 2;

	OS_TV_FORMAT = tv;

	tm = getTiming(mode);

	__VIRegs[1] = 2;
	a           = 0;
	if (a < 1000) {
		while (a < 1000) {
			a = a + 8;
		}
	}
	__VIRegs[1] = 0;

	__VIRegs[3]  = tm->hlw;
	__VIRegs[2]  = (u16)(tm->hce | (tm->hcs << 8));
	__VIRegs[5]  = (u16)(tm->hsy | (tm->hbe640 << 7));
	__VIRegs[4]  = (u16)(tm->hbs640 << 1);
	__VIRegs[0]  = tm->equ;
	__VIRegs[7]  = (u16)(tm->prbOdd + tm->acv * 2 - 2);
	__VIRegs[6]  = (u16)(tm->psbOdd + 2);
	__VIRegs[9]  = (u16)(tm->prbEven + tm->acv * 2 - 2);
	__VIRegs[8]  = (u16)(tm->psbEven + 2);
	__VIRegs[11] = (u16)(tm->bs1 | (tm->be1 << 5));
	__VIRegs[10] = (u16)(tm->bs3 | (tm->be3 << 5));
	__VIRegs[13] = (u16)(tm->bs2 | (tm->be2 << 5));
	__VIRegs[12] = (u16)(tm->bs4 | (tm->be4 << 5));
	__VIRegs[36] = 0x2828;
	__VIRegs[27] = 1;
	__VIRegs[26] = 0x1001;
	{
		u16 hct;
		u16 vct;
		hct          = tm->hlw + 1;
		vct          = (tm->nhlines / 2) + 1;
		__VIRegs[25] = (u16)(u32)hct;
		__VIRegs[24] = (u16)(vct | 0x1000);
	}

	if (mode != VI_TVMODE(0, 2) && mode != VI_TVMODE(0, 3) && mode != VI_TVMODE(6, 2)) {
		__VIRegs[1]  = (u16)(((nonInter << 2) | 1) | (tv << 8));
		__VIRegs[54] = 0;
	} else {
		__VIRegs[1]  = (u16)((tv << 8) | 5);
		__VIRegs[54] = 1;
	}
}

// AdjustPosition: clamps the configured display window into the hardware
// window using the SRAM display offset. Fully inlined at its call sites.
static inline void AdjustPosition(u16 acv)
{
	long coeff, frac;

	HorVer.AdjustedDispPosX = (u16)(((s16)HorVer.DispPosX + displayOffsetH > 720 - HorVer.DispSizeX)
	        ? 720 - HorVer.DispSizeX
	        : ((s16)HorVer.DispPosX + displayOffsetH < 0) ? 0
	                                                      : (s16)HorVer.DispPosX + displayOffsetH);

	coeff = (HorVer.FBMode == 0) ? 2 : 1;
	frac  = HorVer.DispPosY & 1;

	HorVer.AdjustedDispPosY = (u16)(((s16)HorVer.DispPosY + displayOffsetV > frac)
	        ? (s16)HorVer.DispPosY + displayOffsetV
	        : frac);

	HorVer.AdjustedDispSizeY = (u16)(HorVer.DispSizeY
	    + (((s16)HorVer.DispPosY + displayOffsetV - frac < 0)
	            ? (s16)HorVer.DispPosY + displayOffsetV - frac
	            : 0)
	    - (((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + displayOffsetV - ((s16)acv * 2 - frac)
	           > 0)
	            ? (s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + displayOffsetV
	                - ((s16)acv * 2 - frac)
	            : 0));

	HorVer.AdjustedPanPosY = (u16)(HorVer.PanPosY
	    - (((s16)HorVer.DispPosY + displayOffsetV - frac < 0)
	              ? (s16)HorVer.DispPosY + displayOffsetV - frac
	              : 0)
	        / coeff);

	HorVer.AdjustedPanSizeY = (u16)(HorVer.PanSizeY
	    + (((s16)HorVer.DispPosY + displayOffsetV - frac < 0)
	              ? (s16)HorVer.DispPosY + displayOffsetV - frac
	              : 0)
	        / coeff
	    - (((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + displayOffsetV - ((s16)acv * 2 - frac)
	           > 0)
	              ? (s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + displayOffsetV
	                  - ((s16)acv * 2 - frac)
	              : 0)
	        / coeff);
}

void VIInit(void)
{
	u16 dspCfg;
	u32 tv;
	u32 tvInBootrom;
	VITiming* tm;

	if (IsInited != 0) {
		return;
	}

	OSRegisterVersion(__VIVersion);
	IsInited    = 1;
	encoderType = 1;

	if (!(__VIRegs[1] & 1)) {
		__VIInit(VI_TVMODE(0, 0));
	}

	retraceCount   = 0;
	changed        = 0;
	shdwChanged    = 0;
	changeMode     = 0;
	shdwChangeMode = 0;
	FlushFlag      = 0;

	__VIRegs[39] = (u16)(taps[0] | ((taps[1] & 0x3F) << 10));
	__VIRegs[38] = (u16)((taps[1] >> 6) | (taps[2] << 4));
	__VIRegs[41] = (u16)(taps[3] | ((taps[4] & 0x3F) << 10));
	__VIRegs[40] = (u16)((taps[4] >> 6) | (taps[5] << 4));
	__VIRegs[43] = (u16)(taps[6] | ((taps[7] & 0x3F) << 10));
	__VIRegs[42] = (u16)((taps[7] >> 6) | (taps[8] << 4));
	__VIRegs[45] = (u16)(taps[9] | (taps[10] << 8));
	__VIRegs[44] = (u16)(taps[11] | (taps[12] << 8));
	__VIRegs[47] = (u16)(taps[13] | (taps[14] << 8));
	__VIRegs[46] = (u16)(taps[15] | (taps[16] << 8));
	__VIRegs[49] = (u16)(taps[17] | (taps[18] << 8));
	__VIRegs[48] = (u16)(taps[19] | (taps[20] << 8));
	__VIRegs[51] = (u16)(taps[21] | (taps[22] << 8));
	__VIRegs[50] = (u16)(taps[23] | (taps[24] << 8));
	__VIRegs[56] = 640;

	displayOffsetH = (s8)__OSLockSram()->displayOffsetH;
	displayOffsetV = 0;
	__OSUnlockSram(FALSE);

	dspCfg      = __VIRegs[1];
	tvInBootrom = OS_TV_FORMAT;

	HorVer.nonInter = (dspCfg >> 2) & 1;
	HorVer.tv       = ((u32)dspCfg & 0x300) >> 8;

	if (tvInBootrom == 1 && HorVer.tv == 0) {
		HorVer.tv = 5;
	}

	tv            = (HorVer.tv == 3) ? 0 : HorVer.tv;
	tm            = getTiming(VI_TVMODE(tv, 0) + HorVer.nonInter);
	HorVer.timing = tm;

	regs[1] = dspCfg;

	CurrTiming = HorVer.timing;
	CurrTvMode = HorVer.tv;

	HorVer.DispSizeX = 640;
	HorVer.DispSizeY = (u16)(CurrTiming->acv * 2);
	HorVer.DispPosX  = (u16)((720 - HorVer.DispSizeX) / 2);
	HorVer.DispPosY  = 0;

	AdjustPosition(CurrTiming->acv);

	HorVer.FBSizeX     = 640;
	HorVer.FBSizeY     = (u16)(CurrTiming->acv * 2);
	HorVer.PanPosX     = 0;
	HorVer.PanPosY     = 0;
	HorVer.PanSizeX    = 640;
	HorVer.PanSizeY    = (u16)(CurrTiming->acv * 2);
	HorVer.FBMode      = 0;
	HorVer.wordPerLine = 40;
	HorVer.std         = 40;
	HorVer.wpl         = 40;
	HorVer.xof         = 0;
	HorVer.black       = TRUE;
	HorVer.threeD      = FALSE;

	OSInitThreadQueue(&retraceQueue);

	__VIRegs[24] = (u16)(__VIRegs[24] & 0x7FFF);
	__VIRegs[26] = (u16)(__VIRegs[26] & 0x7FFF);

	PreCB  = NULL;
	PostCB = NULL;

	__OSSetInterruptHandler(24, __VIRetraceHandler);
	__OSUnmaskInterrupts(0x80);
}

void VIWaitForRetrace(void)
{
	BOOL enabled;
	u32 count;

	enabled = OSDisableInterrupts();
	count   = retraceCount;
	do {
		OSSleepThread(&retraceQueue);
	} while (count == retraceCount);
	OSRestoreInterrupts(enabled);
}

// calcFbbs is fully inlined into setFbbRegs (no out-of-line body in the DOL).
static inline void calcFbbs(u32 bufAddr, u16 panPosX, u16 panPosY, u8 wordPerLine, long xfbMode,
    u16 dispPosY, u32* tfbb, u32* bfbb)
{
	u32 bytesPerLine;
	u32 xoffInWords;
	u32 tmp;

	xoffInWords  = (panPosX & ~0xF) >> 4;
	bytesPerLine = (wordPerLine & 0xFF) << 5;
	*tfbb        = bufAddr + (xoffInWords << 5) + (bytesPerLine * panPosY);
	*bfbb        = (xfbMode == 0) ? *tfbb : *tfbb + bytesPerLine;
	if (dispPosY % 2 == 1) {
		tmp   = *tfbb;
		*tfbb = *bfbb;
		*bfbb = tmp;
	}
	*tfbb &= 0x3FFFFFFF;
	*bfbb &= 0x3FFFFFFF;
}

static void setFbbRegs(HorVerTyp* hv, u32* tfbb, u32* bfbb, u32* rtfbb, u32* rbfbb)
{
	u32 shifted;

	calcFbbs(hv->bufAddr, hv->PanPosX, hv->AdjustedPanPosY, hv->wordPerLine, hv->FBMode,
	    hv->AdjustedDispPosY, tfbb, bfbb);
	if (hv->threeD) {
		calcFbbs(hv->rbufAddr, hv->PanPosX, hv->AdjustedPanPosY, hv->wordPerLine, hv->FBMode,
		    hv->AdjustedDispPosY, rtfbb, rbfbb);
	}

	if (*tfbb < 0x01000000U && *bfbb < 0x01000000U && *rtfbb < 0x01000000U
	    && *rbfbb < 0x01000000U) {
		shifted = 0;
	} else {
		shifted = 1;
	}

	if (shifted) {
		*tfbb >>= 5;
		*bfbb >>= 5;
		*rtfbb >>= 5;
		*rbfbb >>= 5;
	}

	regs[15] = (u16)*tfbb & 0xFFFF;
	MARK_CHANGED(15);
	regs[14] = (shifted << 12) | ((*tfbb >> 16) | (hv->xof << 8));
	MARK_CHANGED(14);
	regs[19] = (u16)*bfbb & 0xFFFF;
	MARK_CHANGED(19);
	regs[18] = (*bfbb >> 16);
	MARK_CHANGED(18);

	if (hv->threeD) {
		regs[17] = (u16)*rtfbb & 0xFFFF;
		MARK_CHANGED(17);
		regs[16] = *rtfbb >> 16;
		MARK_CHANGED(16);
		regs[21] = (u16)*rbfbb & 0xFFFF;
		MARK_CHANGED(21);
		regs[20] = *rbfbb >> 16;
		MARK_CHANGED(20);
	}
}

static void setVerticalRegs(u16 dispPosY, u16 dispSizeY, u8 equ, u16 acv, u16 prbOdd, u16 prbEven,
    u16 psbOdd, u16 psbEven, BOOL black)
{
	u16 actualPrbOdd;
	u16 actualPrbEven;
	u16 actualPsbOdd;
	u16 actualPsbEven;
	u16 actualAcv;
	u16 c;
	u16 d;

	if (regs[54] & 1) {
		c = 1;
		d = 2;
	} else {
		c = 2;
		d = 1;
	}

	if ((dispPosY % 2) == 0) {
		actualPrbOdd  = prbOdd + (d * dispPosY);
		actualPsbOdd  = psbOdd + (d * (((c * acv) - dispSizeY) - dispPosY));
		actualPrbEven = prbEven + (d * dispPosY);
		actualPsbEven = psbEven + (d * (((c * acv) - dispSizeY) - dispPosY));
	} else {
		actualPrbOdd  = prbEven + (d * dispPosY);
		actualPsbOdd  = psbEven + (d * (((c * acv) - dispSizeY) - dispPosY));
		actualPrbEven = prbOdd + (d * dispPosY);
		actualPsbEven = psbOdd + (d * (((c * acv) - dispSizeY) - dispPosY));
	}

	actualAcv = dispSizeY / c;

	if (black) {
		actualPrbOdd += 2 * actualAcv - 2;
		actualPsbOdd += 2;
		actualPrbEven += 2 * actualAcv - 2;
		actualPsbEven += 2;
		actualAcv = 0;
	}

	regs[0] = equ | (actualAcv << 4);
	MARK_CHANGED(0);
	regs[7] = (u16)(u32)actualPrbOdd;
	MARK_CHANGED(7);
	regs[6] = (u16)(u32)actualPsbOdd;
	MARK_CHANGED(6);
	regs[9] = (u16)(u32)actualPrbEven;
	MARK_CHANGED(9);
	regs[8] = (u16)(u32)actualPsbEven;
	MARK_CHANGED(8);
}

// The helpers below are fully inlined into VIConfigure in the DOL
// (function-level dead stripping removed the out-of-line bodies together
// with VIConfigurePan, their only other caller).

static inline void setInterruptRegs(VITiming* tm)
{
	u16 hct;
	u16 vct;

	vct = tm->nhlines / 2;
	if ((u16)(tm->nhlines % 2) != 0) {
		hct = tm->hlw;
	} else {
		hct = 0;
	}
	vct++;
	hct++;
	regs[25] = (u16)(u32)hct;
	MARK_CHANGED(25);
	regs[24] = vct | 0x1000;
	MARK_CHANGED(24);

	vct; // fixes regalloc
}

static inline void setScalingRegs(u16 panSizeX, u16 dispSizeX, BOOL threeD)
{
	u32 scale;

	panSizeX = threeD ? (panSizeX << 1) : panSizeX;
	if (panSizeX < dispSizeX) {
		scale    = (u32)(dispSizeX + (panSizeX << 8) - 1) / dispSizeX;
		regs[37] = scale | 0x1000;
		MARK_CHANGED(37);
		regs[56] = (u32)panSizeX;
		MARK_CHANGED(56);
	} else {
		regs[37] = 0x100;
		MARK_CHANGED(37);
	}
}

static inline void setHorizontalRegs(VITiming* tm, u16 dispPosX, u16 dispSizeX)
{
	u32 hbe;
	u32 hbs;
	u32 hbeLo;
	u32 hbeHi;

	regs[3] = (u16)(u32)tm->hlw;
	MARK_CHANGED(3);
	regs[2] = tm->hce | (tm->hcs << 8);
	MARK_CHANGED(2);
	hbe     = tm->hbe640 - 40 + dispPosX;
	hbs     = tm->hbs640 + 40 + dispPosX - (720 - dispSizeX);
	hbeLo   = hbe & 0x1FF;
	hbeHi   = hbe >> 9;
	regs[5] = tm->hsy | (hbeLo << 7);
	MARK_CHANGED(5);
	regs[4] = hbeHi | (hbs * 2);
	MARK_CHANGED(4);
}

static inline void setBBIntervalRegs(VITiming* tm)
{
	regs[11] = tm->bs1 | (tm->be1 << 5);
	MARK_CHANGED(11);

	regs[10] = tm->bs3 | (tm->be3 << 5);
	MARK_CHANGED(10);

	regs[13] = tm->bs2 | (tm->be2 << 5);
	MARK_CHANGED(13);

	regs[12] = tm->bs4 | (tm->be4 << 5);
	MARK_CHANGED(12);
}

static inline void setPicConfig(u16 fbSizeX, long xfbMode, u16 panPosX, u16 panSizeX,
    u8* wordPerLine, u8* std, u8* wpl, u8* xof)
{
	*wordPerLine = (fbSizeX + 15) / 16;
	*std         = (xfbMode == 0) ? *wordPerLine : (u8)(*wordPerLine * 2);
	*xof         = panPosX % 16;
	*wpl         = (*xof + panSizeX + 15) / 16;
	regs[36]     = *std | (*wpl << 8);
	MARK_CHANGED(36);
}

static inline void PrintDebugPalCaution(void)
{
	if (unk_8042CCD4 == 0) {
		unk_8042CCD4 = 1;
		OSReport("***************************************\n");
		OSReport(" ! ! ! C A U T I O N ! ! !             \n");
		OSReport("This TV format \"DEBUG_PAL\" is only for \n");
		OSReport("temporary solution until PAL DAC board \n");
		OSReport("is available. Please do NOT use this   \n");
		OSReport("mode in real games!!!                  \n");
		OSReport("***************************************\n");
	}
}

void VIConfigure(GXRenderModeObj* rm)
{
	VITiming* tm;
	u32 regDspCfg;
	u32 regClksel;
	BOOL enabled;
	u32 newNonInter;
	u32 tvInBootrom;
	u32 tvInGame;

	enabled = OSDisableInterrupts();

	newNonInter = rm->viTVmode & 3;
	if (HorVer.nonInter != newNonInter) {
		changeMode      = 1;
		HorVer.nonInter = newNonInter;
	}
	tvInGame    = (u32)rm->viTVmode >> 2;
	tvInBootrom = OS_TV_FORMAT;

	if (tvInGame == 4) {
		PrintDebugPalCaution();
	}

	switch (tvInBootrom) {
		case 0: // NTSC
		case 2: // MPAL
		case 6: // GCA
			if (tvInGame == 0 || tvInGame == 2 || tvInGame == 6) {
				break;
			}
			goto panic;
		case 1: // PAL
		case 5: // EURGB60
			if (tvInGame == 1 || tvInGame == 5) {
				break;
			}
			// fallthrough
		default:
		panic:
			OSPanic("vi.c", 0x774,
			    "VIConfigure(): Tried to change mode from (%d) to (%d), which is forbidden\n",
			    tvInBootrom, tvInGame);
			break;
	}

	if (tvInGame == 0 || tvInGame == 2) {
		HorVer.tv = tvInBootrom;
	} else {
		HorVer.tv = tvInGame;
	}

	HorVer.DispPosX  = rm->viXOrigin;
	HorVer.DispPosY  = (HorVer.nonInter == 1) ? (u16)(rm->viYOrigin * 2) : rm->viYOrigin;
	HorVer.DispSizeX = rm->viWidth;
	HorVer.FBSizeX   = rm->fbWidth;
	HorVer.FBSizeY   = rm->xfbHeight;
	HorVer.FBMode    = rm->xFBmode;
	HorVer.PanSizeX  = HorVer.FBSizeX;
	HorVer.PanSizeY  = HorVer.FBSizeY;
	HorVer.PanPosX   = 0;
	HorVer.PanPosY   = 0;
	HorVer.DispSizeY = (HorVer.nonInter == 2) ? HorVer.PanSizeY
	    : (HorVer.nonInter == 3)              ? HorVer.PanSizeY
	    : (HorVer.FBMode == 0)                ? (u16)(HorVer.PanSizeY * 2)
	                                          : HorVer.PanSizeY;
	HorVer.threeD    = (HorVer.nonInter == 3) ? TRUE : FALSE;

	tm            = getTiming((HorVer.tv << 2) + HorVer.nonInter);
	HorVer.timing = tm;

	AdjustPosition(tm->acv);

	if (encoderType == 0) {
		HorVer.tv = 3; // VI_DEBUG
	}
	setInterruptRegs(tm);

	regDspCfg = regs[1];
	if (HorVer.nonInter == 2 || HorVer.nonInter == 3) {
		regDspCfg = (regDspCfg & ~0x4) | 4;
	} else {
		regDspCfg = (regDspCfg & ~0x4) | ((HorVer.nonInter & 1) << 2);
	}
	regDspCfg = (regDspCfg & ~0x8) | (HorVer.threeD << 3);

	{
		u32 newRegDspCfg;
		if (HorVer.tv == 4 || HorVer.tv == 5 || HorVer.tv == 6) {
			newRegDspCfg = regDspCfg & ~0x300;
		} else {
			newRegDspCfg = (regDspCfg & ~0x300) | (HorVer.tv << 8);
		}
		regs[1] = (u16)newRegDspCfg;
	}
	MARK_CHANGED(1);

	regClksel = regs[54];
	{
		u32 newRegClksel;
		if (rm->viTVmode == VI_TVMODE(0, 2) || rm->viTVmode == VI_TVMODE(0, 3)
		    || rm->viTVmode == VI_TVMODE(6, 2)) {
			newRegClksel = (regClksel & ~1) | 1;
		} else {
			newRegClksel = regClksel & ~1;
		}
		regs[54] = (u16)newRegClksel;
	}
	MARK_CHANGED(54);

	setScalingRegs(HorVer.PanSizeX, HorVer.DispSizeX, HorVer.threeD);
	setHorizontalRegs(tm, HorVer.AdjustedDispPosX, HorVer.DispSizeX);
	setBBIntervalRegs(tm);
	setPicConfig(HorVer.FBSizeX, HorVer.FBMode, HorVer.PanPosX, HorVer.PanSizeX,
	    &HorVer.wordPerLine, &HorVer.std, &HorVer.wpl, &HorVer.xof);

	if (FBSet) {
		setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
	}

	setVerticalRegs(HorVer.AdjustedDispPosY, HorVer.AdjustedDispSizeY, tm->equ, tm->acv, tm->prbOdd,
	    tm->prbEven, tm->psbOdd, tm->psbEven, HorVer.black);

	OSRestoreInterrupts(enabled);
}

void VIFlush(void)
{
	BOOL enabled;
	u32 index;

	enabled = OSDisableInterrupts();
	shdwChangeMode |= changeMode;
	changeMode = 0;
	shdwChanged |= changed;
	while (changed) {
		index           = cntlzd(changed);
		shdwRegs[index] = regs[index];
		changed &= ~VI_BITMASK(index);
	}
	FlushFlag   = 1;
	NextBufAddr = HorVer.bufAddr;
	OSRestoreInterrupts(enabled);
}

void VISetNextFrameBuffer(void* fb)
{
	BOOL enabled;

	enabled        = OSDisableInterrupts();
	HorVer.bufAddr = (u32)fb;
	FBSet          = 1;
	setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
	OSRestoreInterrupts(enabled);
}

void VISetBlack(BOOL black)
{
	BOOL enabled;
	VITiming* tm;

	enabled      = OSDisableInterrupts();
	HorVer.black = black;
	tm           = HorVer.timing;
	setVerticalRegs(HorVer.AdjustedDispPosY, HorVer.DispSizeY, tm->equ, tm->acv, tm->prbOdd,
	    tm->prbEven, tm->psbOdd, tm->psbEven, HorVer.black);
	OSRestoreInterrupts(enabled);
}

static void getCurrentHalfLine(u32* hcount, u32* vcount)
{
	u32 vpos0;
	u32 vpos;
	u32 hpos;

	vpos = __VIRegs[22] & 0x7FF;
	do {
		vpos0 = vpos;
		hpos  = __VIRegs[23] & 0x7FF;
		vpos  = __VIRegs[22] & 0x7FF;
	} while (vpos0 != vpos);

	*hcount = hpos;
	*vcount = vpos;
}

// The half-line computation is its own inlined helper (dolsdk2004's
// getCurrentHalfLine(void)); the position loop above stays out-of-line at
// depth 3 inside VIGetNextField, which is what emits the bl there.
static inline u32 getHalfLine(void)
{
	u32 halfLine;
	u32 hcount, vcount;

	getCurrentHalfLine(&hcount, &vcount);
	halfLine = ((vcount - 1) << 1) + ((hcount - 1) / CurrTiming->hlw);
	return halfLine;
}

static u32 getCurrentFieldEvenOdd(void)
{
	if (getHalfLine() < CurrTiming->nhlines) {
		return 1;
	}
	return 0;
}

BOOL VIGetNextField(void)
{
	// Dead stack: one dead slot; the inlined getHalfLine temporaries sit
	// above it (dolsdk2004's u8 unused[4]).
	u32 pad[1];
	BOOL enabled;
	u32 nextField;

	enabled   = OSDisableInterrupts();
	nextField = getCurrentFieldEvenOdd() ^ 1;
	OSRestoreInterrupts(enabled);
	return (BOOL)(nextField ^ (HorVer.AdjustedDispPosY & 1));
}

u32 VIGetCurrentLine(void)
{
	u32 halfLine;
	u32 hcount, vcount;
	BOOL enabled;
	VITiming* tm;
	// Dead stack: the original frame is 8 bytes wider.
	u32 pad[2];

	tm      = CurrTiming;
	enabled = OSDisableInterrupts();
	getCurrentHalfLine(&hcount, &vcount);
	halfLine = 2 * (vcount - 1) + (hcount - 1) / CurrTiming->hlw;
	OSRestoreInterrupts(enabled);

	if (halfLine >= tm->nhlines) {
		halfLine -= tm->nhlines;
	}
	return halfLine >> 1;
}

u32 VIGetTvFormat(void)
{
	u32 format;
	BOOL enabled;

	enabled = OSDisableInterrupts();
	switch (CurrTvMode) {
		case 0:
		case 3:
		case 6:
			format = 0;
			break;
		case 1:
		case 4:
			format = 1;
			break;
		case 2:
		case 5:
			format = CurrTvMode;
			break;
		default:
			break;
	}
	OSRestoreInterrupts(enabled);
	return format;
}

u32 VIGetDTVStatus(void)
{
	u32 status;
	BOOL enabled;

	enabled = OSDisableInterrupts();
	status  = __VIRegs[55] & 3;
	OSRestoreInterrupts(enabled);
	return status & 1;
}

// Position conversion for the position-interrupt path (VIGetCurrentPosition
// family). SDK names are not established, so the address names stay.
void __VIDisplayPositionToXY(u32 hct, u32 vct, s16* x, s16* y)
{
	u32 halfLine;
	VITiming* tm;

	tm       = CurrTiming;
	halfLine = 2 * (vct - 1) + (hct - 1) / tm->hlw;

	if (HorVer.nonInter == 0) {
		if (halfLine < tm->nhlines) {
			if (halfLine < tm->prbOdd + 3 * tm->equ) {
				*y = -1;
			} else if (halfLine >= tm->nhlines - tm->psbOdd) {
				*y = -1;
			} else {
				*y = (s16)((halfLine - 3 * tm->equ - tm->prbOdd) & ~1);
			}
		} else {
			halfLine -= tm->nhlines;
			if (halfLine < tm->prbEven + 3 * tm->equ) {
				*y = -1;
			} else if (halfLine >= tm->nhlines - tm->psbEven) {
				*y = -1;
			} else {
				*y = (s16)(((halfLine - 3 * tm->equ - tm->prbEven) & ~1) + 1);
			}
		}
	} else if (HorVer.nonInter == 1) {
		if (halfLine >= tm->nhlines) {
			halfLine -= tm->nhlines;
		}
		if (halfLine < tm->prbOdd + 3 * tm->equ) {
			*y = -1;
		} else if (halfLine >= tm->nhlines - tm->psbOdd) {
			*y = -1;
		} else {
			*y = (s16)((halfLine - 3 * tm->equ - tm->prbOdd) & ~1);
		}
	} else if (HorVer.nonInter == 2) {
		if (halfLine < tm->nhlines) {
			if (halfLine < tm->prbOdd + 3 * tm->equ) {
				*y = -1;
			} else if (halfLine >= tm->nhlines - tm->psbOdd) {
				*y = -1;
			} else {
				*y = (s16)(halfLine - 3 * tm->equ - tm->prbOdd);
			}
		} else {
			halfLine -= tm->nhlines;
			if (halfLine < tm->prbEven + 3 * tm->equ) {
				*y = -1;
			} else if (halfLine >= tm->nhlines - tm->psbEven) {
				*y = -1;
			} else {
				*y = (s16)((halfLine - 3 * tm->equ - tm->prbEven) & ~1);
			}
		}
	}

	*x = (s16)(hct - 1);
}

void __VIGetCurrentPosition(s16* x, s16* y)
{
	u32 hct;
	u32 vct;

	getCurrentHalfLine(&hct, &vct);
	__VIDisplayPositionToXY(hct, vct, x, y);
}
