#include "types.h"

// A one-function unit of stage11D (its .rodata is only the {0, 1.5, 0} vector
// each of these units opens with): draws a path as debug line segments, its
// points carried through a transform. The flyer (rel/e_flyer_stage11.cpp)
// calls it to show its flight path.

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct RwMatrix;

/* PATHTAG: the point count is the s16 at 0x2. */
struct PathTag {
	s16 unk0;
	s16 count;
};

/* The vector the stage 11 units carry unreferenced at the head of their
 * .rodata (see e_capture_collision_stage11.cpp). */
#pragma force_active on
static const RwV3d lbl_8_rodata_1A00 = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset

extern "C" {
void GetPointDataOnPath__FP7PATHTAGiP5RwV3d(PathTag*, s32, RwV3d*);
void fn_8019941C(RwV3d*, RwV3d*, s32, RwMatrix*); /* RwV3dTransformPoints */
void fn_8005FC74(RwV3d*, RwV3d*);                 /* debug line */

void fn_8_A9E94(PathTag* path, RwMatrix* matrix)
{
	RwV3d a;
	RwV3d b;
	s32 i;

	if (path != NULL) {
		for (i = 0; i < path->count - 1; i++) {
			GetPointDataOnPath__FP7PATHTAGiP5RwV3d(path, i, &a);
			GetPointDataOnPath__FP7PATHTAGiP5RwV3d(path, i + 1, &b);
			fn_8019941C(&a, &a, 1, matrix);
			fn_8019941C(&b, &b, 1, matrix);
			fn_8005FC74(&a, &b);
		}
	}
}
}
