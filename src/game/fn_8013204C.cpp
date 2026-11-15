// Pulls a point towards a target offset (HYPOTHESIS: one relaxation step of a follow constraint).
// Mode 0 moves the point so that its offset from the anchor approaches the fixed offset; mode 1 so
// that its offset from the second anchor approaches the offset between the reference points. The
// remaining error is scaled by the stiffness. Other modes do nothing. Names are inferred from this
// function only.
// NonMatching (built with the neighbouring units' noschedule preset): mode 1 matches; in mode 0
// retail keeps the anchor x in f4, the error in f5-f7 and the offset in f1-f3, while this source
// gets a different float register assignment (19 words). Function-scope vector locals do not
// change it.
#include "game/object.h"

struct Constraint8013204C {
	s32 mode;         // 0x0: 0 fixed offset, 1 relative offset
	RwV3d* anchor;    // 0x4
	RwV3d* point;     // 0x8: the point that moves
	RwV3d* reference; // 0xC: mode 1, offset = anchor - reference
	RwV3d* anchor2;   // 0x10: mode 1 anchor of the point
	RwV3d* offset;    // 0x14: mode 0 fixed offset
	f32 stiffness;    // 0x18: fraction of the error kept
};

extern "C" {
void fn_8013204C(Constraint8013204C* c)
{
	switch (c->mode) {
		case 1: {
			RwV3d rest;
			RwV3d error;

			rest.x  = c->anchor->x - c->reference->x;
			rest.y  = c->anchor->y - c->reference->y;
			rest.z  = c->anchor->z - c->reference->z;
			error.x = (c->point->x - c->anchor2->x) - rest.x;
			error.y = (c->point->y - c->anchor2->y) - rest.y;
			error.z = (c->point->z - c->anchor2->z) - rest.z;
			error.x *= c->stiffness;
			error.y *= c->stiffness;
			error.z *= c->stiffness;
			error.x += rest.x;
			error.y += rest.y;
			error.z += rest.z;
			c->point->x = error.x + c->anchor2->x;
			c->point->y = error.y + c->anchor2->y;
			c->point->z = error.z + c->anchor2->z;
			break;
		}
		case 0: {
			RwV3d error;

			error.x = c->point->x - c->anchor->x;
			error.y = c->point->y - c->anchor->y;
			error.z = c->point->z - c->anchor->z;
			error.x -= c->offset->x;
			error.y -= c->offset->y;
			error.z -= c->offset->z;
			error.x *= c->stiffness;
			error.y *= c->stiffness;
			error.z *= c->stiffness;
			error.x += c->offset->x;
			error.y += c->offset->y;
			error.z += c->offset->z;
			c->point->x = error.x + c->anchor->x;
			c->point->y = error.y + c->anchor->y;
			c->point->z = error.z + c->anchor->z;
			break;
		}
	}
}
}
