// Copies the three-word plugin record at object + lbl_8042C868 (see fn_80149E54) from src to dst
// (HYPOTHESIS: the plugin's copy callback). When the record's key (word 8) no longer matches the
// source object's word at 0x18, the copy is reset to the constructor defaults instead. A copied
// record with a descriptor applies the descriptor's two shorts (+0x4/+0x6) and value (+0x8, also
// stored as its reciprocal) and the record's value to dst at 0x50-0x5C, flagging dst dirty after
// each. Returns dst. Names are inferred from this function only.
// NonMatching: retail loads src->key before the plugin offset and builds the source record
// pointer in the src register (r4); this source keeps src in r4 and the record in r3, so the
// first block is ordered differently (12 words). Load-order and comparison-order variants do not
// change it.
#include "game/rw_engine.h"

struct Descriptor80149E74 {
	u8 pad0[0x4];
	s16 value4; // 0x4
	s16 value6; // 0x6
	f32 value8; // 0x8
};

struct Rec80149E74 {
	Descriptor80149E74* descriptor; // 0x0
	f32 value;                      // 0x4
	u32 key;                        // 0x8
};

struct Object80149E74 {
	u8 pad0[0x4];
	RwFrame* frame; // 0x4
	u8 pad8[0x18 - 0x8];
	u32 key; // 0x18
	u8 pad1C[0x4C - 0x1C];
	u32 flags;        // 0x4C
	s16 value50;      // 0x50
	s16 value52;      // 0x52
	f32 value54;      // 0x54
	f32 recipValue54; // 0x58
	f32 value5C;      // 0x5C
};

#define OBJECT_80149E74_DIRTY         0x3
#define OBJECT_80149E74_NO_FRAME_SYNC 0x4

extern "C" {
extern s32 lbl_8042C868;
extern f32 lbl_8042F2B0;
extern f32 lbl_8042F2B4; // 1.0f
// HYPOTHESIS: RwFrameUpdateObjects.
RwFrame* fn_8019E880(RwFrame* frame);
}

// Flags the object dirty and, unless frame sync is suppressed, updates its frame.
static inline void MarkDirty80149E74(Object80149E74* object)
{
	object->flags |= OBJECT_80149E74_DIRTY;
	if (!(object->flags & OBJECT_80149E74_NO_FRAME_SYNC) && object->frame != 0) {
		fn_8019E880(object->frame);
	}
}

extern "C" {
Object80149E74* fn_80149E74(Object80149E74* dst, Object80149E74* src)
{
	Rec80149E74* srcRec = (Rec80149E74*)((u8*)src + lbl_8042C868);
	Rec80149E74* dstRec = (Rec80149E74*)((u8*)dst + lbl_8042C868);

	u32 key = srcRec->key;

	if (key != src->key) {
		dstRec->descriptor = 0;
		dstRec->value      = lbl_8042F2B0;
		dstRec->key        = 0;
	} else {
		dstRec->descriptor = srcRec->descriptor;
		dstRec->value      = srcRec->value;
		dstRec->key        = key;
		if (dstRec->descriptor != 0) {
			dst->value50 = dstRec->descriptor->value4;
			MarkDirty80149E74(dst);
			dst->value52 = dstRec->descriptor->value6;
			MarkDirty80149E74(dst);
			dst->value54      = dstRec->descriptor->value8;
			dst->recipValue54 = lbl_8042F2B4 / dstRec->descriptor->value8;
			MarkDirty80149E74(dst);
			dst->value5C = dstRec->value;
			MarkDirty80149E74(dst);
		}
	}
	return dst;
}
}
