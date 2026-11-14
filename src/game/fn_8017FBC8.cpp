// Expands a row of 1-, 2- or 4-bit samples to one byte per sample, working backwards in place,
// and updates the row information to 8-bit depth (HYPOTHESIS: libpng png_do_unpack); rows of 8
// bits or more are left unchanged.
#include "types.h"

// Fields used here (HYPOTHESIS: png_row_info layout).
struct PngRowInfo8017FBC8 {
	u32 width;     // 0x0
	u32 rowbytes;  // 0x4
	u8 colorType;  // 0x8
	u8 bitDepth;   // 0x9
	u8 channels;   // 0xA
	u8 pixelDepth; // 0xB
};

extern "C" {
void fn_8017FBC8(PngRowInfo8017FBC8* rowInfo, u8* row)
{
	if (rowInfo->bitDepth < 8) {
		u32 i;
		u32 rowWidth = rowInfo->width;

		switch (rowInfo->bitDepth) {
			case 1: {
				u8* sp    = row + ((rowWidth - 1) >> 3);
				u8* dp    = row + rowWidth - 1;
				u32 shift = 7 - (s32)((rowWidth + 7) & 0x07);
				for (i = 0; i < rowWidth; i++) {
					*dp = (u8)((*sp >> shift) & 0x01);
					if (shift == 7) {
						shift = 0;
						sp--;
					} else {
						shift++;
					}
					dp--;
				}
				break;
			}
			case 2: {
				u8* sp    = row + ((rowWidth - 1) >> 2);
				u8* dp    = row + rowWidth - 1;
				u32 shift = (s32)((3 - ((rowWidth + 3) & 0x03)) << 1);
				for (i = 0; i < rowWidth; i++) {
					*dp = (u8)((*sp >> shift) & 0x03);
					if (shift == 6) {
						shift = 0;
						sp--;
					} else {
						shift += 2;
					}
					dp--;
				}
				break;
			}
			case 4: {
				u8* sp    = row + ((rowWidth - 1) >> 1);
				u8* dp    = row + rowWidth - 1;
				u32 shift = (s32)((1 - ((rowWidth + 1) & 0x01)) << 2);
				for (i = 0; i < rowWidth; i++) {
					*dp = (u8)((*sp >> shift) & 0x0F);
					if (shift == 4) {
						shift = 0;
						sp--;
					} else {
						shift = 4;
					}
					dp--;
				}
				break;
			}
		}
		rowInfo->bitDepth   = 8;
		rowInfo->pixelDepth = (u8)(8 * rowInfo->channels);
		rowInfo->rowbytes   = rowWidth * rowInfo->channels;
	}
}
}
