// Updates the running CRC of the current chunk with length bytes at data unless the error flags say
// it is ignored (HYPOTHESIS: libpng png_calculate_crc): ancillary chunks (chunk name bit 5) skip it
// when both ancillary CRC flags (0x300) are set, critical chunks when flag 0x800 is set.
#include "types.h"

// Fields used here (HYPOTHESIS: png_struct layout).
struct Png8017BF08 {
	unsigned char pad0[0x2C];
	unsigned int flags; // 0x2C
	unsigned char pad30[0xD0 - 0x30];
	unsigned int crc; // 0xD0
	unsigned char padD4[0xDC - 0xD4];
	unsigned char chunkName[4]; // 0xDC
};

extern "C" {
// HYPOTHESIS: zlib crc32.
unsigned int fn_8017BC74(unsigned int crc, const unsigned char* data, unsigned int length);

void fn_8017BF08(Png8017BF08* png, const unsigned char* data, unsigned int length)
{
	int needCrc = 1;
	if (png->chunkName[0] & 0x20) {
		if ((png->flags & 0x300) == 0x300) {
			needCrc = 0;
		}
	} else if (png->flags & 0x800) {
		needCrc = 0;
	}
	if (needCrc) {
		png->crc = fn_8017BC74(png->crc, data, length);
	}
}
}
