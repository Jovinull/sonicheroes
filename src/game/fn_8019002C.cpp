// Records the image gamma (HYPOTHESIS: libpng png_set_gAMA): stores it as a float (+0x28) and as a
// fixed-point value scaled by 100000 and rounded (+0xFC), marks gAMA as valid and warns through
// fn_8017C5FC (png_warning) with lbl_8028FF10 when the gamma is zero. The double constants are the
// .sdata2 pool entries of the original unit.
#include "types.h"

#define PNG_INFO_gAMA 0x1

// Fields used here (HYPOTHESIS: png_info layout).
struct PngInfo8019002C {
	unsigned char pad0[0x8];
	unsigned int valid; // 0x8
	unsigned char padC[0x28 - 0xC];
	float gamma; // 0x28
	unsigned char pad2C[0xFC - 0x2C];
	int intGamma; // 0xFC
};

extern "C" {
// .sdata2 constants 100000.0, 0.5 and 0.0 (non-const: loaded as ordinary globals).
extern double lbl_8042F600;
extern double lbl_8042F5F8;
extern double lbl_8042F610;
extern char lbl_8028FF10[];
void fn_8017C5FC(void* png, const char* message);

void fn_8019002C(void* png, PngInfo8019002C* info, double fileGamma)
{
	if (png == 0 || info == 0) {
		return;
	}
	info->gamma = (float)fileGamma;
	// The retail code rounds the scaled value to single precision before the integer conversion.
	info->intGamma = (int)(float)(lbl_8042F600 * fileGamma + lbl_8042F5F8);
	info->valid |= PNG_INFO_gAMA;
	if (lbl_8042F610 == fileGamma) {
		fn_8017C5FC(png, lbl_8028FF10);
	}
}
}
