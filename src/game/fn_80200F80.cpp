// Moves a key-frame cursor to a key frame (HYPOTHESIS: animation interpolator seek): when the
// target lies before the previous key, restarts the cursor as fn_80200AC4 does and steps once,
// then steps forward or back by the distance from the previous key (the index itself when there
// is none). Each step makes the next (or previous) key current, applies its data with fn_80201B10
// and moves to its neighbour, stopping at either end. Returns the cursor.
// The backward loop decrements its negative count, as retail does, so it only stops at the
// first key frame.
#include "game/keyframe_cursor.h"

extern "C" {
extern f32 lbl_8042FF6C;

// HYPOTHESIS: RwSListGetArray.
KeyFrame* fn_8019460C(RwSList* list);
void fn_80201B10(void* data, void* arg);

static inline void Restart80200F80(KeyFrameCursor* cursor, void* arg)
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
}

static inline void Step80200F80(KeyFrameCursor* cursor, void* arg, s32 count)
{
	KeyFrame* first = fn_8019460C(cursor->keyFrames);

	while (count > 0 && cursor->next != 0) {
		cursor->time = cursor->next->time;
		fn_80201B10(cursor->next->data, arg);
		cursor->previous = cursor->next;
		if (cursor->next < cursor->last) {
			cursor->next++;
		} else {
			cursor->next = 0;
		}
		count--;
	}
	while (count < 0 && cursor->previous != 0) {
		cursor->time = cursor->previous->time;
		fn_80201B10(cursor->previous->data, arg);
		cursor->next = cursor->previous;
		if (cursor->previous > first) {
			cursor->previous--;
		} else {
			cursor->previous = 0;
		}
		count--;
	}
}

KeyFrameCursor* fn_80200F80(KeyFrameCursor* cursor, void* arg, s32 index)
{
	KeyFrame* target = fn_8019460C(cursor->keyFrames) + index;
	s32 offset;

	if (target < cursor->previous) {
		Restart80200F80(cursor, arg);
		Step80200F80(cursor, arg, 1);
	}
	if (cursor->previous != 0) {
		offset = target - cursor->previous;
	} else {
		offset = index;
	}
	Step80200F80(cursor, arg, offset);
	return cursor;
}
}
