// Prepares the additive glow pass of effect texture `index` (0-6, lbl_80253938): binds its raster
// (render state 1), clears two words of lbl_803EDBD0, sets the GX blend mode (3, 4, 1, 0) and
// render state 0x14 to 1, and converts the colour lbl_80253A64 (0-1 floats, scaled by 255 and the
// global factor lbl_8042DD68) into the bytes of lbl_8042C3C4, clamping values above 256 (as 16-bit)
// to 255. HYPOTHESIS: the field roles are UNKNOWN.
#include "types.h"

struct Glow800B7864 {
	void* raster; // 0x0
};

struct Colour800B7864 {
	f32 red;
	f32 green;
	f32 blue;
};

struct State800B7864 {
	u8 pad0[0x34];
	s32 unknown34; // 0x34
	s32 unknown38; // 0x38
};

extern "C" {
extern Glow800B7864* lbl_80253938[7];
extern State800B7864 lbl_803EDBD0;
extern const Colour800B7864 lbl_80253A64;
extern f32 lbl_8042DD58; // 255.0f
extern f32 lbl_8042DD68; // 2.0f in the retail data
extern u8 lbl_8042C3C4[3];
void fn_80194234(s32 state, void* value);
void GXSetBlendMode(s32 type, s32 src, s32 dst, s32 op);

void fn_800B7864(s32 index)
{
	Glow800B7864* glow;
	s32 red;
	s32 green;
	s32 blue;

	if (index < 0 || index >= 7) {
		return;
	}
	glow = lbl_80253938[index];
	if (glow != NULL) {
		fn_80194234(1, glow->raster);
		lbl_803EDBD0.unknown34 = 0;
		lbl_803EDBD0.unknown38 = 0;
		GXSetBlendMode(3, 4, 1, 0);
		fn_80194234(0x14, (void*)1);
		red   = (s32)(lbl_8042DD58 * (lbl_8042DD68 * lbl_80253A64.red));
		green = (s32)(lbl_8042DD58 * (lbl_8042DD68 * lbl_80253A64.green));
		blue  = (s32)(lbl_8042DD58 * (lbl_8042DD68 * lbl_80253A64.blue));
		if ((u16)red > 0x100) {
			red = 0xFF;
		}
		if ((u16)green > 0x100) {
			green = 0xFF;
		}
		if ((u16)blue > 0x100) {
			blue = 0xFF;
		}
		lbl_8042C3C4[2] = blue;
		lbl_8042C3C4[1] = green;
		lbl_8042C3C4[0] = red;
	}
}
}
