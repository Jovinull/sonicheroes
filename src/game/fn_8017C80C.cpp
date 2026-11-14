// Issues a warning about the current chunk (HYPOTHESIS: libpng png_chunk_warning): formats the chunk
// name (non-letters as "[hex]") followed by ": " and up to 63 characters of the message, then issues
// it as png_warning (fn_8017C5FC) does, skipping an optional "#nnnn " prefix and passing it to the
// user warning handler at +0x4 or to fn_8017CA08 (png_default_warning). png_format_buffer and
// png_warning are inlined here.
#include "types.h"
#include "MSL_C/string.h"

struct Png8017C80C {
	void (*errorFn)(Png8017C80C* png, const char* message);   // 0x0
	void (*warningFn)(Png8017C80C* png, const char* message); // 0x4
	unsigned char pad8[0xDC - 0x8];
	unsigned char chunkName[4]; // 0xDC
};

#define PNG_IS_NON_ALPHA(c) ((c) < 41 || (c) > 122 || ((c) > 90 && (c) < 97))

extern "C" {
// Hexadecimal digits "0123456789ABCDEF" (HYPOTHESIS: png_digit, .rodata of the original unit).
extern const char lbl_8023C8B8[16];
void fn_8017CA08(Png8017C80C* png, const char* message);
}

// HYPOTHESIS: png_format_buffer.
static inline void PngFormatBuffer(Png8017C80C* png, char* buffer, const char* message)
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
void fn_8017C80C(Png8017C80C* png, const char* message)
{
	char msg[18 + 64];
	int offset;
	PngFormatBuffer(png, msg, message);
	offset = 0;
	if (*msg == '#') {
		for (offset = 1; offset < 15; offset++) {
			if (*(msg + offset) == ' ') {
				break;
			}
		}
	}
	if (png->warningFn != 0) {
		png->warningFn(png, msg + offset);
	} else {
		fn_8017CA08(png, msg + offset);
	}
}
}
