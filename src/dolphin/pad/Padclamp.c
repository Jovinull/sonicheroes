#include "types.h"
// Functions below marked static inline without being helpers: they are real
// SDK API this game never calls, and the original linker stripped them from
// the DOL. The inline marking keeps their bodies out of the object so the
// section sizes match the original exactly; the code stays for SDK fidelity.

// The pad library's clamping helpers, the SDK's Padclamp.c. WORK IN PROGRESS.
//
// The translation unit runs from ClampStick at 0x801DDB58 to PADClamp's end at
// 0x801DDD9C, where Pad.c begins with UpdateOrigin. The split between the two
// files is not a guess: the SDK ships pad.a with Padclamp.o linked before
// Pad.o, which is exactly the order here, and this unit's ClampRegion carries
// two radius fields that only PADClampCircle reads - a function that no code
// in the game calls, which is why the linker dropped it along with the
// helpers ClampCircle and ClampTrigger (the latter survives only inlined into
// PADClamp). Functions are in the order the original emits them.

// Channel status, ten data bytes plus the error code. Kept in sync with the
// copy in Pad.c, as the SDK's pad.h would have done.
typedef struct PADStatus {
	u16 button;      // 0x0
	s8 stickX;       // 0x2
	s8 stickY;       // 0x3
	s8 substickX;    // 0x4
	s8 substickY;    // 0x5
	u8 triggerLeft;  // 0x6
	u8 triggerRight; // 0x7
	u8 analogA;      // 0x8
	u8 analogB;      // 0x9
	s8 err;          // 0xA
	u8 pad;          // 0xB
} PADStatus;         // 0xC

#define PAD_MAX_CONTROLLERS 4
#define PAD_ERR_NONE        0

extern f32 sqrtf(f32 x);

typedef struct PADClampRegion {
	u8 minTrigger;  // 0x0
	u8 maxTrigger;  // 0x1
	s8 minStick;    // 0x2
	s8 maxStick;    // 0x3
	s8 xyStick;     // 0x4
	s8 minSubstick; // 0x5
	s8 maxSubstick; // 0x6
	s8 xySubstick;  // 0x7
	s8 radStick;    // 0x8
	s8 radSubstick; // 0x9
} PADClampRegion;

// The clamp thresholds, ten bytes in .rodata at 0x8023D450:
// 1e b4 0f 48 28 0f 3b 1f 38 2c.
static const PADClampRegion ClampRegion = {
	// Triggers
	30,
	180,

	// Left stick
	15,
	72,
	40,

	// Right stick
	15,
	59,
	31,

	// Stick radii
	56,
	44,
};

static void ClampStick(s8* px, s8* py, s8 max, s8 xy, s8 min)
{
	int x = *px;
	int y = *py;
	int signX;
	int signY;
	int d;

	if (0 <= x) {
		signX = 1;
	} else {
		signX = -1;
		x     = -x;
	}

	if (0 <= y) {
		signY = 1;
	} else {
		signY = -1;
		y     = -y;
	}

	if (x <= min) {
		x = 0;
	} else {
		x -= min;
	}
	if (y <= min) {
		y = 0;
	} else {
		y -= min;
	}

	if (x == 0 && y == 0) {
		*px = *py = 0;
		return;
	}

	if (xy * y <= xy * x) {
		d = xy * x + (max - xy) * y;
		if (xy * max < d) {
			x = (s8)(xy * max * x / d);
			y = (s8)(xy * max * y / d);
		}
	} else {
		d = xy * y + (max - xy) * x;
		if (xy * max < d) {
			x = (s8)(xy * max * x / d);
			y = (s8)(xy * max * y / d);
		}
	}

	*px = (s8)(signX * x);
	*py = (s8)(signY * y);
}

// Dropped by the original linker along with PADClampCircle, its only caller.
static inline void ClampCircle(s8* px, s8* py, s8 radius, s8 min)
{
	int x = *px;
	int y = *py;
	int squared;
	int length;

	if (-min < x && x < min) {
		x = 0;
	} else if (0 < x) {
		x -= min;
	} else {
		x += min;
	}

	if (-min < y && y < min) {
		y = 0;
	} else if (0 < y) {
		y -= min;
	} else {
		y += min;
	}

	squared = x * x + y * y;
	if (radius * radius < squared) {
		length = sqrtf(squared);
		x      = (x * radius) / length;
		y      = (y * radius) / length;
	}

	*px = x;
	*py = y;
}

static inline void ClampTrigger(u8* trigger, u8 min, u8 max)
{
	if (*trigger <= min) {
		*trigger = 0;
	} else {
		if (max < *trigger) {
			*trigger = max;
		}
		*trigger -= min;
	}
}

void PADClamp(PADStatus* status)
{
	s32 i;

	for (i = 0; i < PAD_MAX_CONTROLLERS; i++, status++) {
		if (status->err != PAD_ERR_NONE) {
			continue;
		}

		ClampStick(&status->stickX, &status->stickY, ClampRegion.maxStick, ClampRegion.xyStick,
		    ClampRegion.minStick);
		ClampStick(&status->substickX, &status->substickY, ClampRegion.maxSubstick,
		    ClampRegion.xySubstick, ClampRegion.minSubstick);
		ClampTrigger(&status->triggerLeft, ClampRegion.minTrigger, ClampRegion.maxTrigger);
		ClampTrigger(&status->triggerRight, ClampRegion.minTrigger, ClampRegion.maxTrigger);
	}
}

// Not in the binary: nothing references it, so the original linker dropped it.
// The radStick/radSubstick fields of ClampRegion exist only for this pair.
static inline void PADClampCircle(PADStatus* status)
{
	s32 i;

	for (i = 0; i < PAD_MAX_CONTROLLERS; i++, status++) {
		if (status->err != PAD_ERR_NONE) {
			continue;
		}

		ClampCircle(&status->stickX, &status->stickY, ClampRegion.radStick, ClampRegion.minStick);
		ClampCircle(&status->substickX, &status->substickY, ClampRegion.radSubstick,
		    ClampRegion.minSubstick);
		ClampTrigger(&status->triggerLeft, ClampRegion.minTrigger, ClampRegion.maxTrigger);
		ClampTrigger(&status->triggerRight, ClampRegion.minTrigger, ClampRegion.maxTrigger);
	}
}
