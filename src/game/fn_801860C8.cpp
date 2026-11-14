// Reads the 4-byte CRC that ends the current chunk and reports whether it differs from the
// running CRC (HYPOTHESIS: libpng png_crc_error). The comparison is skipped (0 returned) for an
// ancillary chunk when the ancillary CRC flags are "use, no warning" (0x300), or for a critical
// chunk when the critical-ignore flag 0x800 is set.
#include "types.h"

// Fields used here (HYPOTHESIS: png_struct layout).
struct PngStruct801860C8 {
	u8 pad0[0x2C];
	u32 flags; // 0x2C
	u8 pad30[0xD0 - 0x30];
	u32 crc; // 0xD0
	u8 padD4[0xDC - 0xD4];
	u8 chunkName[5]; // 0xDC
};

#define PNG_FLAG_CRC_ANCILLARY_MASK  0x300
#define PNG_FLAG_CRC_CRITICAL_IGNORE 0x800

extern "C" {
// HYPOTHESIS: png_read_data.
void fn_8017E708(PngStruct801860C8* png, u8* data, u32 length);

s32 fn_801860C8(PngStruct801860C8* png)
{
	u8 crcBytes[4];
	u32 crc;
	s32 needCrc = 1;

	if (png->chunkName[0] & 0x20) {
		if ((png->flags & PNG_FLAG_CRC_ANCILLARY_MASK) == PNG_FLAG_CRC_ANCILLARY_MASK) {
			needCrc = 0;
		}
	} else if (png->flags & PNG_FLAG_CRC_CRITICAL_IGNORE) {
		needCrc = 0;
	}

	fn_8017E708(png, crcBytes, 4);
	if (needCrc) {
		crc = ((u32)crcBytes[0] << 24) + ((u32)crcBytes[1] << 16) + ((u32)crcBytes[2] << 8)
		    + (u32)crcBytes[3];
		return (s32)(crc != png->crc);
	}
	return 0;
}
}
