// Inverts every byte of a 1-bit greyscale row (HYPOTHESIS: libpng png_do_invert); other rows are
// left unchanged.
#include "types.h"

// Fields used here (HYPOTHESIS: png_row_info layout).
struct PngRowInfo8019119C {
	unsigned int width;      // 0x0
	unsigned int rowbytes;   // 0x4
	unsigned char colorType; // 0x8
	unsigned char bitDepth;  // 0x9
};

extern "C" {
void fn_8019119C(PngRowInfo8019119C* rowInfo, unsigned char* row)
{
	if (rowInfo->bitDepth == 1 && rowInfo->colorType == 0) {
		unsigned char* rp = row;
		unsigned int i;
		unsigned int istop = rowInfo->rowbytes;
		for (i = 0; i < istop; i++) {
			*rp = (unsigned char)(~(*rp));
			rp++;
		}
	}
}
}
