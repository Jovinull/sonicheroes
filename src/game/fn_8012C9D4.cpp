// Per-part callback of fn_8012CEF0 (HYPOTHESIS; names inferred): restarts the part's key-frame
// cursor (fn_80200AC4), then by mode either restarts it again and moves it by a time step
// (mode 0, fn_80200B6C) or restarts it and seeks a key frame (mode 1, fn_80200BAC with the value
// truncated to an index). Returns the part.
#include "game/keyframe_cursor.h"

struct Param8012C9D4 {
	s32 mode;  // 0x0
	f32 value; // 0x4
};

extern "C" {
KeyFrameCursor* fn_80200AC4(KeyFrameCursor* cursor, void* arg);
KeyFrameCursor* fn_80200B6C(KeyFrameCursor* cursor, void* arg, f32 step);
KeyFrameCursor* fn_80200BAC(KeyFrameCursor* cursor, void* arg, s32 index);

void* fn_8012C9D4(void* part, KeyFrameCursor* cursor, void* arg, Param8012C9D4* param)
{
	fn_80200AC4(cursor, arg);
	switch (param->mode) {
		case 0:
			fn_80200AC4(cursor, arg);
			fn_80200B6C(cursor, arg, param->value);
			break;
		case 1:
			fn_80200AC4(cursor, arg);
			fn_80200BAC(cursor, arg, param->value);
			break;
	}
	return part;
}
}
