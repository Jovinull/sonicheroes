#include "types.h"

struct Placement {
	u32 values[4];
};

struct Color {
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
};

extern "C" u32 lbl_8029BB80[];

extern "C" void fn_2_26C0(void* state, Placement* placement, Color* color);

extern "C" void fn_2_340C(void* state)
{
	Placement placement;
	placement.values[0] = 0;
	placement.values[1] = 0;
	placement.values[2] = lbl_8029BB80[1];
	placement.values[3] = lbl_8029BB80[2];

	Color color;
	color.red   = 0;
	color.green = 0;
	color.blue  = 0;
	color.alpha = 0xA0;

	fn_2_26C0(state, &placement, &color);
}
