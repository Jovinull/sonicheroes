// Handles a PNG zTXt chunk (HYPOTHESIS: libpng 1.0 png_handle_zTXt): requires IHDR, marks the
// image as past IDAT when IDAT was seen, reads the chunk into a NUL-terminated buffer and checks
// its CRC (dropping the chunk on a bad CRC), then finds the end of the keyword: a chunk with no
// compression byte warns and is stored uncompressed, an unknown compression method warns and is
// treated as deflate. Decompresses the text after the keyword (fn_8018618C) and stores it as one
// text entry with png_set_text (fn_80190B5C), then frees the buffers. Messages come from the
// chunk reader's pool lbl_8028F2F8 ("Missing IHDR before zTXt" at 0xAE8, "Zero length zTXt chunk"
// at 0xB04, "Unknown compression type in zTXt chunk" at 0xB1C).
// NonMatching: retail builds the pool base straight into a saved register (lis/addi r31), while
// this source's local goes through a scratch register and a move, which shifts the allocation
// (two instructions, 178 words), the same gap as fn_80186E14. Direct pool offsets lose the shared
// base; C mode, compilers GC/1.1 to 2.0 and permuted declarations do not help.
#include "game/png_internal.h"

#define PNG_TEXT_COMPRESSION_NONE (-1)
#define PNG_TEXT_COMPRESSION_ZTXT 0

// Text entry (HYPOTHESIS: png_text without iTXt fields).
struct PngText8018E038 {
	s32 compression; // 0x0
	char* key;       // 0x4
	char* text;      // 0x8
	u32 textLength;  // 0xC
};

extern "C" {
// HYPOTHESIS: png_malloc, png_free, png_decompress_chunk and png_set_text.
void* fn_8017CDA4(PngStruct* png, u32 size);
void fn_8017CE74(PngStruct* png, void* ptr);
char* fn_8018618C(
    PngStruct* png, s32 compType, char* chunkData, u32 length, u32 prefixLength, u32* newLength);
void fn_80190B5C(PngStruct* png, void* info, PngText8018E038* text, s32 numText);

void fn_8018E038(PngStruct* png, void* info, u32 length)
{
	PngText8018E038* textEntry;
	char* chunkData;
	char* text;
	s32 compType;
	u32 prefixLength;
	u32 dataLength;
	const char* messages;

	messages = lbl_8028F2F8;

	if (!(png->mode & PNG_HAVE_IHDR)) {
		fn_8017C5A8(png, messages + 0xAE8);
	}
	if (png->mode & PNG_HAVE_IDAT) {
		png->mode |= PNG_AFTER_IDAT;
	}

	chunkData = (char*)fn_8017CDA4(png, length + 1);
	PngCrcRead(png, (u8*)chunkData, length);
	if (PngCrcFinish(png, 0, messages)) {
		fn_8017CE74(png, chunkData);
		return;
	}

	chunkData[length] = 0;
	for (text = chunkData; *text; text++) {
	}
	if (text == chunkData + length) {
		compType = PNG_TEXT_COMPRESSION_NONE;
		fn_8017C5FC(png, messages + 0xB04);
	} else {
		compType = *(++text);
		if (compType != PNG_TEXT_COMPRESSION_ZTXT) {
			fn_8017C5FC(png, messages + 0xB1C);
			compType = PNG_TEXT_COMPRESSION_ZTXT;
		}
		text++;
	}
	prefixLength = text - chunkData;
	chunkData    = fn_8018618C(png, compType, chunkData, length, prefixLength, &dataLength);

	textEntry              = (PngText8018E038*)fn_8017CDA4(png, sizeof(PngText8018E038));
	textEntry->compression = compType;
	textEntry->key         = chunkData;
	textEntry->text        = chunkData + prefixLength;
	textEntry->textLength  = dataLength;
	fn_80190B5C(png, info, textEntry, 1);
	fn_8017CE74(png, textEntry);
	fn_8017CE74(png, chunkData);
}
}
