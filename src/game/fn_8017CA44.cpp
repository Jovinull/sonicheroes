// Reports the image header of info (HYPOTHESIS: libpng png_get_IHDR): width, height, bit depth and
// colour type, plus the optional compression, filter and interlace methods, and warns through
// fn_8017C5FC (png_warning) with lbl_8028EC70 when a row would overflow PNG_UINT_31_MAX bytes.
// Returns 1, or 0 when a required pointer is null.
#include "types.h"

#define PNG_COLOR_MASK_COLOR   2
#define PNG_COLOR_MASK_ALPHA   4
#define PNG_COLOR_TYPE_PALETTE 3
#define PNG_UINT_31_MAX        0x7FFFFFFF

// Fields used here (HYPOTHESIS: png_info layout).
struct PngInfo8017CA44 {
	unsigned int width;  // 0x0
	unsigned int height; // 0x4
	unsigned char pad8[0x18 - 0x8];
	unsigned char bitDepth;        // 0x18
	unsigned char colorType;       // 0x19
	unsigned char compressionType; // 0x1A
	unsigned char filterType;      // 0x1B
	unsigned char interlaceType;   // 0x1C
};

extern "C" {
extern char lbl_8028EC70[];
void fn_8017C5FC(void* png, const char* message);

int fn_8017CA44(void* png, PngInfo8017CA44* info, unsigned int* width, unsigned int* height,
    int* bitDepth, int* colorType, int* interlaceType, int* compressionType, int* filterType)
{
	if (png != 0 && info != 0 && width != 0 && height != 0 && bitDepth != 0 && colorType != 0) {
		int pixelDepth;
		int channels;
		unsigned int rowbytesPerPixel;
		*width     = info->width;
		*height    = info->height;
		*bitDepth  = info->bitDepth;
		*colorType = info->colorType;
		if (compressionType != 0) {
			*compressionType = info->compressionType;
		}
		if (filterType != 0) {
			*filterType = info->filterType;
		}
		if (interlaceType != 0) {
			*interlaceType = info->interlaceType;
		}
		if (*colorType == PNG_COLOR_TYPE_PALETTE) {
			channels = 1;
		} else if (*colorType & PNG_COLOR_MASK_COLOR) {
			channels = 3;
		} else {
			channels = 1;
		}
		if (*colorType & PNG_COLOR_MASK_ALPHA) {
			channels++;
		}
		pixelDepth       = *bitDepth * channels;
		rowbytesPerPixel = (pixelDepth + 7) >> 3;
		if (*width > PNG_UINT_31_MAX / rowbytesPerPixel) {
			fn_8017C5FC(png, lbl_8028EC70);
		}
		return 1;
	}
	return 0;
}
}
