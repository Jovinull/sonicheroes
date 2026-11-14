// Reports the level-of-detail settings of a raster's GameCube texture object, stored in the raster
// plugin data at the offset lbl_8042CA60: LOD bias, bias clamp, edge LOD and maximum anisotropy.
// When bit 24 of the plugin word at +0x20 is set, fixed defaults are reported instead (bias
// lbl_8042F808, clamp and edge LOD on, GX_ANISO_1). Plugin and flag names are UNKNOWN.
extern "C" {
#include "dolphin/gx.h"
}
#include "game/rw_engine.h"

extern "C" {
// Offset of the GameCube raster extension inside RwRaster (UNKNOWN plugin name).
extern s32 lbl_8042CA60;
// .sdata2 constant: default LOD bias (non-const: see RW_MATRIX_SET_IDENTITY).
extern f32 lbl_8042F808;

void fn_801B27EC(RwRaster* raster, f32* lodBias, s32* biasClamp, s32* edgeLod, s32* maxAniso)
{
	GXTexObj* texObj = (GXTexObj*)((u8*)raster + lbl_8042CA60);
	if (*(u32*)((u8*)texObj + 0x20) & 0x01000000) {
		*lodBias   = lbl_8042F808;
		*biasClamp = 1;
		*edgeLod   = 1;
		*maxAniso  = GX_ANISO_1;
	} else {
		*lodBias   = GXGetTexObjLODBias(texObj);
		*biasClamp = GXGetTexObjBiasClamp(texObj);
		*edgeLod   = GXGetTexObjEdgeLOD(texObj);
		*maxAniso  = GXGetTexObjMaxAniso(texObj);
	}
}
}
