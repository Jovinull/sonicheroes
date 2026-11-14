// Strips 16-bit samples of a row to 8 bits by keeping each sample's high byte, then updates the
// row information (HYPOTHESIS: libpng png_do_strip_16); rows of other depths are left unchanged.
#include "types.h"

// Fields used here (HYPOTHESIS: png_row_info layout).
struct PngRowInfo8018052C {
	u32 width;     // 0x0
	u32 rowbytes;  // 0x4
	u8 colorType;  // 0x8
	u8 bitDepth;   // 0x9
	u8 channels;   // 0xA
	u8 pixelDepth; // 0xB
};

extern "C" {
void fn_8018052C(PngRowInfo8018052C* rowInfo, u8* row)
{
	if (rowInfo->bitDepth == 16) {
		u8* sp = row;
		u8* dp = row;
		u32 i;
		u32 istop = rowInfo->width * rowInfo->channels;

		for (i = 0; i < istop; i++, sp += 2, dp++) {
			*dp = *sp;
		}
		rowInfo->bitDepth   = 8;
		rowInfo->pixelDepth = (u8)(8 * rowInfo->channels);
		rowInfo->rowbytes   = rowInfo->width * rowInfo->channels;
	}
}
}
