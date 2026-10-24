#include "types.h"

// ObjRingScattering (the PS2 build's name): ObjRingScatteringNonSE
// (rel/scattered_ring_scatter.cpp) with the drop's sound.

#include "src/rel/scattered_ring.inc"

extern "C" TObject* lbl_8042C2A0;
extern "C" TObject* lbl_8042C110;

TObjScatteredRing* ObjRingScattering(u32 count, RwV3d* pos, sRealAngle3* ang, f32 speed, f32 spread)
{
	TObject* parent = lbl_8042C2A0;

	if (parent == NULL) {
		parent = lbl_8042C110;
	}
	return new TObjScatteredRing(parent, count, pos, ang, speed, spread, 1);
}
