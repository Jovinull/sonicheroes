// Skips the rest of the current chunk and checks its CRC (HYPOTHESIS: libpng png_crc_finish, with
// png_crc_read inlined): reads `skip` bytes through the zlib buffer in buffer-sized pieces,
// feeding them to the running CRC, then on a CRC mismatch (fn_801860C8) warns about an ancillary
// chunk without the no-warning flag 0x200 or a critical chunk with the use flag 0x400
// (fn_8017C80C) and raises a chunk error otherwise (fn_8017C6D4), both with the message at
// lbl_8028F2F8 ("CRC error" in libpng). Returns 1 on a mismatch, otherwise 0.
#include "types.h"

// Fields used here (HYPOTHESIS: png_struct layout).
struct PngStruct80185FC0 {
	u8 pad0[0x2C];
	u32 flags; // 0x2C
	u8 pad30[0x6C - 0x30];
	u8* zbuf;     // 0x6C
	u32 zbufSize; // 0x70
	u8 pad74[0xDC - 0x74];
	u8 chunkName[5]; // 0xDC
};

#define PNG_FLAG_CRC_ANCILLARY_NOWARN 0x200
#define PNG_FLAG_CRC_CRITICAL_USE     0x400

extern "C" {
extern char lbl_8028F2F8[];

// HYPOTHESIS: png_read_data, png_calculate_crc, png_crc_error, png_chunk_error and
// png_chunk_warning.
void fn_8017E708(PngStruct80185FC0* png, u8* data, u32 length);
void fn_8017BF08(PngStruct80185FC0* png, u8* data, u32 length);
s32 fn_801860C8(PngStruct80185FC0* png);
void fn_8017C6D4(PngStruct80185FC0* png, const char* message);
void fn_8017C80C(PngStruct80185FC0* png, const char* message);
}

static inline void PngCrcRead(PngStruct80185FC0* png, u8* buffer, u32 length)
{
	fn_8017E708(png, buffer, length);
	fn_8017BF08(png, buffer, length);
}

extern "C" {
s32 fn_80185FC0(PngStruct80185FC0* png, u32 skip)
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
