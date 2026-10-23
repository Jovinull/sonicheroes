#include "types.h"

// The hint ring's GetRGB_Rw (a local function in the PS2 build;
// hintringGetRGB_Rw here): the colour at the index of the ring's colour table
// (5-bit red, green and blue) as an opaque RwRGBA.

typedef struct RwRGBA {
	u8 red, green, blue, alpha;
} RwRGBA;

extern "C" u16 hintringColors[];

void hintringGetRGB_Rw(int index, RwRGBA* color)
{
	color->red   = (hintringColors[index] & 0x1F) << 3;
	color->green = ((hintringColors[index] >> 5) & 0x1F) << 3;
	color->blue  = ((hintringColors[index] >> 10) & 0x1F) << 3;
	color->alpha = 0xFF;
}
