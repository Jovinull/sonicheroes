#include "types.h"

// Packs bytes at offsets 0, 1 and 2 into masked high and low word fields.
extern "C" {
struct Color801A9228 {
	u8 r;
	u8 g;
	u8 b;
};

s32 fn_801A9228(Color801A9228* color)
{
	return ((color->r << 8) & 0xF800) | ((color->g << 3) & 0x7E0) | ((color->b >> 3) & 0x1F);
}
}
