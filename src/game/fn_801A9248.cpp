#include "types.h"

// Packs the three color channels using the format selected by field 3.
extern "C" {
struct Color801A9248 {
	u8 field0;
	u8 field1;
	u8 field2;
	u8 field3;
};
s32 fn_801A9248(Color801A9248* color)
{
	if (color->field3 != 0xFF) {
		return ((color->field0 * 0x10) & 0xF00) | ((color->field3 << 7) & 0x7000)
		    | (color->field1 & 0xF0) | ((color->field2 >> 4) & 0xF);
	}
	return ((color->field0 << 7) & 0x7C00) | 0x8000 | ((color->field1 << 2) & 0x3E0)
	    | ((color->field2 >> 3) & 0x1F);
}
}
