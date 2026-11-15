// Draws one 2D immediate-mode line between two vertices of an array (HYPOTHESIS: the GameCube
// RwIm2DRenderLine): sets up the immediate-mode state (fn_801A7B70), sends a two-vertex GX_LINES
// primitive with position and colour, plus texture coordinates when a texture is bound
// (lbl_8042CA54), then restores the state (fn_801A7E58). Returns 1.
extern "C" {
#include "dolphin/gx.h"
}
#include "game/rw_engine.h"

// Immediate-mode 2D vertex (HYPOTHESIS: RwIm2DVertex on GameCube).
struct RwIm2DVertex801A83F0 {
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

extern "C" {
// Currently bound texture slot; non-null contents mean textured vertices.
extern u32* lbl_8042CA54;
void fn_801A7B70(void);
void fn_801A7E58(void);

static inline void SendVertex801A83F0(const RwIm2DVertex801A83F0* vertex, s32 textured)
{
	GXPosition3f32(vertex->x, vertex->y, vertex->z);
	GXColor4u8(vertex->red, vertex->green, vertex->blue, vertex->alpha);
	if (textured) {
		GXTexCoord2f32(vertex->u, vertex->v);
	}
}

s32 fn_801A83F0(RwIm2DVertex801A83F0* vertices, s32 numVertices, s32 vert1, s32 vert2)
{
	RwIm2DVertex801A83F0* a = &vertices[vert1];
	RwIm2DVertex801A83F0* b = &vertices[vert2];

	fn_801A7B70();
	GXBegin(GX_LINES, GX_VTXFMT0, 2);
	if (*lbl_8042CA54 != 0) {
		SendVertex801A83F0(a, 1);
		SendVertex801A83F0(b, 1);
	} else {
		SendVertex801A83F0(a, 0);
		SendVertex801A83F0(b, 0);
	}
	fn_801A7E58();
	return 1;
}
}
