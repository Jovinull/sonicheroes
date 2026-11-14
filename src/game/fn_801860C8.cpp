// Reads the 4-byte CRC that ends the current chunk and reports whether it differs from the
// running CRC (HYPOTHESIS: libpng png_crc_error). The comparison is skipped (0 returned) for an
// ancillary chunk when the ancillary CRC flags are "use, no warning" (0x300), or for a critical
// chunk when the critical-ignore flag 0x800 is set.
#include "game/png_internal.h"

extern "C" {
s32 fn_801860C8(PngStruct* png)
{
	return PngCrcError(png);
}
}
