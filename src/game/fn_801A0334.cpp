// Search-path callback that tries the extensions of every registered image format on a
// candidate file name (HYPOTHESIS: RenderWare image path search): appends each format's
// lower-case, then upper-case extension and stops at the first file that exists, returning 0
// and storing the matching extension. Returns the name when no extension matches.
#include "game/rw_engine.h"

// Registered image format (HYPOTHESIS: _rwImageFormat); read and write callbacks are not used
// here.
struct RwImageFormat801A0334 {
	char lowerExtension[0x14];   // 0x0
	char upperExtension[0x14];   // 0x14
	u8 pad28[0x8];               // 0x28
	RwImageFormat801A0334* next; // 0x30
};

// Head of the image format list in the image module globals.
#define RW_IMAGE_FORMATS                                                                           \
	(*(RwImageFormat801A0334**)((u8*)lbl_8042C9A4 + lbl_8042C9B0.globalsOffset + 0x21C))

extern "C" {
char* fn_801A0334(char* name, const char** extension)
{
	RwImageFormat801A0334* format;
	char* end;

	end    = name + lbl_8042C9A4->rwstrlen(name);
	format = RW_IMAGE_FORMATS;

	while (format) {
		lbl_8042C9A4->rwstrcpy(end, format->lowerExtension);
		if (lbl_8042C9A4->rwfexist(name)) {
			*extension = format->lowerExtension;
			return 0;
		}
		lbl_8042C9A4->rwstrcpy(end, format->upperExtension);
		if (lbl_8042C9A4->rwfexist(name)) {
			*extension = format->upperExtension;
			return 0;
		}
		format = format->next;
	}
	return name;
}
}
