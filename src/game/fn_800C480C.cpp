// Advances an animation to time *time, wrapped into [0, duration): when the new time is before the
// current one the animation is restarted first (fn_80200AC4) and advanced by the whole time,
// otherwise by the difference (fn_80200B6C); *time then receives the resulting current time.
// Returns `result`, also unchanged when the animation has no duration. HYPOTHESIS: RtAnim
// interpolator helpers (fn_802012B8 the duration, fn_802012B0 the current time); the names are
// UNKNOWN.
#include "types.h"

extern "C" {
extern f32 lbl_8042DE54; // 0.0f
f32 fn_802012B8(void* anim);
f32 fn_802012B0(void* anim);
void fn_80200AC4(void* anim, void* data);
void fn_80200B6C(void* anim, void* data, f32 delta);

// The retail code reloads the 0.0 constant after the first loop (no common subexpression
// elimination in this function).
#pragma opt_common_subs off
void* fn_800C480C(void* result, void* anim, void* data, f32* time)
{
	f32 t        = *time;
	f32 duration = fn_802012B8(anim);
	f32 delta;

	if (lbl_8042DE54 == duration) {
		return result;
	}
	while (duration < t) {
		t -= duration;
	}
	while (t < lbl_8042DE54) {
		t += duration;
	}
	delta = t - fn_802012B0(anim);
	if (delta < lbl_8042DE54) {
		fn_80200AC4(anim, data);
		delta = t;
	}
	fn_80200B6C(anim, data, delta);
	*time = fn_802012B0(anim);
	return result;
}
#pragma opt_common_subs reset
}
