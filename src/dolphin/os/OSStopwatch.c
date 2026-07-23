#include "types.h"

// Stopwatches. The translation unit runs from OSInitStopwatch at 0x801D60C0
// to the end of OSResetStopwatch at 0x801D628C. Before it is OSRtc, after it
// is OSSync.
//
// The five functions carry their SDK names: the struct layout and the
// running-total arithmetic match the public OSStopwatch.c exactly.

#define NULL  0
#define FALSE 0
#define TRUE  1

typedef int BOOL;
typedef s64 OSTime;

typedef struct OSStopwatch {
	char* name;   // 0x00
	u32 hits;     // 0x04
	OSTime total; // 0x08
	OSTime min;   // 0x10
	OSTime max;   // 0x18
	OSTime last;  // 0x20
	BOOL running; // 0x28
} OSStopwatch;

extern OSTime OSGetTime(void);

void OSInitStopwatch(OSStopwatch* sw, char* name)
{
	sw->name  = name;
	sw->total = 0;
	sw->hits  = 0;
	sw->min   = 0xFFFFFFFF;
	sw->max   = 0;
}

void OSStartStopwatch(OSStopwatch* sw)
{
	sw->running = TRUE;
	sw->last    = OSGetTime();
}

void OSStopStopwatch(OSStopwatch* sw)
{
	OSTime interval;

	if (sw->running) {
		interval = OSGetTime() - sw->last;
		sw->total += interval;
		sw->running = FALSE;
		sw->hits++;

		if (interval > sw->max) {
			sw->max = interval;
		}
		if (interval < sw->min) {
			sw->min = interval;
		}
	}
}

OSTime OSCheckStopwatch(OSStopwatch* sw)
{
	OSTime running;

	running = sw->total;
	if (sw->running) {
		running += OSGetTime() - sw->last;
	}
	return running;
}

void OSResetStopwatch(OSStopwatch* sw)
{
	sw->total = 0;
	sw->hits  = 0;
	sw->min   = 0xFFFFFFFF;
	sw->max   = 0;
}
