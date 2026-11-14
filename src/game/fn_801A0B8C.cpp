// Converts a device pixel of the given raster format to a colour through the driver standard
// function (HYPOTHESIS: RwRGBASetFromPixel). Returns rgbOut.
#include "game/rw_engine.h"

extern "C" {
RwRGBA* fn_801A0B8C(RwRGBA* rgbOut, u32 pixel, s32 format)
{
	lbl_8042C9A4->stdFunc[rwSTANDARDPIXELTORGB](rgbOut, &pixel, format);
	return rgbOut;
}
}
