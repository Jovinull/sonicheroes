// Registers an image file format (HYPOTHESIS: RwImageRegisterImageFormat): builds the lower-case
// ".ext" key, finds the registered format with that extension or creates one from the format free
// list (both extension spellings stored, no read or write function, linked at the list head), then
// installs the given read and write functions when they are non-null. Returns 1, or 0 when a new
// format cannot be allocated.
// NonMatching: for the first two string calls retail sets up the arguments before loading the
// engine globals pointer, while this source loads it first (7 words). Declaration order and C mode
// do not change it.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

#define RW_IMAGE_EXTENSION_SIZE 0x14

// Registered image format (HYPOTHESIS: rwImageFormat; layout as in fn_801A01C0).
struct RwImageFormat801A0470 {
	char lcExtension[RW_IMAGE_EXTENSION_SIZE]; // 0x0
	char ucExtension[RW_IMAGE_EXTENSION_SIZE]; // 0x14
	void* imageRead;                           // 0x28
	void* imageWrite;                          // 0x2C
	RwImageFormat801A0470* nextFormat;         // 0x30
};

#define RW_IMAGE_FORMATS_801A0470                                                                  \
	(*(RwImageFormat801A0470**)((u8*)lbl_8042C9A4 + lbl_8042C9B0.globalsOffset + 0x21C))

extern "C" {
s32 fn_801A0470(const char* extension, void* imageRead, void* imageWrite)
{
	char key[RW_IMAGE_EXTENSION_SIZE];
	RwImageFormat801A0470* format;
	RwImageFormat801A0470* found;

	key[0] = '.';
	lbl_8042C9A4->rwstrncpy(&key[1], extension, RW_IMAGE_EXTENSION_SIZE - 2);
	key[RW_IMAGE_EXTENSION_SIZE - 1] = 0;
	lbl_8042C9A4->rwstrlwr(key);

	found  = 0;
	format = RW_IMAGE_FORMATS_801A0470;
	while (format != 0 && found == 0) {
		if (lbl_8042C9A4->rwstrcmp(format->lcExtension, key) == 0) {
			found = format;
		} else {
			format = format->nextFormat;
		}
	}

	if (found == 0) {
		found = (RwImageFormat801A0470*)lbl_8042C9A4->freeListAlloc(RW_IMAGE_FORMAT_FREE_LIST);
		if (found == 0) {
			return 0;
		}
		memcpy(found->lcExtension, key, RW_IMAGE_EXTENSION_SIZE);
		found->ucExtension[0] = '.';
		lbl_8042C9A4->rwstrncpy(&found->ucExtension[1], extension, RW_IMAGE_EXTENSION_SIZE - 2);
		found->ucExtension[RW_IMAGE_EXTENSION_SIZE - 1] = 0;
		lbl_8042C9A4->rwstrupr(found->ucExtension);
		found->imageRead          = 0;
		found->imageWrite         = 0;
		found->nextFormat         = RW_IMAGE_FORMATS_801A0470;
		RW_IMAGE_FORMATS_801A0470 = found;
	}
	if (imageRead != 0) {
		found->imageRead = imageRead;
	}
	if (imageWrite != 0) {
		found->imageWrite = imageWrite;
	}
	return 1;
}
}
