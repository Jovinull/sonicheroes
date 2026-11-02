#include "types.h"

// Clears one of the capture enemy's bubbles (captureBubbleInit here), the
// same in the seven stage modules that carry the capture: at the origin,
// sinking, growing by the module's 0.2 step, with no top yet.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct CaptureBubble {
	RwV3d pos;   // 0x00
	RwV3d speed; // 0x0C
	f32 scale;   // 0x18
	f32 grow;    // 0x1C
	f32 top;     // 0x20
} CaptureBubble;

extern "C" const f32 captureZero;
extern "C" const f32 captureBubbleSink;
extern "C" const f32 captureRiseSpeed;

extern "C" void captureBubbleInit(CaptureBubble* bubble)
{
	bubble->pos.x = bubble->pos.y = bubble->pos.z = captureZero;
	bubble->speed.x = bubble->speed.z = captureZero;
	bubble->speed.y                   = captureBubbleSink;
	bubble->scale                     = captureZero;
	bubble->grow                      = captureRiseSpeed;
	bubble->top                       = captureZero;
}
