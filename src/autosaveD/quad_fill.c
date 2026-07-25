#include "types.h"

// Fills a rectangle with a flat colour.
//
// The translation unit is the single function fn_2_26C0, .text 0x26C0 to
// 0x2868, and it owns .rodata 0x320 to 0x328. That eight byte block is not
// written here: it is the constant the compiler emits for itself to convert a
// signed int to a float, and every one of the eight conversions below reads
// it. The cut is the first one out of 0x26C0 where no private data crosses.
//
// It is the untextured twin of fn_2_31F0 in quad_submit.c. Same four vertices
// in the same order, same submit call, and the same vertex layout, but the
// corners come from a rectangle in integer screen coordinates rather than a
// float position and size, the depth is whatever the renderer is currently
// handing out, and nothing writes the texture coordinates.
//
// fn_80194234(1, 0) is the last thing fn_2_24FC does as well, so the pair
// around the body is a save, a set and a restore of the same render state.

typedef struct Vec2 {
	f32 x;
	f32 y;
} Vec2;

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct Vertex {
	Vec3 position;
	u8 color[4];
	Vec2 texcoord;
} Vertex;

typedef struct Rect {
	s32 x;
	s32 y;
	s32 width;
	s32 height;
} Rect;

struct AutosaveState;

extern "C" void fn_80194234(s32 id, s32 value);
extern "C" f32 fn_8019421C(void);
extern "C" void fn_801942C0(s32 primitive, Vertex* vertices, s32 count);
extern "C" void fn_2_24FC(AutosaveState* state);
extern "C" void fn_2_25A8(AutosaveState* state);

extern "C" void fn_2_26C0(AutosaveState* state, Rect* rect, u8* color)
{
	Vertex vertices[4];
	f32 depth;

	fn_80194234(1, 0);
	fn_2_25A8(state);
	depth = fn_8019421C();

	vertices[0].position.x = rect->x;
	vertices[0].position.y = rect->y;
	vertices[0].position.z = depth;

	vertices[1].position.x = rect->x;
	vertices[1].position.y = rect->y + rect->height;
	vertices[1].position.z = depth;

	vertices[2].position.x = rect->x + rect->width;
	vertices[2].position.y = rect->y;
	vertices[2].position.z = depth;

	vertices[3].position.x = rect->x + rect->width;
	vertices[3].position.y = rect->y + rect->height;
	vertices[3].position.z = depth;

	vertices[0].color[0] = color[0];
	vertices[0].color[1] = color[1];
	vertices[0].color[2] = color[2];
	vertices[0].color[3] = color[3];

	vertices[1].color[0] = color[0];
	vertices[1].color[1] = color[1];
	vertices[1].color[2] = color[2];
	vertices[1].color[3] = color[3];

	vertices[2].color[0] = color[0];
	vertices[2].color[1] = color[1];
	vertices[2].color[2] = color[2];
	vertices[2].color[3] = color[3];

	vertices[3].color[0] = color[0];
	vertices[3].color[1] = color[1];
	vertices[3].color[2] = color[2];
	vertices[3].color[3] = color[3];

	fn_801942C0(4, vertices, 4);
	fn_2_24FC(state);
}
