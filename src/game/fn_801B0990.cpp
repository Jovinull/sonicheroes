// Renders a raster into the current raster (HYPOTHESIS: the GameCube driver's raster render
// standard function): builds the destination rectangle (position from rect, size from rect when
// flags is set, else the raster's own size), then accepts normal, texture and camera-texture
// sources on a camera raster (drawn by fn_801B03C8) and rejects other source types; any other
// pairing raises error 2 of plugin 1 with the message lbl_80291094. Returns 1, or 0 on error.
#include "game/rw_engine.h"

struct RwRect801B0990 {
	s32 x;
	s32 y;
	s32 w;
	s32 h;
};

#define RW_RASTER_TYPE_NORMAL            0
#define RW_RASTER_TYPE_ZBUFFER           1
#define RW_RASTER_TYPE_CAMERA            2
#define RW_RASTER_TYPE_TEXTURE           4
#define RW_RASTER_TYPE_CAMERA_TEXTURE    5
#define RW_ERROR_INVALID_RASTER_801B0990 2

extern "C" {
// Raster currently set as the render target.
extern RwRaster* lbl_8042CA58;
extern char lbl_80291094[];
void fn_801B03C8(RwRaster* raster, RwRect801B0990* rect);
}

static inline s32 RasterError801B0990(void)
{
	RwError error;
	error.pluginID  = 1;
	error.errorCode = fn_8019408C(RW_ERROR_INVALID_RASTER_801B0990, lbl_80291094);
	fn_80193FE8(&error);
	return 0;
}

extern "C" {
s32 fn_801B0990(RwRaster* raster, RwRect801B0990* rect, s32 flags)
{
	RwRect801B0990 area;

	area.x = rect->x;
	area.y = rect->y;
	if (flags != 0) {
		area.w = rect->w;
		area.h = rect->h;
	} else {
		area.w = raster->width;
		area.h = raster->height;
	}

	switch (lbl_8042CA58->cType) {
		case RW_RASTER_TYPE_NORMAL:
		case RW_RASTER_TYPE_TEXTURE:
		case RW_RASTER_TYPE_CAMERA_TEXTURE:
			switch (raster->cType) {
				case RW_RASTER_TYPE_NORMAL:
				case RW_RASTER_TYPE_ZBUFFER:
				case RW_RASTER_TYPE_CAMERA:
				case RW_RASTER_TYPE_TEXTURE:
				case RW_RASTER_TYPE_CAMERA_TEXTURE:
					return RasterError801B0990();
			}
			break;
		case RW_RASTER_TYPE_CAMERA:
			switch (raster->cType) {
				case RW_RASTER_TYPE_NORMAL:
				case RW_RASTER_TYPE_TEXTURE:
				case RW_RASTER_TYPE_CAMERA_TEXTURE:
					fn_801B03C8(raster, &area);
					break;
				case RW_RASTER_TYPE_ZBUFFER:
				case RW_RASTER_TYPE_CAMERA:
					return RasterError801B0990();
			}
			break;
		default:
			return RasterError801B0990();
	}
	return 1;
}
}
