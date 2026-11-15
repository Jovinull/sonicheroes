// Draws an object's 2D scene (HYPOTHESIS; names inferred) with its own render states: saves the
// eleven states it changes, sets them for alpha-blended (5/6), Gouraud, linear-filtered, clamped
// and unculled drawing without z test, z write or fog, unbinds the raster, draws the scene at 0xC
// between fn_8016F488/fn_8016EAB4 and fn_8016F860, then restores the saved states. Does nothing
// without a scene.
#include "types.h"

// HYPOTHESIS: RenderWare's RwRenderState numbering.
enum RenderState8012CC20 {
	RS_TEXTURE_RASTER    = 1,
	RS_TEXTURE_ADDRESS_U = 3,
	RS_TEXTURE_ADDRESS_V = 4,
	RS_Z_TEST_ENABLE     = 6,
	RS_SHADE_MODE        = 7,
	RS_Z_WRITE_ENABLE    = 8,
	RS_TEXTURE_FILTER    = 9,
	RS_SRC_BLEND         = 10,
	RS_DEST_BLEND        = 11,
	RS_VERTEX_ALPHA      = 12,
	RS_FOG_ENABLE        = 14,
	RS_CULL_MODE         = 20
};

struct Owner8012CC20 {
	u8 pad0[0xC];
	void* scene; // 0xC
};

extern "C" {
// HYPOTHESIS: RwRenderStateGet and RwRenderStateSet.
s32 fn_80194294(s32 state, void* value);
s32 fn_80194234(s32 state, void* value);
void fn_8016F488(void);
void fn_8016EAB4(void);
void fn_802048CC(void* scene);
void fn_8016F860(void);

void fn_8012CC20(Owner8012CC20* owner)
{
	void* zWrite;
	void* zTest;
	void* shadeMode;
	void* filter;
	void* vertexAlpha;
	void* cullMode;
	void* addressU;
	void* addressV;
	void* fog;
	void* srcBlend;
	void* destBlend;

	if (owner->scene == 0) {
		return;
	}
	fn_80194294(RS_Z_WRITE_ENABLE, &zWrite);
	fn_80194294(RS_Z_TEST_ENABLE, &zTest);
	fn_80194294(RS_SHADE_MODE, &shadeMode);
	fn_80194294(RS_TEXTURE_FILTER, &filter);
	fn_80194294(RS_VERTEX_ALPHA, &vertexAlpha);
	fn_80194294(RS_CULL_MODE, &cullMode);
	fn_80194294(RS_TEXTURE_ADDRESS_U, &addressU);
	fn_80194294(RS_TEXTURE_ADDRESS_V, &addressV);
	fn_80194294(RS_FOG_ENABLE, &fog);
	fn_80194294(RS_SRC_BLEND, &srcBlend);
	fn_80194294(RS_DEST_BLEND, &destBlend);
	fn_80194234(RS_Z_WRITE_ENABLE, (void*)0);
	fn_80194234(RS_Z_TEST_ENABLE, (void*)0);
	fn_80194234(RS_SHADE_MODE, (void*)2);
	fn_80194234(RS_TEXTURE_FILTER, (void*)2);
	fn_80194234(RS_VERTEX_ALPHA, (void*)1);
	fn_80194234(RS_CULL_MODE, (void*)1);
	fn_80194234(RS_TEXTURE_ADDRESS_U, (void*)3);
	fn_80194234(RS_TEXTURE_ADDRESS_V, (void*)3);
	fn_80194234(RS_FOG_ENABLE, (void*)0);
	fn_80194234(RS_SRC_BLEND, (void*)5);
	fn_80194234(RS_DEST_BLEND, (void*)6);
	fn_80194234(RS_TEXTURE_RASTER, (void*)0);
	fn_8016F488();
	fn_8016EAB4();
	fn_802048CC(owner->scene);
	fn_8016F860();
	fn_80194234(RS_Z_WRITE_ENABLE, zWrite);
	fn_80194234(RS_Z_TEST_ENABLE, zTest);
	fn_80194234(RS_SHADE_MODE, shadeMode);
	fn_80194234(RS_TEXTURE_FILTER, filter);
	fn_80194234(RS_VERTEX_ALPHA, vertexAlpha);
	fn_80194234(RS_CULL_MODE, cullMode);
	fn_80194234(RS_TEXTURE_ADDRESS_U, addressU);
	fn_80194234(RS_TEXTURE_ADDRESS_V, addressV);
	fn_80194234(RS_FOG_ENABLE, fog);
	fn_80194234(RS_SRC_BLEND, srcBlend);
	fn_80194234(RS_DEST_BLEND, destBlend);
}
}
