#ifndef GAME_PNG_INTERNAL_H
#define GAME_PNG_INTERNAL_H

#include "types.h"

// Pieces of the libpng copy linked into the game (HYPOTHESIS: libpng 1.0/1.2 built with the
// RenderWare code). Only the png_struct fields used by the reconstructed units are listed.
// Names follow libpng 1.2's png_struct, matched by the order png_read_destroy (fn_8017E4B4) frees
// and saves them (CORROBORATED).
struct PngStruct {
	void* errorFn;   // 0x0: error_fn (no jmpbuf: setjmp support is off)
	void* warningFn; // 0x4: warning_fn
	void* errorPtr;  // 0x8: error_ptr
	u8 padC[0x28 - 0xC];
	u32 mode;  // 0x28
	u32 flags; // 0x2C
	u8 pad30[0x34 - 0x30];
	u8 zstream[0x38]; // 0x34: z_stream
	u8* zbuf;         // 0x6C
	u32 zbufSize;     // 0x70
	u8 pad74[0xA8 - 0x74];
	u8* prevRow;   // 0xA8: prev_row
	u8* bigRowBuf; // 0xAC: big_row_buf
	u8 padB0[0xD0 - 0xB0];
	u32 crc;       // 0xD0
	void* palette; // 0xD4
	u8 padD8[0xDC - 0xD8];
	u8 chunkName[5]; // 0xDC
	u8 padE1[0x118 - 0xE1];
	s32 gammaShift; // 0x118: gamma_shift
	u8 pad11C[0x124 - 0x11C];
	u8* gammaTable;     // 0x124
	u8* gammaFrom1;     // 0x128
	u8* gammaTo1;       // 0x12C
	u16** gamma16Table; // 0x130
	u16** gamma16From1; // 0x134
	u16** gamma16To1;   // 0x138
	u8 pad13C[0x148 - 0x13C];
	u8* trans; // 0x148
	u8 pad14C[0x160 - 0x14C];
	u8* paletteLookup; // 0x160: palette_lookup
	u8* ditherIndex;   // 0x164: dither_index
	u16* hist;         // 0x168
	u8 pad16C[0x184 - 0x16C];
	u32 freeMe; // 0x184: free_me
	u8 pad188[0x1B0 - 0x188];
	void* freeFn; // 0x1B0: free_fn
};

#define PNG_STRUCT_SIZE 0x1B4

#define PNG_FREE_HIST 0x8
#define PNG_FREE_PLTE 0x1000
#define PNG_FREE_TRNS 0x2000

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
