#include "types.h"

// The capture enemy's shadows (captureShadow here), the same in the seven
// stage modules that carry the capture: the shadow fades with the height
// above its spot (between the module's lowest and full strength), then the
// body's shadow and the two smaller ones are cast along the ground normal.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct CaptureShadow {
	RwV3d pos; // 0x00
} CaptureShadow;

typedef struct Capture {
	u8 unk000[0x144];
	f32 y; // 0x144
	u8 unk148[0x1B0];
	CaptureShadow shadows[3]; // 0x2F8
	RwV3d ground;             // 0x31C
} Capture;

extern "C" const RwV3d captureShadowSize;
extern "C" const f32 captureOne;
extern "C" const f32 captureShadowFade;
extern "C" const f32 captureShadowMin;
extern "C" const f32 captureShadowMax;
extern "C" const f32 captureShadowWidth;
extern "C" const f32 captureShadowDepth;

extern "C" void fn_800B7864(s32 arg);
extern "C" void fn_800B7514(CaptureShadow* shadow, RwV3d* ground, RwV3d* size, f32 alpha);
extern "C" void fn_800B7820(void);

static inline const f32& captureClamp(const f32& value, const f32& low, const f32& high)
{
	if (value < low) {
		return low;
	}
	if (value > high) {
		return high;
	}
	return value;
}

extern "C" void captureShadow(Capture* object)
{
	fn_800B7864(0);
	{
		RwV3d size = captureShadowSize;
		f32 alpha  = captureOne - captureShadowFade * (object->y - object->shadows[0].pos.y);

		alpha = captureClamp(alpha, captureShadowMin, captureShadowMax);
		fn_800B7514(&object->shadows[0], &object->ground, &size, alpha);
		size.x = captureShadowWidth;
		size.z = captureShadowDepth;
		fn_800B7514(&object->shadows[1], &object->ground, &size, alpha);
		fn_800B7514(&object->shadows[2], &object->ground, &size, alpha);
	}
	fn_800B7820();
}
