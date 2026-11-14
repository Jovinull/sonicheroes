// Loads TEV colour register 1 with a colour scaled by intensity and the factor lbl_8042F3F0 (each
// component truncated to a byte, alpha 0).
extern "C" {
#include "dolphin/gx.h"
}
#include "game/rw_engine.h"

extern "C" {
// .sdata2 colour scale (non-const: see RW_MATRIX_SET_IDENTITY).
extern f32 lbl_8042F3F0;

void fn_8015EA90(const RwV3d* colour, f32 intensity)
{
	GXColor tev;
	f32 scale = lbl_8042F3F0 * intensity;
	tev.r     = (u8)(colour->x * scale);
	tev.g     = (u8)(colour->y * scale);
	tev.b     = (u8)(colour->z * scale);
	tev.a     = 0;
	GXSetTevColor(GX_TEVREG1, tev);
}
}
