// Updates the bounding sphere of a morphing atomic (HYPOTHESIS: the RpAtomic sphere sync for
// morph targets): between two distinct valid morph targets the sphere is interpolated by
// position * recipTime; otherwise the sphere of the start target (or of target 0 when the start is
// out of range) is copied. Clears the interpolator's dirty-sphere flag and marks the world bounds
// dirty.
// NonMatching: C++ copies the all-float RwSphere with lwz/stw for the centre and lfs/stfs for the
// radius, while retail copies all four words as integers. The same source compiled with -lang=c is
// EXACT (92/92 words), evidence that this RenderWare unit was C; moving it to a reviewed C boundary
// is left for review.
#include "game/object.h"

struct MorphTarget8014F854 {
	void* parentGeom;        // 0x0
	RwSphere boundingSphere; // 0x4
	void* verts;             // 0x14
	void* normals;           // 0x18
};

struct Geometry8014F854 {
	u8 pad0[0x18];
	s32 numMorphTargets; // 0x18
	u8 pad1C[0x5C - 0x1C];
	MorphTarget8014F854* morphTarget; // 0x5C
};

struct Atomic8014F854 {
	RwObject object; // 0x0
	u8 pad8[0x18 - 0x8];
	Geometry8014F854* geometry; // 0x18
	RwSphere boundingSphere;    // 0x1C
	u8 pad2C[0x4C - 0x2C];
	u32 interpFlags;      // 0x4C
	s16 startMorphTarget; // 0x50
	s16 endMorphTarget;   // 0x52
	f32 time;             // 0x54
	f32 recipTime;        // 0x58
	f32 position;         // 0x5C
};

#define RP_INTERPOLATOR_DIRTY_SPHERE        0x2
#define RP_ATOMIC_PRIVATE_WORLD_BOUND_DIRTY 0x1

extern "C" {
void fn_8014F854(Atomic8014F854* atomic)
{
	Geometry8014F854* geometry = atomic->geometry;

	if (geometry == 0) {
		return;
	}
	if (atomic->startMorphTarget == atomic->endMorphTarget
	    || atomic->startMorphTarget >= geometry->numMorphTargets
	    || atomic->endMorphTarget >= geometry->numMorphTargets) {
		if (atomic->startMorphTarget >= geometry->numMorphTargets
		    || atomic->endMorphTarget >= geometry->numMorphTargets) {
			atomic->boundingSphere = geometry->morphTarget[0].boundingSphere;
		} else {
			atomic->boundingSphere = geometry->morphTarget[atomic->startMorphTarget].boundingSphere;
		}
	} else {
		MorphTarget8014F854* a = &geometry->morphTarget[atomic->startMorphTarget];
		MorphTarget8014F854* b = &geometry->morphTarget[atomic->endMorphTarget];
		f32 t                  = atomic->recipTime * atomic->position;

		atomic->boundingSphere.radius
		    = t * (b->boundingSphere.radius - a->boundingSphere.radius) + a->boundingSphere.radius;
		atomic->boundingSphere.center.x = b->boundingSphere.center.x - a->boundingSphere.center.x;
		atomic->boundingSphere.center.y = b->boundingSphere.center.y - a->boundingSphere.center.y;
		atomic->boundingSphere.center.z = b->boundingSphere.center.z - a->boundingSphere.center.z;
		atomic->boundingSphere.center.x = atomic->boundingSphere.center.x * t;
		atomic->boundingSphere.center.y = atomic->boundingSphere.center.y * t;
		atomic->boundingSphere.center.z = atomic->boundingSphere.center.z * t;
		atomic->boundingSphere.center.x
		    = atomic->boundingSphere.center.x + a->boundingSphere.center.x;
		atomic->boundingSphere.center.y
		    = atomic->boundingSphere.center.y + a->boundingSphere.center.y;
		atomic->boundingSphere.center.z
		    = atomic->boundingSphere.center.z + a->boundingSphere.center.z;
	}
	atomic->interpFlags &= ~RP_INTERPOLATOR_DIRTY_SPHERE;
	atomic->object.privateFlags |= RP_ATOMIC_PRIVATE_WORLD_BOUND_DIRTY;
}
}
