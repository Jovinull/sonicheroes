// Handles a PNG tEXt chunk (HYPOTHESIS: libpng 1.2 png_handle_tEXt): requires IHDR ("Missing IHDR
// before tEXt", the first message of lbl_8028FDC4), marks the image as past IDAT when IDAT was
// seen, reads the chunk into a NUL-terminated buffer and checks its CRC (dropping the chunk on a
// bad CRC), splits it into keyword and text at the first NUL and stores it as one uncompressed
// text entry with png_set_text (fn_80190B5C), then frees the buffers.
#include "game/png_internal.h"
#include "MSL_C/string.h"

#define PNG_TEXT_COMPRESSION_NONE (-1)

// Text entry (HYPOTHESIS: png_text without iTXt fields).
struct PngText8018DD9C {
	s32 compression; // 0x0
	char* key;       // 0x4
	char* text;      // 0x8
	u32 textLength;  // 0xC
};

extern "C" {
// Message pool of this chunk handler ("Missing IHDR before tEXt" at offset 0).
extern char lbl_8028FDC4[];

// HYPOTHESIS: png_malloc, png_free and png_set_text.
void* fn_8017CDA4(PngStruct* png, u32 size);
void fn_8017CE74(PngStruct* png, void* ptr);
void fn_80190B5C(PngStruct* png, void* info, PngText8018DD9C* text, s32 numText);

void fn_8018DD9C(PngStruct* png, void* info, u32 length)
{
	PngText8018DD9C* textEntry;
	char* key;
	char* text;

	if (!(png->mode & PNG_HAVE_IHDR)) {
		fn_8017C5A8(png, lbl_8028FDC4);
	}
	if (png->mode & PNG_HAVE_IDAT) {
		png->mode |= PNG_AFTER_IDAT;
	}

	key = (char*)fn_8017CDA4(png, length + 1);
	PngCrcRead(png, (u8*)key, length);
	if (PngCrcFinish(png, 0, lbl_8028F2F8)) {
		fn_8017CE74(png, key);
		return;
	}

	key[length] = 0;
	for (text = key; *text; text++) {
	}
	if (text != key + length) {
		text++;
	}

	textEntry              = (PngText8018DD9C*)fn_8017CDA4(png, sizeof(PngText8018DD9C));
	textEntry->compression = PNG_TEXT_COMPRESSION_NONE;
	textEntry->key         = key;
	textEntry->text        = text;
	textEntry->textLength  = strlen(text);
	fn_80190B5C(png, info, textEntry, 1);
	fn_8017CE74(png, key);
	fn_8017CE74(png, textEntry);
}
}
