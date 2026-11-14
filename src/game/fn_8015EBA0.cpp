// Sets the material colour of channel GX_COLOR0A0 to material and the ambient colour of channel
// GX_COLOR0 to ambient scaled by intensity and the factor lbl_8042F3F0 (each component truncated to
// a byte, alpha 0).
extern "C" {
#include "dolphin/gx.h"
}
#include "game/rw_engine.h"

extern "C" {
// .sdata2 colour scale (non-const: see RW_MATRIX_SET_IDENTITY).
extern f32 lbl_8042F3F0;

void fn_8015EBA0(const RwV3d* ambient, const GXColor* material, f32 intensity)
{
	GXColor amb;
	f32 scale = lbl_8042F3F0 * intensity;
	amb.r     = (u8)(ambient->x * scale);
	amb.g     = (u8)(ambient->y * scale);
	amb.b     = (u8)(ambient->z * scale);
	amb.a     = 0;
	GXSetChanMatColor(GX_COLOR0A0, *material);
	GXSetChanAmbColor(GX_COLOR0, amb);
}
}
