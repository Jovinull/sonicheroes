#include "types.h"

// Whether one of the capture enemy's bubbles has reached its top
// (captureBubbleDone here), the same in the seven stage modules that carry
// the capture.

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

extern "C" s32 captureBubbleDone(CaptureBubble* bubble)
{
	return (bubble->pos.y < bubble->top) == 0;
}
