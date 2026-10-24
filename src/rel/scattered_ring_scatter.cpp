#include "types.h"

// ObjRingScatteringNonSE (the PS2 build's name): the rings a hurt player
// drops, made silently under the stage's object root (the game's when the
// stage has none), TObjScatteredRing's constructor inlined; the rings made, if
// they could be.

#include "src/rel/scattered_ring.inc"

extern "C" TObject* lbl_8042C2A0;
extern "C" TObject* lbl_8042C110;

TObjScatteredRing* ObjRingScatteringNonSE(
    u32 count, RwV3d* pos, sRealAngle3* ang, f32 speed, f32 spread)
{
	TObject* parent = lbl_8042C2A0;

	if (parent == NULL) {
		parent = lbl_8042C110;
	}

	return new TObjScatteredRing(parent, count, pos, ang, speed, spread, 0);
}
