// Applies a key-frame cursor (HYPOTHESIS): after fn_80201390 updates it, computes the blend
// factor of its time between the previous and next key frames (the .sdata2 constant
// lbl_8042FF6C when the update fails or either key is missing) and hands the next key frame's
// data, or the last one's when there is no next key, to fn_80201E58 with the argument. Returns
// the cursor, or null when there is no key frame or fn_80201E58 fails.
#include "game/keyframe_cursor.h"

extern "C" {
extern f32 lbl_8042FF6C;

s32 fn_80201390(KeyFrameCursor* cursor);
void* fn_80201E58(void* data, void* arg, f32 blend);

KeyFrameCursor* fn_80200CB0(KeyFrameCursor* cursor, void* arg)
{
	f32 blend;

	if (fn_80201390(cursor)) {
		if (cursor->previous && cursor->next) {
			blend = (cursor->time - cursor->previous->time)
			    / (cursor->next->time - cursor->previous->time);
		} else {
			blend = lbl_8042FF6C;
		}
	} else {
		blend = lbl_8042FF6C;
	}

	if (cursor->next) {
		if (fn_80201E58(cursor->next->data, arg, blend)) {
			return cursor;
		}
	} else if (cursor->last) {
		if (fn_80201E58(cursor->last->data, arg, blend)) {
			return cursor;
		}
	}
	return 0;
}
}
