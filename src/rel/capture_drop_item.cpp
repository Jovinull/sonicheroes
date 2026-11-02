#include "types.h"

// The capture enemy's item drop (captureDropItem here), the same in the seven
// stage modules that carry the capture: an item box at the given point.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

namespace nItemBox
{
void CreateItemBox(RwV3d* pos);
}

extern "C" void captureDropItem(void* object, RwV3d* pos)
{
	nItemBox::CreateItemBox(pos);
}
