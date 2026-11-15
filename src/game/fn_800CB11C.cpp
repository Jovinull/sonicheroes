// Returns the state byte (+0x29) of sound stream entry `index` of lbl_8042B634 (two entries, see
// fn_800CB84C), or -1 when the index is out of range or the entry is not allocated.
#include "types.h"

struct Entry800CB11C {
	u8 pad0[0x29];
	u8 state; // 0x29 (signed char in fn_800CB84C; read unsigned here)
};

extern "C" {
extern Entry800CB11C* lbl_8042B634[2];

s32 fn_800CB11C(s8 index)
{
	Entry800CB11C* entry;

	if (index < 0 || index >= 2) {
		return -1;
	}
	entry = lbl_8042B634[index];
	if (entry == NULL) {
		return -1;
	}
	return entry->state;
}
}
