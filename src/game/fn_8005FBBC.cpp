// Draws a line from `a` to `b` in the colour `color` (0xAARRGGBB) as two immediate-mode vertices:
// transforms them (fn_801B2934) and renders a line list (fn_801B2C00(2), fn_801B2A14).
// HYPOTHESIS: RwIm3DTransform/RwIm3DRenderPrimitive/RwIm3DEnd. The first vertex gets the green and
// blue bytes swapped, as the retail code stores them.
#include "types.h"

struct Vec8005FBBC {
	f32 x;
	f32 y;
	f32 z;
};

struct Vertex8005FBBC {
	Vec8005FBBC position; // 0x0
	Vec8005FBBC normal;   // 0xC
	u8 red;               // 0x18
	u8 green;             // 0x19
	u8 blue;              // 0x1A
	u8 alpha;             // 0x1B
	f32 u;                // 0x1C
	f32 v;                // 0x20
};

extern "C" {
void* fn_801B2934(Vertex8005FBBC* vertices, s32 count, void* matrix, u32 flags);
void fn_801B2C00(s32 primitive);
void fn_801B2A14(void);
}

static inline void SetPos(Vertex8005FBBC* v, f32 x, f32 y, f32 z)
{
	v->position.x = x;
	v->position.y = y;
	v->position.z = z;
}

static inline void SetRGBA(Vertex8005FBBC* v, u8 r, u8 g, u8 b, u8 a)
{
	v->red   = r;
	v->green = g;
	v->blue  = b;
	v->alpha = a;
}

extern "C" void fn_8005FBBC(Vec8005FBBC* a, Vec8005FBBC* b, u32 color)
{
	Vertex8005FBBC vertices[2];

	f32 ax = a->x;
	f32 ay = a->y;
	f32 az = a->z;
	SetPos(&vertices[0], ax, ay, az);
	SetRGBA(&vertices[0], (color & 0xFF0000) >> 16, color & 0xFF, (color & 0xFF00) >> 8,
	    (color & 0xFF000000) >> 24);
	f32 bx = b->x;
	f32 by = b->y;
	f32 bz = b->z;
	SetPos(&vertices[1], bx, by, bz);
	SetRGBA(&vertices[1], (color & 0xFF0000) >> 16, (color & 0xFF00) >> 8, color & 0xFF,
	    (color & 0xFF000000) >> 24);
	if (fn_801B2934(vertices, 2, NULL, 0) != NULL) {
		fn_801B2C00(2);
		fn_801B2A14();
	}
}
