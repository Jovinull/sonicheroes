// Draws a textured 2D quad (HYPOTHESIS: a menu sprite helper; names inferred): builds a
// four-vertex strip at (x, y, z) spanning width * lbl_8042EE40 by height * lbl_8042EE40, with the
// texture coordinates of the cell starting at (0xC, 0x10) of the source and lbl_8042EE44 wide, all
// in the given colour (opaque white when none), and renders it (fn_801942C0). Built with the
// game-unit flags and -fp_contract off.
// NonMatching: retail copies the white default from one register and allocates the corner floats
// differently (21 register-only words, same instructions).
#include "types.h"

struct Vertex8012F03C {
	f32 x;    // 0x0
	f32 y;    // 0x4
	f32 z;    // 0x8
	u8 red;   // 0xC
	u8 green; // 0xD
	u8 blue;  // 0xE
	u8 alpha; // 0xF
	f32 u;    // 0x10
	f32 v;    // 0x14
};

struct Cell8012F03C {
	u8 pad0[0xC];
	f32 u; // 0xC
	f32 v; // 0x10
};

struct Color8012F03C {
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
};

extern "C" {
extern f32 lbl_8042EE40;
extern f32 lbl_8042EE44;
// HYPOTHESIS: RwIm2DRenderPrimitive (4: triangle strip).
s32 fn_801942C0(s32 primType, Vertex8012F03C* vertices, s32 numVertices);

void fn_8012F03C(void* owner, Cell8012F03C* cell, Color8012F03C* color, f32 x, f32 y, f32 z,
    f32 unused, f32 width, f32 height)
{
	Vertex8012F03C quad[4];
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
	f32 u0;
	f32 v0;
	f32 x1;
	f32 y1;
	f32 u1;
	f32 v1;

	if (color != 0) {
		red   = color->red;
		green = color->green;
		blue  = color->blue;
		alpha = color->alpha;
	} else {
		red   = 0xFF;
		green = 0xFF;
		blue  = 0xFF;
		alpha = 0xFF;
	}

	quad[0].x     = x;
	quad[0].y     = y;
	quad[0].z     = z;
	quad[0].red   = red;
	quad[0].green = green;
	quad[0].blue  = blue;
	quad[0].alpha = alpha;
	u0            = cell->u;
	quad[0].u     = u0;
	v0            = cell->v;
	quad[0].v     = v0;

	quad[1].x     = x;
	y1            = y + lbl_8042EE40 * height;
	quad[1].y     = y1;
	quad[1].z     = z;
	quad[1].red   = red;
	quad[1].green = green;
	quad[1].blue  = blue;
	quad[1].alpha = alpha;
	quad[1].u     = u0;
	v1            = lbl_8042EE44 + v0;
	quad[1].v     = v1;

	x1            = x + lbl_8042EE40 * width;
	quad[2].x     = x1;
	quad[2].y     = y;
	quad[2].z     = z;
	quad[2].red   = red;
	quad[2].green = green;
	quad[2].blue  = blue;
	quad[2].alpha = alpha;
	u1            = lbl_8042EE44 + u0;
	quad[2].u     = u1;
	quad[2].v     = v0;

	quad[3].x     = x1;
	quad[3].y     = y1;
	quad[3].z     = z;
	quad[3].red   = red;
	quad[3].green = green;
	quad[3].blue  = blue;
	quad[3].alpha = alpha;
	quad[3].u     = u1;
	quad[3].v     = v1;

	fn_801942C0(4, quad, 4);
}
}
