// Adds unknown chunks to an info structure (HYPOTHESIS: libpng png_set_unknown_chunks): grows the
// chunk array (fn_8017CDA4, HYPOTHESIS: png_malloc; old array freed with fn_8017CE74,
// HYPOTHESIS: png_free), copies each chunk's name and a fresh copy of its data, records the
// current read/write mode byte as its location and flags the array as owned (0x200). Nothing is
// done for a null structure or an empty list.
#include "MSL_C/string.h"
#include "types.h"

// Unknown chunk (HYPOTHESIS: png_unknown_chunk, 0x14 bytes).
struct PngUnknownChunk80190FCC {
	char name[5]; // 0x0
	u8 pad5[0x3];
	u8* data;    // 0x8
	u32 size;    // 0xC
	u8 location; // 0x10
	u8 pad11[0x3];
};

// Fields used here (HYPOTHESIS: png_struct and png_info layouts).
struct PngStruct80190FCC {
	u8 pad0[0x28];
	u32 mode; // 0x28
};

struct PngInfo80190FCC {
	u8 pad0[0xB8];
	u32 freeMe;                             // 0xB8
	PngUnknownChunk80190FCC* unknownChunks; // 0xBC
	s32 unknownChunksNum;                   // 0xC0
};

#define PNG_FREE_UNKN 0x200

extern "C" {
void* fn_8017CDA4(PngStruct80190FCC* png, u32 size);
void fn_8017CE74(PngStruct80190FCC* png, void* block);
char* strcpy(char* dst, const char* src);

void fn_80190FCC(PngStruct80190FCC* png, PngInfo80190FCC* info, PngUnknownChunk80190FCC* unknowns,
    s32 numUnknowns)
{
	PngUnknownChunk80190FCC* np;
	s32 i;

	if (png == 0 || info == 0 || numUnknowns == 0) {
		return;
	}

	np = (PngUnknownChunk80190FCC*)fn_8017CDA4(
	    png, (info->unknownChunksNum + numUnknowns) * sizeof(PngUnknownChunk80190FCC));
	memcpy(np, info->unknownChunks, info->unknownChunksNum * sizeof(PngUnknownChunk80190FCC));
	fn_8017CE74(png, info->unknownChunks);
	info->unknownChunks = 0;

	for (i = 0; i < numUnknowns; i++) {
		PngUnknownChunk80190FCC* to   = np + info->unknownChunksNum + i;
		PngUnknownChunk80190FCC* from = unknowns + i;
		strcpy(to->name, from->name);
		to->data = (u8*)fn_8017CDA4(png, from->size);
		memcpy(to->data, from->data, from->size);
		to->size     = from->size;
		to->location = (u8)(png->mode & 0xFF);
	}

	info->unknownChunks = np;
	info->unknownChunksNum += numUnknowns;
	info->freeMe |= PNG_FREE_UNKN;
}
}
