#include "types.h"

// Packs four bytes into the corresponding lanes of a 32-bit word.
extern "C" {
struct Color801A92BC {
	u8 b0;
	u8 b1;
	u8 b2;
	u8 b3;
};

s32 fn_801A92BC(Color801A92BC* color)
{
	return color->b2
	    | ((((color->b3 << 24) | ((color->b0 << 16) & ~0xFF000000)) & ~0xFF00)
	        | ((color->b1 << 8) & 0xFF00));
}
}
