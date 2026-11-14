// Reports an error about the current chunk (HYPOTHESIS: libpng png_chunk_error): formats the chunk
// name (non-letters as "[hex]") followed by ": " and up to 63 characters of the message, then raises
// it as png_error does: the user error handler at +0x0 when installed, then fn_8017C9E8
// (png_default_error). png_format_buffer and png_error are inlined here.
#include "types.h"
#include "MSL_C/string.h"

struct Png8017C6D4 {
	void (*errorFn)(Png8017C6D4* png, const char* message); // 0x0
	unsigned char pad4[0xDC - 0x4];
	unsigned char chunkName[4]; // 0xDC
};

#define PNG_IS_NON_ALPHA(c) ((c) < 41 || (c) > 122 || ((c) > 90 && (c) < 97))

extern "C" {
// Hexadecimal digits "0123456789ABCDEF" (HYPOTHESIS: png_digit, .rodata of the original unit).
extern const char lbl_8023C8B8[16];
void fn_8017C9E8(Png8017C6D4* png, const char* message);
}

// HYPOTHESIS: png_format_buffer.
static inline void PngFormatBuffer(Png8017C6D4* png, char* buffer, const char* message)
{
	int iout = 0;
	int iin  = 0;
	while (iin < 4) {
		int c = png->chunkName[iin++];
		if (PNG_IS_NON_ALPHA(c)) {
			buffer[iout++] = '[';
			buffer[iout++] = lbl_8023C8B8[(c & 0xF0) >> 4];
			buffer[iout++] = lbl_8023C8B8[c & 0x0F];
			buffer[iout++] = ']';
		} else {
			buffer[iout++] = (char)c;
		}
	}
	if (message == 0) {
		buffer[iout] = 0;
	} else {
		buffer[iout++] = ':';
		buffer[iout++] = ' ';
		memcpy(buffer + iout, message, 64);
		buffer[iout + 63] = 0;
	}
}

extern "C" {
void fn_8017C6D4(Png8017C6D4* png, const char* message)
{
	char msg[18 + 64];
	PngFormatBuffer(png, msg, message);
	if (png->errorFn != 0) {
		png->errorFn(png, msg);
	}
	fn_8017C9E8(png, msg);
}
}
