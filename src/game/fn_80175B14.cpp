// Classifies a point against a triangle of 2D vertices (HYPOTHESIS: an Rt2d triangulation helper;
// names inferred). For each edge a-b, b-c and c-a, takes the unit normal of the edge (fn_8019930C)
// and the sign of the dot product with the vector from the point to the edge start: positive
// gives 1, negative 2 and zero 4. Returns 8 when the point is on the positive side of all three
// edges, 4 when it lies on an edge line and 0x10 otherwise.
// NonMatching: same 153 instructions; the floating-point registers of each dot product are
// allocated one step apart (24 words). Tried swapped products, delta locals and a vector dot
// helper.
#include "game/matrix.h"

#define POINT_INSIDE  0x8
#define POINT_ON_EDGE 0x4
#define POINT_OUTSIDE 0x10

struct Vertex80175B14 {
	u8 pad0[0x4];
	s32 index; // 0x4: index into the shape's positions
};

struct Shape80175B14 {
	u8 pad0[0x10];
	RwV2d* positions; // 0x10
};

extern "C" {
extern f64 lbl_8042F4C8; // 0.0
// HYPOTHESIS: RwV2dNormalize.
f32 fn_8019930C(RwV2d* out, const RwV2d* in);

static inline u32 EdgeSide80175B14(
    Shape80175B14* shape, Vertex80175B14* point, Vertex80175B14* from, Vertex80175B14* to)
{
	RwV2d normal;
	f32 dot;

	normal.x = shape->positions[to->index].y - shape->positions[from->index].y;
	normal.y = shape->positions[from->index].x - shape->positions[to->index].x;
	fn_8019930C(&normal, &normal);
	dot = (shape->positions[from->index].x - shape->positions[point->index].x) * normal.x
	    + (shape->positions[from->index].y - shape->positions[point->index].y) * normal.y;
	if (dot > lbl_8042F4C8) {
		return 1;
	} else if (dot < lbl_8042F4C8) {
		return 2;
	}
	return 4;
}

s32 fn_80175B14(Shape80175B14* shape, Vertex80175B14* point, Vertex80175B14* a, Vertex80175B14* b,
    Vertex80175B14* c)
{
	u32 sideA = EdgeSide80175B14(shape, point, a, b);
	u32 sideB = EdgeSide80175B14(shape, point, b, c);
	u32 sideC = EdgeSide80175B14(shape, point, c, a);
	s32 result;

	if ((sideC & (sideA & sideB)) == 1) {
		result = POINT_INSIDE;
	} else if ((sideC | (sideA | sideB)) & 4) {
		result = POINT_ON_EDGE;
	} else {
		result = POINT_OUTSIDE;
	}
	return result;
}
}
