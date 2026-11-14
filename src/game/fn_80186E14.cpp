// Handles the IEND chunk (HYPOTHESIS: libpng png_handle_IEND, with png_crc_finish inlined):
// raises "No image in file" (lbl_8028F2F8 + 0x1AC) unless IHDR and IDAT were seen, marks the
// stream as past IDAT and at IEND, warns about a non-empty chunk (lbl_8028F2F8 + 0x1C0) and skips
// it, checking its CRC.
// NonMatching: the retail code keeps the message pool base (one string pool per libpng source file)
// in r31; the local copy here costs one extra register move (116 vs 115 instructions).
#include "game/png_internal.h"

extern "C" {
void fn_80186E14(PngStruct* png, void* info, u32 length)
{
	const char* messages = lbl_8028F2F8;

	if (!(png->mode & PNG_HAVE_IHDR) || !(png->mode & PNG_HAVE_IDAT)) {
		fn_8017C5A8(png, messages + 0x1AC);
	}
	png->mode |= PNG_AFTER_IDAT | PNG_HAVE_IEND;
	if (length != 0) {
		fn_8017C5FC(png, messages + 0x1C0);
	}
	PngCrcFinish(png, length, messages);
}
}
