// HYPOTHESIS: RenderWare RtAnimInterpolatorSetCurrentTime. Moves the interpolator to an absolute time by
// subtracting (fn_8020C968) or adding (fn_8020CC18) the difference from currentTime at +4.

#include "types.h"

struct RtAnimInterpolator {
	void* unk0;
	f32 unk4;
};

extern "C" {
s32 fn_8020C968(RtAnimInterpolator*, f32);
s32 fn_8020CC18(RtAnimInterpolator*, f32);
extern f32 lbl_804300F0;

s32 fn_8020D02C(RtAnimInterpolator* interpolator, f32 time)
{
	f32 delta = time - interpolator->unk4;

	if (delta < lbl_804300F0)
		fn_8020C968(interpolator, -delta);
	else
		fn_8020CC18(interpolator, delta);
	return 1;
}
}
