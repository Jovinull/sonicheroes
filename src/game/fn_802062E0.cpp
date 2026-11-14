// Looks up a value in the 0x401-entry table lbl_80298F00: returns the value of the first entry
// whose threshold is above x, or the .sdata2 constant lbl_8042FFB0 when none is.
#include "types.h"

// Table entry (field names inferred from this lookup only).
struct Entry802062E0 {
	f32 value;     // 0x0
	f32 threshold; // 0x4
};

extern "C" {
extern Entry802062E0 lbl_80298F00[0x401];
extern f32 lbl_8042FFB0;

f32 fn_802062E0(f32 x)
{
	for (s32 i = 0; i < 0x401; i++) {
		if (lbl_80298F00[i].threshold > x) {
			return lbl_80298F00[i].value;
		}
	}
	return lbl_8042FFB0;
}
}
