// Sets the ambient colour of channel GX_COLOR0 to a colour scaled by intensity and the factor
// lbl_8042F3F0 (each component truncated to a byte, alpha 0).
extern "C" {
#include "dolphin/gx.h"
}
#include "game/rw_engine.h"

extern "C" {
// .sdata2 colour scale (non-const: see RW_MATRIX_SET_IDENTITY).
extern f32 lbl_8042F3F0;

void fn_8015EB18(const RwV3d* colour, f32 intensity)
{
	GXColor scaled;
	f32 scale = lbl_8042F3F0 * intensity;
	scaled.r  = (u8)(colour->x * scale);
	scaled.g  = (u8)(colour->y * scale);
	scaled.b  = (u8)(colour->z * scale);
	scaled.a  = 0;
	GXSetChanAmbColor(GX_COLOR0, scaled);
}
}
