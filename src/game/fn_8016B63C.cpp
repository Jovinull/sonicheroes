// Applies fn_8016AC30 with arg to every path of a chain whose word at +0x8 is set, following the
// next pointers at +0x14 (HYPOTHESIS: an Rt2d path walk; the compiler inlines the recursion
// several levels deep). Returns the first path. Names are inferred from this function only.
#include "types.h"

struct Path8016B63C {
	u8 pad0[0x8];
	s32 active; // 0x8
	u8 padC[0x14 - 0xC];
	Path8016B63C* next; // 0x14
};

extern "C" {
void fn_8016AC30(Path8016B63C* path, void* arg);

Path8016B63C* fn_8016B63C(Path8016B63C* path, void* arg)
{
	if (path != 0) {
		if (path->active != 0) {
			fn_8016AC30(path, arg);
		}
		fn_8016B63C(path->next, arg);
	}
	return path;
}
}
