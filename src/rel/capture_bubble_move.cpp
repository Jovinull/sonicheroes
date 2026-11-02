#include "types.h"

// One step of a capture enemy bubble (captureBubbleMove here), the same in the
// seven stage modules that carry the capture: it moves by its speed and grows
// by its step, up to the module's largest size.

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

extern "C" const f32 captureBubbleMax;

extern "C" void captureBubbleMove(CaptureBubble* bubble)
{
	bubble->pos.x += bubble->speed.x;
	bubble->pos.y += bubble->speed.y;
	bubble->pos.z += bubble->speed.z;
	bubble->scale += bubble->grow;
	if (bubble->scale > captureBubbleMax) {
		// (two literals in the original; the volatile read keeps the reload)
		bubble->scale = *(volatile const f32*)&captureBubbleMax;
	}
}
