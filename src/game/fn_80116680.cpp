// Advances a looping key-frame cursor to a time (HYPOTHESIS; names inferred): wraps the time held
// by the caller into [0, duration) of the cursor's animation (fn_802012B8, the last key time);
// when the wrapped time lies before the cursor's current time (fn_802012B0) the cursor restarts
// (fn_80200AC4) and steps by the whole time, otherwise by the difference (fn_80200B6C). Stores the
// cursor's new time back. Returns the owner, untouched when the animation has no duration.
// NonMatching: retail lays the early return right after the duration test (with a dead branch)
// and reloads the 0.0f constant for the second loop, as a re-materialised literal would; a
// literal would add this unit's own .sdata2 constant, so the shared lbl_8042EA20 is used (12
// words, same instructions).
#include "game/keyframe_cursor.h"

extern "C" {
extern f32 lbl_8042EA20; // 0.0f
f32 fn_802012B0(KeyFrameCursor* cursor);
f32 fn_802012B8(KeyFrameCursor* cursor);
KeyFrameCursor* fn_80200AC4(KeyFrameCursor* cursor, void* arg);
KeyFrameCursor* fn_80200B6C(KeyFrameCursor* cursor, void* arg, f32 step);

void* fn_80116680(void* owner, KeyFrameCursor* cursor, void* arg, f32* time)
{
	f32 t = *time;
	f32 duration;
	f32 step;

	duration = fn_802012B8(cursor);
	if (lbl_8042EA20 != duration) {
		while (duration < t) {
			t -= duration;
		}
		while (t < lbl_8042EA20) {
			t += duration;
		}
	} else {
		return owner;
	}
	step = t - fn_802012B0(cursor);
	if (step < lbl_8042EA20) {
		fn_80200AC4(cursor, arg);
		step = t;
	}
	fn_80200B6C(cursor, arg, step);
	*time = fn_802012B0(cursor);
	return owner;
}
}
