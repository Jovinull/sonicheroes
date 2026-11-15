// Tests whether a moving sphere hits any polygon on its way to a target (HYPOTHESIS; names
// inferred): sweeps the sphere of radius lbl_8042BBC8 from the position along the vector to the
// target through the collision octree lbl_8042C150, filtering polygons with fn_801354A4. Frees the
// hit list and returns 1 when anything was hit, 0 otherwise.
#include "game/octree.h"

extern OCTREE* lbl_8042C150;

extern "C" {
extern f32 lbl_8042BBC8;
s32 fn_801354A4(POLYDATA* polygon);

s32 fn_80135418(RwV3d* position, RwV3d* target)
{
	RwV3d move;
	ENUM_CL_MOVING moving;
	ColliPolyLinearList* hits;

	move.x = target->x - position->x;
	move.y = target->y - position->y;
	move.z = target->z - position->z;
	hits   = lbl_8042C150->DetectMovingSphereCollisionWithPolygons(
	    position, lbl_8042BBC8, &move, &moving, fn_801354A4);
	if (hits != 0) {
		delete hits;
		return 1;
	}
	return 0;
}
}
