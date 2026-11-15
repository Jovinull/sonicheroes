// Returns the position of `id` in the six-entry table lbl_80241C98 ({1, 2, 3, 4, 5, 6}), or -1
// when it is not there. The id's meaning is UNKNOWN.
#include "types.h"

extern "C" {
extern s32 lbl_80241C98[6];

s32 fn_80041B64(s32 id)
{
	int i;

	for (i = 0; i < 6; i++) {
		if (id == lbl_80241C98[i]) {
			return i;
		}
	}
	return -1;
}
}
