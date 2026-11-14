// Sets the chromaticities of an info structure (HYPOTHESIS: libpng png_set_cHRM): stores the
// white point and the red, green and blue primaries both as floats and as fixed-point values
// (100000 * value + 0.5 with the .sdata2 doubles lbl_8042F600 and lbl_8042F5F8) and flags the
// chunk as valid (0x4). Nothing is done for a null structure.
#include "types.h"

// Fields used here (HYPOTHESIS: png_info layout).
struct PngInfo8018FD08 {
	u8 pad0[0x8];
	u32 valid; // 0x8
	u8 padC[0x80 - 0xC];
	f32 xWhite; // 0x80
	f32 yWhite; // 0x84
	f32 xRed;   // 0x88
	f32 yRed;   // 0x8C
	f32 xGreen; // 0x90
	f32 yGreen; // 0x94
	f32 xBlue;  // 0x98
	f32 yBlue;  // 0x9C
	u8 padA0[0x100 - 0xA0];
	s32 intXWhite; // 0x100
	s32 intYWhite; // 0x104
	s32 intXRed;   // 0x108
	s32 intYRed;   // 0x10C
	s32 intXGreen; // 0x110
	s32 intYGreen; // 0x114
	s32 intXBlue;  // 0x118
	s32 intYBlue;  // 0x11C
};

#define PNG_INFO_cHRM 0x4

extern "C" {
extern f64 lbl_8042F600;
extern f64 lbl_8042F5F8;

void fn_8018FD08(void* png, PngInfo8018FD08* info, f64 whiteX, f64 whiteY, f64 redX, f64 redY,
    f64 greenX, f64 greenY, f64 blueX, f64 blueY)
{
	if (png == 0 || info == 0) {
		return;
	}
	info->xWhite    = (f32)whiteX;
	info->yWhite    = (f32)whiteY;
	info->xRed      = (f32)redX;
	info->yRed      = (f32)redY;
	info->xGreen    = (f32)greenX;
	info->yGreen    = (f32)greenY;
	info->xBlue     = (f32)blueX;
	info->yBlue     = (f32)blueY;
	info->intXWhite = (s32)(f32)(lbl_8042F600 * whiteX + lbl_8042F5F8);
	info->intYWhite = (s32)(f32)(lbl_8042F600 * whiteY + lbl_8042F5F8);
	info->intXRed   = (s32)(f32)(lbl_8042F600 * redX + lbl_8042F5F8);
	info->intYRed   = (s32)(f32)(lbl_8042F600 * redY + lbl_8042F5F8);
	info->intXGreen = (s32)(f32)(lbl_8042F600 * greenX + lbl_8042F5F8);
	info->intYGreen = (s32)(f32)(lbl_8042F600 * greenY + lbl_8042F5F8);
	info->intXBlue  = (s32)(f32)(lbl_8042F600 * blueX + lbl_8042F5F8);
	info->intYBlue  = (s32)(f32)(lbl_8042F600 * blueY + lbl_8042F5F8);
	info->valid |= PNG_INFO_cHRM;
}
}
