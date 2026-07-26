#include "types.h"

// Fills a rectangle with a flat colour, and the pair of render state helpers
// it brackets itself with.
//
// The translation unit runs from fn_1_137B8 at 0x137B8 to the end of
// fn_1_1397C at 0x13B24, and owns .rodata 0x1CD0 to 0x1CD8. Those eight bytes
// are not written here: they are the constant the compiler emits for itself to
// convert a signed int to a float, and every one of the eight conversions
// below reads it. The three functions form an island: nothing outside them
// reads that constant, and neither the run before nor the run after can be cut
// to include them.
//
// fn_1_1397C is the same drawing routine as fn_2_26C0 in autosaveD's
// quad_fill.c, down to the vertex layout and the submit call. What differs is
// that autosaveD keeps its saved render state in a module global reached
// through two shared helpers, while this one keeps it in the object at 0x810
// and carries its own pair.
//
// fn_1_13864 saves the ten states it is about to change and sets them;
// fn_1_137B8 puts them back. The last thing each does is set state 1, which is
// how the drawing routine leaves texturing off on the way in and on the way
// out.

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

typedef struct Scene {
	u8 unk0[0x810]; // 0x000
	s32 state[10];  // 0x810
} Scene;

extern "C" void fn_80194234(s32 id, s32 value);
extern "C" void fn_80194294(s32 id, s32* value);
extern "C" f32 fn_8019421C(void);
extern "C" void fn_801942C0(s32 primitive, Vertex* vertices, s32 count);

extern "C" void fn_1_137B8(Scene* scene);
extern "C" void fn_1_13864(Scene* scene);

#pragma dont_inline on

extern "C" void fn_1_137B8(Scene* scene)
{
	fn_80194234(6, scene->state[0]);
	fn_80194234(8, scene->state[1]);
	fn_80194234(12, scene->state[2]);
	fn_80194234(10, scene->state[3]);
	fn_80194234(11, scene->state[4]);
	fn_80194234(9, scene->state[5]);
	fn_80194234(20, scene->state[6]);
	fn_80194234(3, scene->state[7]);
	fn_80194234(4, scene->state[8]);
	fn_80194234(14, scene->state[9]);
	fn_80194234(1, 0);
}

extern "C" void fn_1_13864(Scene* scene)
{
	fn_80194294(6, &scene->state[0]);
	fn_80194294(8, &scene->state[1]);
	fn_80194294(12, &scene->state[2]);
	fn_80194294(10, &scene->state[3]);
	fn_80194294(11, &scene->state[4]);
	fn_80194294(9, &scene->state[5]);
	fn_80194294(20, &scene->state[6]);
	fn_80194294(3, &scene->state[7]);
	fn_80194294(4, &scene->state[8]);
	fn_80194294(14, &scene->state[9]);

	fn_80194234(6, 0);
	fn_80194234(8, 0);
	fn_80194234(12, 1);
	fn_80194234(10, 5);
	fn_80194234(11, 6);
	fn_80194234(9, 1);
	fn_80194234(20, 1);
	fn_80194234(3, 3);
	fn_80194234(4, 3);
	fn_80194234(14, 0);
}

extern "C" void fn_1_1397C(Scene* scene, Rect* rect, u8* color)
{
	Vertex vertices[4];
	f32 depth;

	fn_80194234(1, 0);
	fn_1_13864(scene);
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
	fn_1_137B8(scene);
}
