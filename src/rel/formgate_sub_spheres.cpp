#include "types.h"

// Two helpers after TObjFormGateSub's constructor (the PS2 build's name), the
// same in the thirteen stage modules that share the engine core:
// formgateSubSetSpheres runs formgateSubSetAtomicSphere on every atomic of a
// clump. That one gives the atomic's morph target a bounding sphere of radius
// formgateSubMorphRadius (and has the engine recompute it), then centres the
// atomic's own sphere on its frame's position with radius
// formgateMaxWidth.

typedef struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
} RwV3d;

typedef struct RwSphere {
	RwV3d center;
	f32 radius;
} RwSphere;

typedef struct RpMorphTarget {
	void* parentGeom;
	RwSphere boundingSphere;
} RpMorphTarget;

typedef struct RpGeometry {
	u8 unk00[0x5C];
	RpMorphTarget* morphTarget;
} RpGeometry;

typedef struct RwFrame {
	u8 unk00[0x40];
	RwV3d pos;
} RwFrame;

typedef struct RpAtomic {
	u8 unk00[0x4];
	RwFrame* frame;
	u8 unk08[0x10];
	RpGeometry* geometry;
	RwSphere boundingSphere;
	u8 unk2C[0x20];
	s32 flags;
} RpAtomic;

extern "C" const f32 formgateSubMorphRadius;
extern "C" const f32 formgateMaxWidth[1];
extern "C" void fn_8015231C(RpMorphTarget* morphTarget, RwSphere* sphere);
extern "C" void fn_8014F854(RpAtomic* atomic);
extern "C" void fn_8019E8EC(RwFrame* frame);
extern "C" void fn_8014FFBC(void* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);

static inline void copySphere(RwSphere* dst, const RwSphere* src)
{
	*dst = *src;
}

extern "C" RpAtomic* formgateSubSetAtomicSphere(RpAtomic* atomic, void* data);

extern "C" void formgateSubSetSpheres(void* object, void* clump)
{
	fn_8014FFBC(clump, formgateSubSetAtomicSphere, NULL);
}

extern "C" RpAtomic* formgateSubSetAtomicSphere(RpAtomic* atomic, void* data)
{
	RpMorphTarget* mt = atomic->geometry->morphTarget;
	RwSphere* sphere  = &mt->boundingSphere;
	RwFrame* frame;

	sphere->radius = formgateSubMorphRadius;
	copySphere(sphere, sphere);
	fn_8015231C(mt, sphere);
	frame = atomic->frame;
	if (atomic->flags & 2) {
		fn_8014F854(atomic);
	}
	atomic->boundingSphere.center.z = frame->pos.z;
	atomic->boundingSphere.center.y = frame->pos.y;
	atomic->boundingSphere.center.x = frame->pos.x;
	fn_8019E8EC(frame);
	atomic->boundingSphere.radius = formgateMaxWidth[0];
	return atomic;
}
