#include "types.h"

// TObjSpring's parameter guard: the last slot of its second base's vtable, the
// same slot sample1Clamp fills for TObjSample.
//
// The code is the same shape in thirteen of the fourteen stage modules, so it
// is written once and each module's unified split names it. stage40D is a
// different revision of the source and is left out, as it is for rel/prolog.c
// and the two sample objects.
//
// What the fields are comes from the strings the module keeps beside the
// spring's vtable: "Power(Def. 5.0f)" for the float, bounded here to -5 up to
// 10, and "No Ctrl Time(Frm)" for the halfword, bounded to a non negative
// count of frames.

typedef struct SpringParams {
	f32 power;      // 0x00
	s16 noCtrlTime; // 0x04
} SpringParams;

typedef struct Frame {
	u8 unk0[0x2C];        // 0x00
	SpringParams* params; // 0x2C
} Frame;

// The object it is called on is not used: everything it touches hangs off the
// keyframe it is handed.
static inline void springClampImpl(void* object, Frame* frame)
{
	SpringParams* params = frame->params;

	if (params->power < -5.0f) {
		params->power = -5.0f;
	}
	if (params->power > 10.0f) {
		params->power = 10.0f;
	}
	if (params->noCtrlTime < 0) {
		params->noCtrlTime = 0;
	}
	if (params->noCtrlTime > 0x7FFF) {
		params->noCtrlTime = 0x7FFF;
	}
}
