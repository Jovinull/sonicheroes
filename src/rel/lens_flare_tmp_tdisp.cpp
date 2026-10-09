// TObjEFLensTmp::TDisp. It refreshes the lens's two camera terms (the
// reciprocal of a camera distance and the span between two camera values,
// fn_80194228's minus fn_8019421C's), then draws the particles
// (TObjEFLens::DispPtcl) with fog off and additive blending (source alpha,
// one), and puts the blend back to source alpha over inverse source alpha and
// the fog to what it was. The camera's field is read in the expression itself:
// a camera pointer local loads the constant first. Render states are
// RenderWare's: 0xA source blend, 0xB destination blend, 0xE fog. The classes
// are in lens_flare_class.inc.

#define LENS_FLARE_CTOR     inline
#define LENS_FLARE_SET_CTOR inline
#define LENS_FLARE_DTOR     inline
#include "src/rel/lens_flare_class.inc"
#include "game/mobject.h"

// The current camera's field at +0x80.
struct LensCamera {
	u8 unk00[0x80];
	f32 unk80; // 0x80
};

extern "C" f32 fn_8019421C(void);
extern "C" f32 fn_80194228(void);
extern "C" void fn_80194294(s32 state, s32* value);
extern "C" void fn_80194234(s32 state, s32 value);

void TObjEFLensTmp::TDisp()
{
	f32 first  = fn_8019421C();
	f32 second = fn_80194228();
	s32 fog;

	unk30 = lensFlareOne[0] / ((LensCamera*)GetCurrentCameraPointer())->unk80;
	unk34 = second - first;

	fn_80194294(0xE, &fog);
	fn_80194234(0xE, 0);
	fn_80194234(0xA, 5);
	fn_80194234(0xB, 2);
	DispPtcl();
	fn_80194234(0xA, 5);
	fn_80194234(0xB, 6);
	fn_80194234(0xE, fog);
}
