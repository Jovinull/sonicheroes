// Skips the rest of the current chunk and checks its CRC (HYPOTHESIS: libpng png_crc_finish, with
// png_crc_read inlined): reads `skip` bytes through the zlib buffer in buffer-sized pieces,
// feeding them to the running CRC, then on a CRC mismatch (fn_801860C8) warns about an ancillary
// chunk without the no-warning flag 0x200 or a critical chunk with the use flag 0x400
// (fn_8017C80C) and raises a chunk error otherwise (fn_8017C6D4), both with the message at
// lbl_8028F2F8 ("CRC error" in libpng). Returns 1 on a mismatch, otherwise 0.
#include "game/png_internal.h"

extern "C" {
// HYPOTHESIS: png_crc_error (called, not inlined, in this function).
s32 fn_801860C8(PngStruct* png);

s32 fn_80185FC0(PngStruct* png, u32 skip)
{
	u32 i;
	u32 istop = png->zbufSize;

	for (i = skip; i > istop; i -= istop) {
		PngCrcRead(png, png->zbuf, png->zbufSize);
	}
	if (i) {
		PngCrcRead(png, png->zbuf, i);
	}

	if (fn_801860C8(png)) {
		if (((png->chunkName[0] & 0x20) && !(png->flags & PNG_FLAG_CRC_ANCILLARY_NOWARN))
		    || (!(png->chunkName[0] & 0x20) && (png->flags & PNG_FLAG_CRC_CRITICAL_USE))) {
			fn_8017C80C(png, lbl_8028F2F8);
		} else {
			fn_8017C6D4(png, lbl_8028F2F8);
		}
		return 1;
	}
	return 0;
}
}
