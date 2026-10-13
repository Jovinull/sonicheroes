#include "types.h"

// Whether none of the flags in lbl_8042C320 is set in the object's flags
// (0x18).

struct Fn800A26ECObject {
	u8 unk00[0x18];
	u32 flags; // 0x18
};

extern s32 lbl_8042C320;

extern "C" s32 fn_800A26EC(Fn800A26ECObject* object)
{
	return (u32)__cntlzw(object->flags & lbl_8042C320) >> 5;
}
