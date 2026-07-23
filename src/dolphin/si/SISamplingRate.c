#include "types.h"

// The sampling-rate half of the serial interface driver, 0x801FA310 to
// 0x801FA418. Split from SIBios.c: the XY tables anchor this unit's .data at
// offset zero and SISetXY stays an out-of-line call, which only happens when
// SISetSamplingRate lives in its own translation unit, matching the SDK's
// SISamplingRate.c.
//
typedef int BOOL;

#ifdef __MWERKS__
volatile u16 __VIRegs[] : 0xCC002000;
#else
extern volatile u16 __VIRegs[];
#endif

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u32 VIGetTvFormat(void);
extern void OSReport(const char* msg, ...);
extern u32 SISetXY(u32 x, u32 y);

// Polling windows per sampling rate, lines-per-poll x and polls-per-frame y,
// one table per TV standard, and the complaint for a standard the driver
// does not know.
typedef struct SIXY {
	u16 x; // 0x00
	u8 y;  // 0x02
} SIXY;

static SIXY XYNTSC[12] = {
	{ 0x00F6, 0x02 },
	{ 0x000F, 0x12 },
	{ 0x001E, 0x09 },
	{ 0x002C, 0x06 },
	{ 0x0034, 0x05 },
	{ 0x0041, 0x04 },
	{ 0x0057, 0x03 },
	{ 0x0057, 0x03 },
	{ 0x0057, 0x03 },
	{ 0x0083, 0x02 },
	{ 0x0083, 0x02 },
	{ 0x0083, 0x02 },
};

static SIXY XYPAL[12] = {
	{ 0x0128, 0x02 },
	{ 0x000F, 0x15 },
	{ 0x001D, 0x0B },
	{ 0x002D, 0x07 },
	{ 0x0034, 0x06 },
	{ 0x003F, 0x05 },
	{ 0x004E, 0x04 },
	{ 0x0068, 0x03 },
	{ 0x0068, 0x03 },
	{ 0x0068, 0x03 },
	{ 0x0068, 0x03 },
	{ 0x009C, 0x02 },
};

static u32 SamplingRate;

void SISetSamplingRate(u32 msec)
{
	BOOL enabled;
	u32 tv;
	SIXY* xy;
	u32 lines;

	if (msec > 11) {
		msec = 11;
	}

	enabled = OSDisableInterrupts();

	SamplingRate = msec;

	tv = VIGetTvFormat();
	switch (tv) {
		case 0:
		case 2:
		case 5:
			xy = XYNTSC;
			break;
		case 1:
			xy = XYPAL;
			break;
		default:
			OSReport("SISetSamplingRate: unknown TV format. Use default.");
			msec = 0;
			xy   = XYNTSC;
			break;
	}

	lines = (__VIRegs[54] & 1) ? 2 : 1;

	SISetXY(lines * xy[msec].x, xy[msec].y);

	OSRestoreInterrupts(enabled);
}

// SIRefreshSamplingRate in the SDK.
void SIRefreshSamplingRate(void)
{
	SISetSamplingRate(SamplingRate);
}
