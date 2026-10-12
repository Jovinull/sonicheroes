#include "types.h"

// Decompiled from main's uncut function at 0x800A3D6C.
struct TFn800A3D6CData {
	u8 mPadding0[0x19C];
	s32 mValue19C;
};

extern "C" s32 fn_800A3D6C(TFn800A3D6CData* arg0)
{
	s32 value = arg0->mValue19C;
	switch (value) {
		case 0x24:
		case 0x25:
			return 0;
		default:
			return 1;
	}
}
