// Resets a key-frame cursor (HYPOTHESIS: animation interpolator start): sets its time to the
// .sdata2 constant lbl_8042FF6C and, when its list has key frames, clears the previous key, points
// the next key at the first frame and the last key at the final one, then runs fn_80201B10 on the
// first frame's data with the argument; otherwise clears all three key pointers. Returns the
// cursor.
#include "game/keyframe_cursor.h"

extern "C" {
extern f32 lbl_8042FF6C;

void fn_80201B10(void* data, void* arg);

KeyFrameCursor* fn_80200AC4(KeyFrameCursor* cursor, void* arg)
{
	s32 count = fn_8019469C(cursor->keyFrames);

	cursor->time = lbl_8042FF6C;
	if (count >= 1) {
		cursor->previous = 0;
		cursor->next     = (KeyFrame*)fn_8019472C(cursor->keyFrames, 0);
		cursor->last     = (KeyFrame*)fn_8019472C(cursor->keyFrames, count - 1);
		fn_80201B10(cursor->next->data, arg);
	} else {
		cursor->previous = 0;
		cursor->next     = 0;
		cursor->last     = 0;
	}
	return cursor;
}
}
