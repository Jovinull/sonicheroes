#include "types.h"

// Packs the three byte channels into the 0x8000-based GameCube color word.
extern "C" {
struct Color801A9208 {
	u8 r;
	u8 g;
	u8 b;
};

s32 fn_801A9208(Color801A9208* color)
{
	return ((color->r << 7) & 0x7C00) | 0x8000 | ((color->g << 2) & 0x3E0)
	    | ((color->b >> 3) & 0x1F);
}
}
