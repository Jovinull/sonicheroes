#include "types.h"

// Draws a widget's texture in pieces: two mirrored halves, a nine slice frame,
// or four quadrants. Every piece goes through fn_2_31F0 in quad_submit.c, one
// call each, so the whole file is about laying out corners and texture
// coordinates and letting that function do the drawing.
//
// The translation unit runs from fn_2_2868 at 0x2868 to the end of fn_2_2F94
// at 0x31F0. It is the first cut out of 0x2868 where no private data crosses:
// the templates each function copies its locals from, 0xD4 through 0x1E0 and
// 0x270 through 0x320, are read from inside this run and nowhere else. The
// .rodata is left to the module, as in window_frame.c, because those templates
// and the constants at 0x328 onwards do not form one contiguous range this
// unit could claim.
//
// NonMatching, by six instructions in fn_2_2BC8. The three other functions
// reproduce exactly and fn_2_2BC8 is the right length with the right
// instructions in the right order and the same stack layout; two of its
// floating point registers come out swapped, the corner width taking the
// register the vertical extent gets in the original and the other way round.
// Twenty-odd source forms were measured against it and none moves those two.
//
// Two things about the shape of it are worth writing down.
//
// The size passed to each piece is a struct holding an array rather than two
// named floats. That is not cosmetic: this compiler copies a struct of two
// scalar floats field by field with lfs and stfs, and one holding an array as
// words with lwz and stw, which is what the original does.
//
// The file is compiled with common subexpression elimination off, like
// window_frame.c. With it on, fn_2_2868 and fn_2_2A18 hoist the address of
// their second piece well above the call that uses it. Turning it off costs
// the values the original keeps in registers across statements, which is why
// the corners read back out of the array they were just written to rather than
// through a local: positions.piece[3].x reads positions.piece[1].x, and the
// compiler forwards the register instead of reloading.

typedef struct Vec2 {
	f32 x;
	f32 y;
} Vec2;

typedef struct Size {
	f32 v[2];
} Size;

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct TexCoords {
	f32 left;
	f32 top;
	f32 right;
	f32 bottom;
} TexCoords;

typedef struct TexCoordPair {
	TexCoords piece[2];
} TexCoordPair;

typedef struct TexCoordQuad {
	TexCoords piece[4];
} TexCoordQuad;

typedef struct TexCoordGrid {
	TexCoords piece[9];
} TexCoordGrid;

typedef struct Positions {
	Vec3 piece[4];
} Positions;

typedef struct PositionGrid {
	Vec3 piece[9];
} PositionGrid;

typedef struct Screen {
	u8 padding[0x80];
	f32 width;
} Screen;

extern "C" Screen** lbl_8042C9A4;

extern "C" const Size lbl_2_rodata_D4;
extern "C" const Positions lbl_2_rodata_DC;
extern "C" const TexCoordQuad lbl_2_rodata_10C;
extern "C" const Size lbl_2_rodata_154;
extern "C" const Size lbl_2_rodata_15C;
extern "C" const Size lbl_2_rodata_164;
extern "C" const Size lbl_2_rodata_16C;
extern "C" const PositionGrid lbl_2_rodata_174;
extern "C" const TexCoordGrid lbl_2_rodata_1E0;
extern "C" const Size lbl_2_rodata_270;
extern "C" const Positions lbl_2_rodata_278;
extern "C" const TexCoordPair lbl_2_rodata_2A8;
extern "C" const Size lbl_2_rodata_2C8;
extern "C" const Positions lbl_2_rodata_2D0;
extern "C" const TexCoordPair lbl_2_rodata_300;
extern "C" const f32 lbl_2_rodata_328;
extern "C" const f32 lbl_2_rodata_32C;
extern "C" const f32 lbl_2_rodata_330;
extern "C" const f32 lbl_2_rodata_334;
extern "C" const f32 lbl_2_rodata_338;

extern "C" void fn_2_31F0(
    void* context, Vec3* position, Vec2* size, TexCoords* texcoords, f32 scale);

#pragma opt_common_subs off

extern "C" void fn_2_2868(void* context, Vec3* position, Vec2* size)
{
	Size half;
	TexCoordPair texcoords;
	Positions positions;
	f32 scale;
	f32 u;

	scale = lbl_2_rodata_328 / (*lbl_8042C9A4)->width;

	half      = lbl_2_rodata_2C8;
	half.v[0] = lbl_2_rodata_32C * size->x;
	half.v[1] = size->y;
	u         = size->x * lbl_2_rodata_330;

	positions            = lbl_2_rodata_2D0;
	positions.piece[0].x = position->x;
	positions.piece[0].y = position->y;
	positions.piece[0].z = position->z;
	positions.piece[1].x = position->x + half.v[0];
	positions.piece[1].y = position->y;
	positions.piece[1].z = position->z;

	texcoords                = lbl_2_rodata_300;
	texcoords.piece[0].right = u;
	texcoords.piece[1].left  = u;

	fn_2_31F0(context, &positions.piece[0], (Vec2*)&half, &texcoords.piece[0], scale);
	fn_2_31F0(context, &positions.piece[1], (Vec2*)&half, &texcoords.piece[1], scale);
}

extern "C" void fn_2_2A18(void* context, Vec3* position, Vec2* size)
{
	Size half;
	TexCoordPair texcoords;
	Positions positions;
	f32 scale;
	f32 u;

	scale = lbl_2_rodata_328 / (*lbl_8042C9A4)->width;

	half      = lbl_2_rodata_270;
	half.v[0] = lbl_2_rodata_32C * size->x;
	half.v[1] = size->y;
	u         = size->x * lbl_2_rodata_330;

	positions            = lbl_2_rodata_278;
	positions.piece[0].x = position->x;
	positions.piece[0].y = position->y;
	positions.piece[0].z = position->z;
	positions.piece[1].x = position->x + half.v[0];
	positions.piece[1].y = position->y;
	positions.piece[1].z = position->z;

	texcoords                = lbl_2_rodata_2A8;
	texcoords.piece[0].right = u;
	texcoords.piece[1].left  = u;

	fn_2_31F0(context, &positions.piece[0], (Vec2*)&half, &texcoords.piece[0], scale);
	fn_2_31F0(context, &positions.piece[1], (Vec2*)&half, &texcoords.piece[1], scale);
}

extern "C" void fn_2_2BC8(void* context, Vec3* position, Vec2* size)
{
	Size corner;
	Size vertical;
	Size horizontal;
	Size body;
	PositionGrid positions;
	TexCoordGrid texcoords;
	f32 scale;
	f32 sumY;
	f32 c1;
	f32 step;
	f32 u;
	f32 v;
	TexCoords* leftTex;
	Vec3* leftPos;
	TexCoords* rightTex;
	Vec3* rightPos;

	scale = lbl_2_rodata_328 / (*lbl_8042C9A4)->width;

	corner     = lbl_2_rodata_154;
	vertical   = lbl_2_rodata_15C;
	horizontal = lbl_2_rodata_164;

	horizontal.v[0] = size->x - lbl_2_rodata_334;
	body            = lbl_2_rodata_16C;
	body.v[0]       = horizontal.v[0];
	body.v[1]       = size->y - lbl_2_rodata_334;

	u = size->x * lbl_2_rodata_330;
	v = size->y * lbl_2_rodata_330;

	positions            = lbl_2_rodata_174;
	positions.piece[0].x = position->x;
	positions.piece[0].y = position->y;
	positions.piece[0].z = position->z;

	positions.piece[1].x = (position->x + size->x) - corner.v[0];
	positions.piece[1].y = position->y;
	positions.piece[1].z = position->z;

	positions.piece[2].x = position->x;
	sumY                 = position->y + size->y;
	c1                   = corner.v[1];
	positions.piece[2].y = sumY - c1;
	positions.piece[2].z = position->z;

	positions.piece[3].x = positions.piece[1].x;
	positions.piece[3].y = positions.piece[2].y;
	positions.piece[3].z = position->z;

	positions.piece[4].x = position->x;
	positions.piece[4].y = position->y + c1;
	positions.piece[4].z = position->z;

	positions.piece[5].x = positions.piece[1].x;
	positions.piece[5].y = positions.piece[4].y;
	positions.piece[5].z = position->z;

	positions.piece[6].x = position->x + corner.v[0];
	positions.piece[6].y = position->y;
	positions.piece[6].z = position->z;

	positions.piece[7].x = positions.piece[6].x;
	positions.piece[7].y = sumY - horizontal.v[1];
	positions.piece[7].z = position->z;

	positions.piece[8].x = positions.piece[6].x;
	positions.piece[8].y = positions.piece[4].y;
	positions.piece[8].z = position->z;

	texcoords                 = lbl_2_rodata_1E0;
	texcoords.piece[4].top    = v;
	texcoords.piece[4].bottom = v;
	texcoords.piece[5].top    = v;
	texcoords.piece[5].bottom = v;
	texcoords.piece[8].left   = u;
	texcoords.piece[8].top    = v;
	texcoords.piece[8].right  = u;
	texcoords.piece[8].bottom = v;

	fn_2_31F0(context, &positions.piece[0], (Vec2*)&corner, &texcoords.piece[0], scale);
	fn_2_31F0(context, &positions.piece[1], (Vec2*)&corner, &texcoords.piece[1], scale);
	fn_2_31F0(context, &positions.piece[2], (Vec2*)&corner, &texcoords.piece[2], scale);
	fn_2_31F0(context, &positions.piece[3], (Vec2*)&corner, &texcoords.piece[3], scale);

	leftTex  = &texcoords.piece[4];
	leftPos  = &positions.piece[4];
	rightTex = &texcoords.piece[5];
	rightPos = &positions.piece[5];

	while (positions.piece[4].y <= positions.piece[2].y - vertical.v[1]) {
		fn_2_31F0(context, leftPos, (Vec2*)&vertical, leftTex, scale);
		fn_2_31F0(context, rightPos, (Vec2*)&vertical, rightTex, scale);
		positions.piece[4].y = positions.piece[4].y + vertical.v[1];
		positions.piece[5].y = positions.piece[5].y + vertical.v[1];
	}

	step          = lbl_2_rodata_338;
	vertical.v[1] = step;
	while (positions.piece[4].y <= positions.piece[2].y) {
		fn_2_31F0(context, leftPos, (Vec2*)&vertical, leftTex, scale);
		fn_2_31F0(context, rightPos, (Vec2*)&vertical, rightTex, scale);
		positions.piece[4].y = positions.piece[4].y + step;
		positions.piece[5].y = positions.piece[5].y + step;
	}

	fn_2_31F0(context, &positions.piece[6], (Vec2*)&horizontal, &texcoords.piece[6], scale);
	fn_2_31F0(context, &positions.piece[7], (Vec2*)&horizontal, &texcoords.piece[7], scale);
	fn_2_31F0(context, &positions.piece[8], (Vec2*)&body, &texcoords.piece[8], scale);
}

extern "C" void fn_2_2F94(void* context, Vec3* position, Vec2* size)
{
	Size half;
	Positions positions;
	TexCoordQuad texcoords;
	f32 scale;
	f32 u;
	f32 v;
	f32 right;
	f32 bottom;

	scale = lbl_2_rodata_328 / (*lbl_8042C9A4)->width;

	half      = lbl_2_rodata_D4;
	half.v[0] = lbl_2_rodata_32C * size->x;
	half.v[1] = lbl_2_rodata_32C * size->y;
	u         = size->x * lbl_2_rodata_330;
	v         = size->y * lbl_2_rodata_330;

	positions            = lbl_2_rodata_DC;
	positions.piece[0].x = position->x;
	positions.piece[0].y = position->y;
	positions.piece[0].z = position->z;

	positions.piece[1].x = position->x + half.v[0];
	positions.piece[1].y = position->y;
	positions.piece[1].z = position->z;

	positions.piece[2].x = position->x;
	positions.piece[2].y = position->y + half.v[1];
	positions.piece[2].z = position->z;

	positions.piece[3].x = positions.piece[1].x;
	positions.piece[3].y = positions.piece[2].y;
	positions.piece[3].z = position->z;

	texcoords                 = lbl_2_rodata_10C;
	texcoords.piece[0].right  = u;
	texcoords.piece[0].bottom = v;
	texcoords.piece[1].left   = u;
	texcoords.piece[1].bottom = v;
	texcoords.piece[2].top    = v;
	texcoords.piece[2].right  = u;
	texcoords.piece[3].left   = u;
	texcoords.piece[3].top    = v;

	fn_2_31F0(context, &positions.piece[0], (Vec2*)&half, &texcoords.piece[0], scale);
	fn_2_31F0(context, &positions.piece[1], (Vec2*)&half, &texcoords.piece[1], scale);
	fn_2_31F0(context, &positions.piece[2], (Vec2*)&half, &texcoords.piece[2], scale);
	fn_2_31F0(context, &positions.piece[3], (Vec2*)&half, &texcoords.piece[3], scale);
}
