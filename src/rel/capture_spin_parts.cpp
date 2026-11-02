#include "types.h"

// The capture enemy's part spin (captureSpinParts here), the same in the
// seven stage modules that carry the capture: while spinning, its first part
// takes its anchor's matrix and the next two are turned half round the Y
// axis before taking theirs; the spin angle then moves on by 0x1000 and the
// pulse follows its sine between 0 and 1.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwFrame RwFrame;
typedef struct RwMatrix RwMatrix;

typedef struct CapturePart {
	u8 unk00[0x4];
	RwFrame* frame; // 0x04
} CapturePart;

typedef struct Capture {
	u8 unk000[0x268];
	void* anchors[3]; // 0x268
	u8 unk274[0x10];
	s32 angle; // 0x284
	f32 pulse; // 0x288
	s32 spin;  // 0x28C
	u8 unk290[0x48];
	CapturePart* parts[3]; // 0x2D8
} Capture;

extern "C" const RwV3d AxisY;
extern "C" const f32 captureHalfTurn;
extern "C" const f32 captureHalf;

extern "C" RwMatrix* fn_8019E8EC(void* anchor);
extern "C" void fn_8019ECCC(RwFrame* frame, RwMatrix* matrix, s32 combine);
extern "C" void fn_8019ED68(RwFrame* frame, const RwV3d* axis, f32 angle, s32 combine);
extern "C" f32 fn_800D7B00(s32 angle);

extern "C" void captureSpinParts(Capture* object)
{
	if (object->spin != 0) {
		CapturePart* part = object->parts[0];

		if (part != NULL && object->anchors[2] != NULL) {
			RwFrame* frame = part->frame;

			fn_8019ECCC(frame, fn_8019E8EC(object->anchors[2]), 0);
		}
		part = object->parts[1];
		if (part != NULL && object->anchors[0] != NULL) {
			RwFrame* frame = part->frame;

			fn_8019ED68(frame, &AxisY, captureHalfTurn, 0);
			fn_8019ECCC(frame, fn_8019E8EC(object->anchors[0]), 2);
		}
		part = object->parts[2];
		if (part != NULL && object->anchors[1] != NULL) {
			RwFrame* frame = part->frame;

			fn_8019ED68(frame, &AxisY, captureHalfTurn, 0);
			fn_8019ECCC(frame, fn_8019E8EC(object->anchors[1]), 2);
		}
		object->angle += 0x1000;
		{
			f32 sine = fn_800D7B00(object->angle);

			object->pulse = captureHalf + captureHalf * sine;
		}
	}
}
