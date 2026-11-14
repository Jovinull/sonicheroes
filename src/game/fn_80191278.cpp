// Swaps the byte order of every 16-bit sample of a row (HYPOTHESIS: libpng png_do_swap); rows of
// other bit depths are left unchanged.
#include "types.h"

// Fields used here (HYPOTHESIS: png_row_info layout).
struct PngRowInfo80191278 {
	unsigned int width;      // 0x0
	unsigned int rowbytes;   // 0x4
	unsigned char colorType; // 0x8
	unsigned char bitDepth;  // 0x9
	unsigned char channels;  // 0xA
};

extern "C" {
void fn_80191278(PngRowInfo80191278* rowInfo, unsigned char* row)
{
	if (rowInfo->bitDepth == 16) {
		unsigned char* bp  = row;
		unsigned int istop = rowInfo->width * rowInfo->channels;
		unsigned int i;
		for (i = 0; i < istop; i++, bp += 2) {
			unsigned char t = *bp;
			*bp             = *(bp + 1);
			*(bp + 1)       = t;
		}
	}
}
}
