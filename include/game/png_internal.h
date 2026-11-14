#ifndef GAME_PNG_INTERNAL_H
#define GAME_PNG_INTERNAL_H

#include "types.h"

// Pieces of the libpng copy linked into the game (HYPOTHESIS: libpng 1.0/1.2 built with the
// RenderWare code). Only the png_struct fields used by the reconstructed units are listed.
struct PngStruct {
	u8 pad0[0x28];
	u32 mode;  // 0x28
	u32 flags; // 0x2C
	u8 pad30[0x6C - 0x30];
	u8* zbuf;     // 0x6C
	u32 zbufSize; // 0x70
	u8 pad74[0xD0 - 0x74];
	u32 crc; // 0xD0
	u8 padD4[0xDC - 0xD4];
	u8 chunkName[5]; // 0xDC
};

#define PNG_HAVE_IHDR  0x1
#define PNG_HAVE_IDAT  0x4
#define PNG_AFTER_IDAT 0x8
#define PNG_HAVE_IEND  0x10

#define PNG_FLAG_CRC_ANCILLARY_NOWARN 0x200
#define PNG_FLAG_CRC_ANCILLARY_MASK   0x300
#define PNG_FLAG_CRC_CRITICAL_USE     0x400
#define PNG_FLAG_CRC_CRITICAL_IGNORE  0x800

extern "C" {
// Message pool of the chunk reader ("CRC error" at offset 0 in libpng).
extern char lbl_8028F2F8[];

// HYPOTHESIS: png_read_data, png_calculate_crc, png_error, png_warning, png_chunk_error and
// png_chunk_warning.
void fn_8017E708(PngStruct* png, u8* data, u32 length);
void fn_8017BF08(PngStruct* png, u8* data, u32 length);
void fn_8017C5A8(PngStruct* png, const char* message);
void fn_8017C5FC(PngStruct* png, const char* message);
void fn_8017C6D4(PngStruct* png, const char* message);
void fn_8017C80C(PngStruct* png, const char* message);
}

// png_crc_read: reads data and feeds it to the running CRC.
static inline void PngCrcRead(PngStruct* png, u8* buffer, u32 length)
{
	fn_8017E708(png, buffer, length);
	fn_8017BF08(png, buffer, length);
}

// png_crc_error: reads the chunk CRC and reports whether it differs from the running one.
static inline s32 PngCrcError(PngStruct* png)
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

// png_crc_finish: skips the rest of the chunk and checks its CRC; crcMessage is the "CRC error"
// string (lbl_8028F2F8; units that keep the pool base in a register pass that copy).
static inline s32 PngCrcFinish(PngStruct* png, u32 skip, const char* crcMessage)
{
	u32 i;
	u32 istop = png->zbufSize;

	for (i = skip; i > istop; i -= istop) {
		PngCrcRead(png, png->zbuf, png->zbufSize);
	}
	if (i) {
		PngCrcRead(png, png->zbuf, i);
	}

	if (PngCrcError(png)) {
		if (((png->chunkName[0] & 0x20) && !(png->flags & PNG_FLAG_CRC_ANCILLARY_NOWARN))
		    || (!(png->chunkName[0] & 0x20) && (png->flags & PNG_FLAG_CRC_CRITICAL_USE))) {
			fn_8017C80C(png, crcMessage);
		} else {
			fn_8017C6D4(png, crcMessage);
		}
		return 1;
	}
	return 0;
}

#endif
