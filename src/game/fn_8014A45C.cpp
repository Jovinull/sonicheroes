// Selects the current interpolator of a morphing atomic (HYPOTHESIS:
// RpMorphAtomicSetCurrentInterpolator): binds the atomic's plugin 0x105 data to its geometry, picks
// entry index of the geometry's interpolator table and loads its start and end morph targets, a
// zero position and its scale (time and reciprocal) into the atomic's interpolator, flagging the
// atomic dirty after each. An atomic without geometry raises error 1 of plugin 0x105 and returns
// null; otherwise returns the atomic.
#include "game/geometry_plugin_105.h"
#include "game/rw_engine.h"

// Atomic plugin 0x105 data (layout from fn_80149E54 and fn_80149E74).
struct AtomicPlugin105Data8014A45C {
	GeometryPlugin105Entry* current; // 0x0
	f32 position;                    // 0x4
	void* geometry;                  // 0x8: geometry the data was bound to
};

// RpAtomic fields used here (HYPOTHESIS: RpAtomic with its RpInterpolator at 0x4C).
struct Atomic8014A45C {
	u8 pad0[0x4];
	RwFrame* frame; // 0x4: object parent
	u8 pad8[0x18 - 0x8];
	void* geometry; // 0x18
	u8 pad1C[0x4C - 0x1C];
	u32 interpFlags;      // 0x4C
	s16 startMorphTarget; // 0x50
	s16 endMorphTarget;   // 0x52
	f32 time;             // 0x54
	f32 recipTime;        // 0x58
	f32 position;         // 0x5C
};

#define RP_INTERPOLATOR_DIRTY          0x3 // dirty instance and sphere
#define RP_INTERPOLATOR_NO_FRAME_DIRTY 0x4
#define PLUGIN_ID_MORPH                0x105

extern "C" {
// Offset of the plugin 0x105 data inside an atomic.
extern s32 lbl_8042C868;
extern f32 lbl_8042F2B0; // 0.0f
extern f32 lbl_8042F2B4; // 1.0f
// HYPOTHESIS: RwFrameUpdateObjects.
RwFrame* fn_8019E880(RwFrame* frame);
}

// Flags the interpolator dirty and, unless frame dirtying is disabled, updates the atomic's frame.
static inline void MarkDirty8014A45C(Atomic8014A45C* atomic)
{
	atomic->interpFlags |= RP_INTERPOLATOR_DIRTY;
	if (!(atomic->interpFlags & RP_INTERPOLATOR_NO_FRAME_DIRTY) && atomic->frame != 0) {
		fn_8019E880(atomic->frame);
	}
}

// Sets the interpolation time scale and its reciprocal (HYPOTHESIS: RpInterpolatorSetScale).
static inline void SetScale8014A45C(Atomic8014A45C* atomic, f32 scale)
{
	atomic->time      = scale;
	atomic->recipTime = lbl_8042F2B4 / scale;
	MarkDirty8014A45C(atomic);
}

extern "C" {
Atomic8014A45C* fn_8014A45C(Atomic8014A45C* atomic, s32 index)
{
	void* geometry = atomic->geometry;
	if (geometry != 0) {
		AtomicPlugin105Data8014A45C* data
		    = (AtomicPlugin105Data8014A45C*)((u8*)atomic + lbl_8042C868);
		GeometryPlugin105Data* geometryData = GEOMETRY_PLUGIN_105_DATA(geometry);
		if (data->geometry != geometry) {
			data->geometry = geometry;
		}
		data->current = &geometryData->entries[index];

		atomic->startMorphTarget = data->current->a;
		MarkDirty8014A45C(atomic);
		atomic->endMorphTarget = data->current->b;
		MarkDirty8014A45C(atomic);
		atomic->position = lbl_8042F2B0;
		MarkDirty8014A45C(atomic);
		SetScale8014A45C(atomic, data->current->value);
		return atomic;
	} else {
		RwError error;
		error.pluginID  = PLUGIN_ID_MORPH;
		error.errorCode = fn_8019408C(1);
		fn_80193FE8(&error);
		return 0;
	}
}
}
