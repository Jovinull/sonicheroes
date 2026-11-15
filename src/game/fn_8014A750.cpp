// Advances the morph time of a morphing atomic (HYPOTHESIS: RpMorphAtomicAddTime): binds the
// atomic's plugin 0x105 data to its geometry as fn_8014A5CC does, adds delta to the position and,
// while it runs past the current interpolator's time, lets the geometry's interpolator callback
// (fn at geometry plugin data +0x4) move to the next one and return the new position; then loads
// the interpolator's start and end targets, the position and the scale into the atomic. An atomic
// without geometry raises error 1 of plugin 0x105 and returns null; otherwise returns the atomic.
#include "game/geometry_plugin_105.h"
#include "game/rw_engine.h"

// Atomic plugin 0x105 data (layout from fn_80149E54 and fn_80149E74).
struct AtomicPlugin105Data8014A750 {
	GeometryPlugin105Entry* current; // 0x0
	f32 position;                    // 0x4
	void* geometry;                  // 0x8: geometry the data was bound to
};

// RpAtomic fields used here (HYPOTHESIS: RpAtomic with its RpInterpolator at 0x4C).
struct Atomic8014A750 {
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

// Interpolator callback: moves to the next interpolator and returns the new position.
typedef f32 (*MorphCallBack8014A750)(Atomic8014A750* atomic, f32 position);

#define RP_INTERPOLATOR_DIRTY          0x3 // dirty instance and sphere
#define RP_INTERPOLATOR_NO_FRAME_DIRTY 0x4
#define PLUGIN_ID_MORPH                0x105

extern "C" {
// Offset of the plugin 0x105 data inside an atomic.
extern s32 lbl_8042C868;
extern f32 lbl_8042F2B4; // 1.0f
// HYPOTHESIS: RwFrameUpdateObjects.
RwFrame* fn_8019E880(RwFrame* frame);
}

// Flags the interpolator dirty and, unless frame dirtying is disabled, updates the atomic's frame.
static inline void MarkDirty8014A750(Atomic8014A750* atomic)
{
	atomic->interpFlags |= RP_INTERPOLATOR_DIRTY;
	if (!(atomic->interpFlags & RP_INTERPOLATOR_NO_FRAME_DIRTY) && atomic->frame != 0) {
		fn_8019E880(atomic->frame);
	}
}

// Sets the interpolation time scale and its reciprocal (HYPOTHESIS: RpInterpolatorSetScale).
static inline void SetScale8014A750(Atomic8014A750* atomic, f32 scale)
{
	atomic->time      = scale;
	atomic->recipTime = lbl_8042F2B4 / scale;
	MarkDirty8014A750(atomic);
}

extern "C" {
Atomic8014A750* fn_8014A750(Atomic8014A750* atomic, f32 delta)
{
	void* geometry = atomic->geometry;
	if (geometry != 0) {
		AtomicPlugin105Data8014A750* data
		    = (AtomicPlugin105Data8014A750*)((u8*)atomic + lbl_8042C868);
		GeometryPlugin105Data* geometryData = GEOMETRY_PLUGIN_105_DATA(geometry);
		if (data->geometry != geometry || data->current == 0) {
			data->current  = geometryData->entries;
			data->geometry = geometry;
		}
		if (data->current != 0) {
			data->position += delta;
			while (data->position > data->current->value) {
				data->position
				    = ((MorphCallBack8014A750)geometryData->callback)(atomic, data->position);
			}
			atomic->startMorphTarget = data->current->a;
			MarkDirty8014A750(atomic);
			atomic->endMorphTarget = data->current->b;
			MarkDirty8014A750(atomic);
			atomic->position = data->position;
			MarkDirty8014A750(atomic);
			SetScale8014A750(atomic, data->current->value);
		}
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
