#include "types.h"

// The word at 0x3C of the object in lbl_8042B624, or -1 when there is none.

struct Fn800CB5BCObject {
	u8 unk00[0x3C];
	s32 value; // 0x3C
};

extern "C" Fn800CB5BCObject* lbl_8042B624;

extern "C" s32 fn_800CB5BC(void)
{
	if (lbl_8042B624 == 0) {
		return -1;
	}
	return lbl_8042B624->value;
}
