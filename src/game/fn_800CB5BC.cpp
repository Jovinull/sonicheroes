#include "types.h"

struct Fn800CB5BCData {
	u8 pad[0x3C];
	s32 field3C;
};

extern "C" Fn800CB5BCData* lbl_8042B624;

extern "C" s32 fn_800CB5BC(void)
{
	if (lbl_8042B624 == 0) {
		return -1;
	}
	return lbl_8042B624->field3C;
}
