// Creates an atomic (HYPOTHESIS: RpAtomicCreate): takes one from the atomic free list of the
// engine (module lbl_8042C8D8), initialises it as an atomic object with the sync callback
// fn_8014F168, render and collision flags (0x5) and a dirty private flag, clears its geometry
// (fn_80152220 with null), bounding spheres and instance data, installs the default render
// callback fn_8014F1B0, sets up its interpolator (.sdata2 lbl_8042F30C and lbl_8042F308) and tie
// list, then runs the atomic plugin constructors (fn_80198D5C on lbl_8028D230). Returns the atomic,
// or null when the free list is exhausted. Field names are inferred.
#include "game/rw_engine.h"

struct Atomic80150140;
typedef Atomic80150140* (*AtomicCallBack80150140)(Atomic80150140* atomic);

struct Sphere80150140 {
	f32 x;      // 0x0
	f32 y;      // 0x4
	f32 z;      // 0x8
	f32 radius; // 0xC
};

struct Atomic80150140 {
	u8 type;         // 0x0
	u8 subType;      // 0x1
	u8 flags;        // 0x2
	u8 privateFlags; // 0x3
	void* parent;    // 0x4
	u8 pad8[0x8];
	AtomicCallBack80150140 sync;        // 0x10
	void* repEntry;                     // 0x14
	void* geometry;                     // 0x18
	Sphere80150140 boundingSphere;      // 0x1C
	Sphere80150140 worldBoundingSphere; // 0x2C
	void* word3C;                       // 0x3C
	void* word40;                       // 0x40
	void* word44;                       // 0x44
	AtomicCallBack80150140 render;      // 0x48
	s32 interpFlags;                    // 0x4C
	u16 startMorphTarget;               // 0x50
	u16 endMorphTarget;                 // 0x52
	f32 time;                           // 0x54
	f32 recipTime;                      // 0x58
	f32 position;                       // 0x5C
	u8 pad60[0x4];
	RwLinkList ties; // 0x64
	void* word6C;    // 0x6C
};

extern "C" {
extern RwModuleInfo lbl_8042C8D8;
extern RwPluginRegistry lbl_8028D230;
extern f32 lbl_8042F308;
extern f32 lbl_8042F30C;

Atomic80150140* fn_8014F168(Atomic80150140* atomic);
Atomic80150140* fn_8014F1B0(Atomic80150140* atomic);
Atomic80150140* fn_80152220(Atomic80150140* atomic, void* geometry);

Atomic80150140* fn_80150140(void)
{
	Atomic80150140* atomic = (Atomic80150140*)lbl_8042C9A4->freeListAlloc(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C8D8.globalsOffset));

	if (!atomic) {
		return 0;
	}
	atomic->type         = 1;
	atomic->subType      = 0;
	atomic->flags        = 0;
	atomic->privateFlags = 0;
	atomic->parent       = 0;
	atomic->sync         = fn_8014F168;
	atomic->repEntry     = 0;
	atomic->flags        = 0x5;
	atomic->privateFlags = 1;
	fn_80152220(atomic, 0);
	atomic->geometry                   = 0;
	atomic->boundingSphere.radius      = lbl_8042F308;
	atomic->boundingSphere.x           = lbl_8042F308;
	atomic->boundingSphere.y           = lbl_8042F308;
	atomic->boundingSphere.z           = lbl_8042F308;
	atomic->worldBoundingSphere.radius = lbl_8042F308;
	atomic->worldBoundingSphere.x      = lbl_8042F308;
	atomic->worldBoundingSphere.y      = lbl_8042F308;
	atomic->worldBoundingSphere.z      = lbl_8042F308;
	atomic->render                     = fn_8014F1B0;
	if (!atomic->render) {
		atomic->render = fn_8014F1B0;
	}
	atomic->startMorphTarget = 0;
	atomic->endMorphTarget   = 0;
	atomic->time             = lbl_8042F30C;
	atomic->recipTime        = lbl_8042F30C;
	atomic->position         = lbl_8042F308;
	atomic->interpFlags      = 3;
	atomic->word44           = 0;
	atomic->word40           = 0;
	atomic->word3C           = 0;
	atomic->word6C           = 0;
	atomic->ties.link.next   = &atomic->ties.link;
	atomic->ties.link.prev   = &atomic->ties.link;
	fn_80198D5C(&lbl_8028D230, atomic);
	return atomic;
}
}
