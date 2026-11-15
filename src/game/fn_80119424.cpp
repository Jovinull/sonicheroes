// Draws a debug line between two points of an object (HYPOTHESIS; names inferred): saves the
// source and destination blend and z-test render states (10, 11, 20), sets them to 5, 2 and 1,
// sends the points at 0xC0 and 0xB4 in the colour lbl_8042EA58 through the 3D immediate mode
// (fn_801B2934, flag 0x10) and draws them as a line (fn_801B2C00, fn_801B2A14), then restores the
// three states.
#include "game/matrix.h"

#define RW_RENDERSTATE_SRCBLEND  10
#define RW_RENDERSTATE_DESTBLEND 11
#define RW_RENDERSTATE_ZTEST     20

struct Im3DVertex80119424 {
	RwV3d pos;    // 0x0
	RwV3d normal; // 0xC
	u8 red;       // 0x18
	u8 green;     // 0x19
	u8 blue;      // 0x1A
	u8 alpha;     // 0x1B
	f32 u;        // 0x1C
	f32 v;        // 0x20

	void SetPos(const RwV3d& p)
	{
		f32 z, y;
		y     = p.y;
		z     = p.z;
		pos.x = p.x;
		pos.y = y;
		pos.z = z;
	}
};

struct Color80119424 {
	u8 red, green, blue, alpha;
};

struct Line80119424 {
	u8 pad0[0xB4];
	RwV3d end;   // 0xB4
	RwV3d start; // 0xC0
};

extern "C" {
extern Color80119424 lbl_8042EA58;
// HYPOTHESIS: RwRenderStateGet/Set, RwIm3DTransform, RwIm3DRenderPrimitive and RwIm3DEnd.
s32 fn_80194294(s32 state, void* value);
s32 fn_80194234(s32 state, void* value);
void* fn_801B2934(Im3DVertex80119424* vertices, u32 numVertices, RwMatrixTag* ltm, u32 flags);
s32 fn_801B2C00(s32 primType);
s32 fn_801B2A14(void);

void fn_80119424(Line80119424* line)
{
	Im3DVertex80119424 vertices[2];
	void* srcBlend;
	void* destBlend;
	void* zTest;

	fn_80194294(RW_RENDERSTATE_SRCBLEND, &srcBlend);
	fn_80194294(RW_RENDERSTATE_DESTBLEND, &destBlend);
	fn_80194294(RW_RENDERSTATE_ZTEST, &zTest);
	fn_80194234(RW_RENDERSTATE_SRCBLEND, (void*)5);
	fn_80194234(RW_RENDERSTATE_DESTBLEND, (void*)2);
	fn_80194234(RW_RENDERSTATE_ZTEST, (void*)1);

	vertices[0].SetPos(line->start);
	vertices[1].SetPos(line->end);
	vertices[0].red   = lbl_8042EA58.red;
	vertices[0].green = lbl_8042EA58.green;
	vertices[0].blue  = lbl_8042EA58.blue;
	vertices[0].alpha = lbl_8042EA58.alpha;
	vertices[1].red   = vertices[0].red;
	vertices[1].green = vertices[0].green;
	vertices[1].blue  = vertices[0].blue;
	vertices[1].alpha = vertices[0].alpha;
	if (fn_801B2934(vertices, 2, 0, 0x10) != 0) {
		fn_801B2C00(1);
		fn_801B2A14();
	}

	fn_80194234(RW_RENDERSTATE_ZTEST, zTest);
	fn_80194234(RW_RENDERSTATE_SRCBLEND, srcBlend);
	fn_80194234(RW_RENDERSTATE_DESTBLEND, destBlend);
}
}
