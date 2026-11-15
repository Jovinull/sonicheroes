// Clones an atomic (HYPOTHESIS: RpAtomicClone): creates a new atomic (fn_80150140), copies the
// object header with no parent and the atomic flags, detaches it from any frame (fn_80152220),
// shares the source geometry as RpAtomicSetGeometry does (reference added, previous geometry
// destroyed, bounding sphere from morph target 0, frame update), then copies the bounding sphere,
// render callback, pipeline and interpolator and runs the atomic plugin copy callbacks. Returns the
// clone, or null when it cannot be created.
// NonMatching: C++ copies the RwSphere radius and the interpolator fields with float/halfword
// moves; retail copies both structs as integer words. The same source compiled with -lang=c is
// EXACT (94/94 words), more evidence that the RenderWare core units were C (see fn_8014F854).
#include "game/object.h"
#include "game/rw_engine.h"

struct MorphTarget80150410 {
	void* parentGeom;        // 0x0
	RwSphere boundingSphere; // 0x4
	void* verts;             // 0x14
	void* normals;           // 0x18
};

struct Geometry80150410 {
	u8 pad0[0x5C];
	MorphTarget80150410* morphTarget; // 0x5C
};

struct Interpolator80150410 {
	u32 flags;            // 0x0
	s16 startMorphTarget; // 0x4
	s16 endMorphTarget;   // 0x6
	f32 time;             // 0x8
	f32 recipTime;        // 0xC
	f32 position;         // 0x10
};

struct Atomic80150410 {
	RwObject object; // 0x0
	u8 pad8[0x18 - 0x8];
	Geometry80150410* geometry; // 0x18
	RwSphere boundingSphere;    // 0x1C
	u8 pad2C[0x48 - 0x2C];
	void* renderCallBack;              // 0x48
	Interpolator80150410 interpolator; // 0x4C
	u8 pad60[0x6C - 0x60];
	void* pipeline; // 0x6C
};

extern "C" {
// Atomic plugin registry (HYPOTHESIS: atomicTKList).
extern RwPluginRegistry lbl_8028D230;
// HYPOTHESIS: RpAtomicCreate, _rwObjectHasFrameSetFrame, RpGeometryAddRef, RpGeometryDestroy,
// the atomic frame-update test and RwFrameUpdateObjects.
Atomic80150410* fn_80150140(void);
void fn_80152220(Atomic80150410* atomic, RwFrame* frame);
void fn_80152EDC(Geometry80150410* geometry);
void fn_80152EEC(Geometry80150410* geometry);
void* fn_8015BAFC(Atomic80150410* atomic);
RwFrame* fn_8019E880(RwFrame* frame);

Atomic80150410* fn_80150410(Atomic80150410* atomic)
{
	Atomic80150410* clone = fn_80150140();
	Geometry80150410* geometry;

	if (clone == 0) {
		return 0;
	}
	clone->object.type         = atomic->object.type;
	clone->object.subType      = atomic->object.subType;
	clone->object.flags        = atomic->object.flags;
	clone->object.privateFlags = atomic->object.privateFlags;
	clone->object.parent       = 0;
	clone->object.flags        = atomic->object.flags;
	fn_80152220(clone, 0);

	geometry = atomic->geometry;
	if (geometry != clone->geometry) {
		if (geometry != 0) {
			fn_80152EDC(geometry);
		}
		if (clone->geometry != 0) {
			fn_80152EEC(clone->geometry);
		}
		clone->geometry = geometry;
		if (geometry != 0) {
			clone->boundingSphere = geometry->morphTarget[0].boundingSphere;
		}
		{
			RwFrame* frame = (RwFrame*)clone->object.parent;
			if (frame != 0 && fn_8015BAFC(clone) != 0) {
				fn_8019E880(frame);
			}
		}
	}
	clone->boundingSphere = atomic->boundingSphere;
	clone->renderCallBack = atomic->renderCallBack;
	clone->pipeline       = atomic->pipeline;
	clone->interpolator   = atomic->interpolator;
	fn_80198E70(&lbl_8028D230, clone, atomic);
	return clone;
}
}
