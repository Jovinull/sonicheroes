// Reads an image (HYPOTHESIS: RwImageRead): takes the extension after the last '.' of the file
// name (past any drive, '/' or '\\' part), finds the registered image format whose lower- or
// upper-case extension matches, and reads the file through the image search path
// (fn_8019FE30 with the per-path reader fn_801A0148 and the format's read function). Returns the
// image, or null when the name has no extension, no format matches or the format cannot read.
#include "game/rw_engine.h"

// Registered image format (HYPOTHESIS: rwImageFormat).
struct RwImageFormat801A01C0 {
	char lcExtension[0x14];                  // 0x0
	char ucExtension[0x14];                  // 0x14
	RwImage* (*imageRead)(const char* name); // 0x28
	void* imageWrite;                        // 0x2C
	RwImageFormat801A01C0* nextFormat;       // 0x30
};

// Context handed to the per-path reader.
struct RwImageReadInfo801A01C0 {
	RwImage* (*imageRead)(const char* name); // 0x0
	RwImage* image;                          // 0x4: result
};

#define RW_IMAGE_FORMATS_801A01C0                                                                  \
	(*(RwImageFormat801A01C0**)((u8*)lbl_8042C9A4 + lbl_8042C9B0.globalsOffset + 0x21C))

extern "C" {
s32 fn_801A0148(const char* path, void* data);
// HYPOTHESIS: runs callback on each candidate path of the image search path.
void fn_8019FE30(
    const char* name, s32 mode, s32 (*callback)(const char* path, void* data), void* data);

RwImage* fn_801A01C0(const char* imageName)
{
	const char* name;
	const char* separator;
	const char* extension;
	RwImageFormat801A01C0* format;

	separator = lbl_8042C9A4->rwstrrchr(imageName, ':');
	if (separator != 0) {
		name = separator;
	} else {
		name = imageName;
	}
	separator = lbl_8042C9A4->rwstrrchr(name, '/');
	if (separator != 0) {
		name = separator;
	}
	separator = lbl_8042C9A4->rwstrrchr(name, '\\');
	extension = lbl_8042C9A4->rwstrrchr(separator ? separator : name, '.');
	if (extension != 0) {
		for (format = RW_IMAGE_FORMATS_801A01C0; format != 0; format = format->nextFormat) {
			if (lbl_8042C9A4->rwstrcmp(format->lcExtension, extension) == 0
			    || lbl_8042C9A4->rwstrcmp(format->ucExtension, extension) == 0) {
				if (format->imageRead != 0) {
					RwImageReadInfo801A01C0 info;
					info.imageRead = format->imageRead;
					info.image     = 0;
					fn_8019FE30(imageName, 5, fn_801A0148, &info);
					return info.image;
				}
				return 0;
			}
		}
		return 0;
	}
	return 0;
}
}
