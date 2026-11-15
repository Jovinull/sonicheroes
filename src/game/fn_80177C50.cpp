// Flushes the pending quad batch lbl_8028D840 (HYPOTHESIS): when quads are queued, saves seven
// render states, draws the batch as an indexed triangle list (4 vertices and 6 indices per quad)
// with depth test and write off, the batch texture, alpha blending and no culling, restores the
// states, then empties the batch and clears its texture. Returns 1. State names follow the
// RenderWare RwRenderState enumeration (HYPOTHESIS).
#include "types.h"

struct QuadBatch80177C50 {
	u8 pad0[0x4];
	void* texture;  // 0x4
	u32 numQuads;   // 0x8
	void* vertices; // 0xC
	u16* indices;   // 0x10
	u8 pad14[0x18 - 0x14];
};

#define RW_STATE_TEXTURE_RASTER 1
#define RW_STATE_ZTEST_ENABLE   6
#define RW_STATE_ZWRITE_ENABLE  8
#define RW_STATE_SHADE_MODE     9
#define RW_STATE_SRC_BLEND      10
#define RW_STATE_DEST_BLEND     11
#define RW_STATE_CULL_MODE      20
#define RW_BLEND_SRC_ALPHA      5
#define RW_BLEND_INV_SRC_ALPHA  6
#define RW_PRIM_TYPE_TRI_LIST   3

extern "C" {
extern QuadBatch80177C50 lbl_8028D840;
// HYPOTHESIS: RwRenderStateGet, RwRenderStateSet and RwIm2DRenderIndexedPrimitive.
s32 fn_80194294(s32 state, void* value);
s32 fn_80194234(s32 state, void* value);
s32 fn_801942EC(s32 primType, void* vertices, s32 numVertices, u16* indices, s32 numIndices);

s32 fn_80177C50(void)
{
	if (lbl_8028D840.numQuads != 0) {
		void* zTest;
		void* zWrite;
		void* srcBlend;
		void* destBlend;
		void* texture;
		void* shadeMode;
		void* cullMode;

		fn_80194294(RW_STATE_ZTEST_ENABLE, &zTest);
		fn_80194294(RW_STATE_ZWRITE_ENABLE, &zWrite);
		fn_80194294(RW_STATE_SRC_BLEND, &srcBlend);
		fn_80194294(RW_STATE_DEST_BLEND, &destBlend);
		fn_80194294(RW_STATE_TEXTURE_RASTER, &texture);
		fn_80194294(RW_STATE_SHADE_MODE, &shadeMode);
		fn_80194294(RW_STATE_CULL_MODE, &cullMode);

		fn_80194234(RW_STATE_ZTEST_ENABLE, (void*)0);
		fn_80194234(RW_STATE_ZWRITE_ENABLE, (void*)0);
		fn_80194234(RW_STATE_SHADE_MODE, (void*)1);
		fn_80194234(RW_STATE_TEXTURE_RASTER, lbl_8028D840.texture);
		fn_80194234(RW_STATE_SRC_BLEND, (void*)RW_BLEND_SRC_ALPHA);
		fn_80194234(RW_STATE_DEST_BLEND, (void*)RW_BLEND_INV_SRC_ALPHA);
		fn_80194234(RW_STATE_CULL_MODE, (void*)1);

		fn_801942EC(RW_PRIM_TYPE_TRI_LIST, lbl_8028D840.vertices, lbl_8028D840.numQuads * 4,
		    lbl_8028D840.indices, lbl_8028D840.numQuads * 6);

		fn_80194234(RW_STATE_ZTEST_ENABLE, zTest);
		fn_80194234(RW_STATE_ZWRITE_ENABLE, zWrite);
		fn_80194234(RW_STATE_SRC_BLEND, srcBlend);
		fn_80194234(RW_STATE_DEST_BLEND, destBlend);
		fn_80194234(RW_STATE_TEXTURE_RASTER, texture);
		fn_80194234(RW_STATE_SHADE_MODE, shadeMode);
		fn_80194234(RW_STATE_CULL_MODE, cullMode);
	}
	lbl_8028D840.numQuads = 0;
	lbl_8028D840.texture  = 0;
	return 1;
}
}
