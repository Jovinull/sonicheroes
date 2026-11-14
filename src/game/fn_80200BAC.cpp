// Steps a key-frame cursor (HYPOTHESIS): a positive count moves forward over that many key frames,
// a negative one backward; each step sets the cursor time to the key frame's time, runs
// fn_80201B10 on its data with the argument and moves the previous/next pair, clearing the end
// that runs off the list. The retail backward loop decrements the count as well, so it only stops
// at the first key frame. Returns the cursor.
#include "game/keyframe_cursor.h"

extern "C" {
void* fn_8019460C(RwSList* list);
void fn_80201B10(void* data, void* arg);

KeyFrameCursor* fn_80200BAC(KeyFrameCursor* cursor, void* arg, s32 steps)
{
	KeyFrame* first = (KeyFrame*)fn_8019460C(cursor->keyFrames);

	while (steps > 0 && cursor->next) {
		cursor->time = cursor->next->time;
		fn_80201B10(cursor->next->data, arg);
		cursor->previous = cursor->next;
		if (cursor->next < cursor->last) {
			cursor->next++;
		} else {
			cursor->next = 0;
		}
		steps--;
	}
	while (steps < 0 && cursor->previous) {
		cursor->time = cursor->previous->time;
		fn_80201B10(cursor->previous->data, arg);
		cursor->next = cursor->previous;
		if (cursor->previous > first) {
			cursor->previous--;
		} else {
			cursor->previous = 0;
		}
		steps--;
	}
	return cursor;
}
}
