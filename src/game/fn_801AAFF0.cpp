// Derives the raster layout for an image (HYPOTHESIS: the GameCube driver's
// _rwGameCubeImageFindRasterFormat): records the raster type, then for normal, texture and camera
// texture rasters clamps the size to 1024 (rounded down to powers of two for mipmapped formats)
// and picks the pixel format from the image (fn_801AAEC4) plus the mipmap/auto-mipmap bits; Z
// buffer and camera rasters take the image size with format 0. Other types raise error 0x8000000D
// of plugin 1. Returns 1, or 0 for an invalid type.
// NonMatching: retail computes the type into the incoming flags register (r5) after copying the
// flags to r31; this source puts it in r3, which reorders the first stores (8 words differ).
// Switching on the masked expression, statement order, an unsigned type and compilers 1.3 to 2.6
// do not change it.
#include "game/rw_engine.h"

// Raster types (HYPOTHESIS: RwRasterType).
#define RW_RASTER_TYPE_NORMAL         0
#define RW_RASTER_TYPE_ZBUFFER        1
#define RW_RASTER_TYPE_CAMERA         2
#define RW_RASTER_TYPE_TEXTURE        4
#define RW_RASTER_TYPE_CAMERA_TEXTURE 5
#define RW_RASTER_TYPE_MASK           0x7

#define RW_RASTER_FORMAT_AUTO_MIPMAP 0x1000
#define RW_RASTER_MAX_SIZE           1024
#define RW_ERROR_INVALID_RASTER_TYPE ((s32)0x8000000D)

extern "C" {
// Pixel format (in the "format << 8" encoding) for an image.
s32 fn_801AAEC4(const RwImage* image);

s32 fn_801AAFF0(RwRaster* raster, const RwImage* image, s32 flags)
{
	s32 type = flags & RW_RASTER_TYPE_MASK;

	raster->cType = type;
	raster->depth = 0;
	switch (type) {
		case RW_RASTER_TYPE_NORMAL:
		case RW_RASTER_TYPE_TEXTURE:
		case RW_RASTER_TYPE_CAMERA_TEXTURE:
			raster->width = (image->width > RW_RASTER_MAX_SIZE) ? RW_RASTER_MAX_SIZE : image->width;
			raster->height
			    = (image->height > RW_RASTER_MAX_SIZE) ? RW_RASTER_MAX_SIZE : image->height;
			if (flags & RW_RASTER_FORMAT_MIPMAP) {
				s32 size;
				s32 widthShift;
				s32 heightShift;

				size       = raster->width;
				widthShift = -1;
				while (size != 0) {
					size >>= 1;
					widthShift++;
				}
				raster->width = 1 << widthShift;

				size        = raster->height;
				heightShift = -1;
				while (size != 0) {
					size >>= 1;
					heightShift++;
				}
				raster->height = 1 << heightShift;
			}
			{
				s32 format = fn_801AAEC4(image);
				format |= flags & (RW_RASTER_FORMAT_MIPMAP | RW_RASTER_FORMAT_AUTO_MIPMAP);
				raster->cFormat = format >> 8;
			}
			return 1;
		case RW_RASTER_TYPE_ZBUFFER:
		case RW_RASTER_TYPE_CAMERA:
			raster->cFormat = 0;
			raster->width   = image->width;
			raster->height  = image->height;
			return 1;
		default: {
			RwError error;
			error.pluginID  = 1;
			error.errorCode = fn_8019408C(RW_ERROR_INVALID_RASTER_TYPE);
			fn_80193FE8(&error);
			return 0;
		}
	}
}
}
