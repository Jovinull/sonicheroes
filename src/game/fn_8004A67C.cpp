// Render callback installed by fn_8004A6F0: when a statistics record is selected (lbl_8042C1E0,
// a 0x10-byte cell), adds the object's two counts (fn_80158920 into +0x8, fn_80158918 into +0xC)
// to it, then runs the original callback lbl_8042C1D4 and returns the object. HYPOTHESIS: a
// debug per-cell polygon/vertex counter around an atomic's render callback; the RenderWare
// names are UNKNOWN.
#include "types.h"

struct Stats8004A67C {
	u8 pad0[0x8];
	s32 count8; // 0x8
	s32 countC; // 0xC
};

extern "C" {
extern Stats8004A67C* lbl_8042C1E0;
extern void* (*lbl_8042C1D4)(void* object);
s32 fn_80158920(void* object);
s32 fn_80158918(void* object);

void* fn_8004A67C(void* object)
{
	if (lbl_8042C1E0 != NULL) {
		lbl_8042C1E0->count8 += fn_80158920(object);
		lbl_8042C1E0->countC += fn_80158918(object);
	}
	lbl_8042C1D4(object);
	return object;
}
}
