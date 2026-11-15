// Prepares the render states of a 2D menu layer (HYPOTHESIS; names inferred): saves ten render
// states into the layer (0x228C-0x22B0) and sets them for alpha-blended, unfogged sprites, then
// binds the raster of the layer's texture (0x2284) when it has one. The state numbers follow
// RenderWare's RwRenderState (HYPOTHESIS).
#include "types.h"

struct Texture8012F728 {
	void* raster; // 0x0
};

struct Layer8012F728 {
	u8 pad0[0x2284];
	Texture8012F728* texture; // 0x2284
	u8 pad2288[0x228C - 0x2288];
	void* saved[10]; // 0x228C
};

extern "C" {
// HYPOTHESIS: RwRenderStateGet and RwRenderStateSet.
s32 fn_80194294(s32 state, void* value);
s32 fn_80194234(s32 state, void* value);

void fn_8012F728(Layer8012F728* layer)
{
	fn_80194294(6, &layer->saved[0]);
	fn_80194294(8, &layer->saved[1]);
	fn_80194294(12, &layer->saved[2]);
	fn_80194294(10, &layer->saved[3]);
	fn_80194294(11, &layer->saved[4]);
	fn_80194294(9, &layer->saved[5]);
	fn_80194294(20, &layer->saved[6]);
	fn_80194294(14, &layer->saved[7]);
	fn_80194294(3, &layer->saved[8]);
	fn_80194294(4, &layer->saved[9]);
	fn_80194234(6, (void*)0);
	fn_80194234(8, (void*)0);
	fn_80194234(12, (void*)1);
	fn_80194234(10, (void*)5);
	fn_80194234(11, (void*)6);
	fn_80194234(9, (void*)1);
	fn_80194234(20, (void*)1);
	fn_80194234(14, (void*)0);
	fn_80194234(3, (void*)3);
	fn_80194234(4, (void*)3);
	if (layer->texture != 0) {
		fn_80194234(1, layer->texture->raster);
	}
}
}
