// Closes the image module (HYPOTHESIS: _rwImageClose): frees the scratch buffer and the search
// path buffer, returns every registered image format to the format free list, destroys that free
// list and the image free list, and drops the instance count. Returns the instance.
#include "game/rw_engine.h"

// Registered image format (HYPOTHESIS: rwImageFormat); only the link is used here.
struct RwImageFormat8019F180 {
	u8 pad0[0x30];
	RwImageFormat8019F180* nextFormat; // 0x30
};

// Image module globals as seen through the format list head (+0x21C).
struct RwImageGlobals8019F180 {
	u8 pad0[0x21C];
	RwImageFormat8019F180* imageFormats; // 0x21C
};

#define RW_IMAGE_GLOBALS_8019F180                                                                  \
	((RwImageGlobals8019F180*)((u8*)lbl_8042C9A4 + lbl_8042C9B0.globalsOffset))

extern "C" {
void* fn_8019F180(void* instance)
{
	if (RW_IMAGE_SCRATCH_MEM != 0) {
		lbl_8042C9A4->rwfree(RW_IMAGE_SCRATCH_MEM);
		RW_IMAGE_SCRATCH_MEM      = 0;
		RW_IMAGE_SCRATCH_MEM_SIZE = 0;
	}
	if (RW_IMAGE_PATH != 0) {
		lbl_8042C9A4->rwfree(RW_IMAGE_PATH);
		RW_IMAGE_PATH      = 0;
		RW_IMAGE_PATH_SIZE = 0;
	}
	while (RW_IMAGE_GLOBALS_8019F180->imageFormats != 0) {
		RwImageFormat8019F180* format           = RW_IMAGE_GLOBALS_8019F180->imageFormats;
		RW_IMAGE_GLOBALS_8019F180->imageFormats = format->nextFormat;
		lbl_8042C9A4->freeListFree(RW_IMAGE_FORMAT_FREE_LIST, format);
	}
	if (RW_IMAGE_FORMAT_FREE_LIST != 0) {
		RwFreeListDestroy(RW_IMAGE_FORMAT_FREE_LIST);
		RW_IMAGE_FORMAT_FREE_LIST = 0;
	}
	if (RW_IMAGE_FREE_LIST != 0) {
		RwFreeListDestroy(RW_IMAGE_FREE_LIST);
		RW_IMAGE_FREE_LIST = 0;
	}
	lbl_8042C9B0.numInstances--;
	return instance;
}
}
