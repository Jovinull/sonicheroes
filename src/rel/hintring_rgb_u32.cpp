#include "types.h"

// The hint ring's colour at the index of its colour table (5-bit red, green
// and blue) packed as an opaque 0xAARRGGBB (hintringGetRGB here; the GameCube
// build's own, beside GetRGB_Rw).

extern "C" u16 hintringColors[];

u32 hintringGetRGB(int index)
{
	u16 color = hintringColors[index];
	u8 red    = (color & 0x1F) << 3;
	u8 green  = ((color >> 5) & 0x1F) << 3;
	u8 blue   = ((color >> 10) & 0x1F) << 3;

	return blue | (0xFF000000 | (red << 16) | (green << 8));
}
