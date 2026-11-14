// Adds suggested palettes to an info structure (HYPOTHESIS: libpng png_set_sPLT): grows the
// palette array (fn_8017CDA4, HYPOTHESIS: png_malloc; old array freed with fn_8017CE74,
// HYPOTHESIS: png_free), gives each palette copies of its name and of its 16-byte entries, and
// flags the chunk as valid (0x2000) and the array as owned (0x20). The arguments are not checked.
#include "MSL_C/string.h"
#include "types.h"

// Suggested palette entry; 16 bytes in this build (layout UNKNOWN).
struct PngSPLTEntry80190EA0 {
	u8 bytes[0x10];
};

// Suggested palette (HYPOTHESIS: png_sPLT_t, 0x10 bytes).
struct PngSPLT80190EA0 {
	char* name; // 0x0
	u8 depth;   // 0x4
	u8 pad5[0x3];
	PngSPLTEntry80190EA0* entries; // 0x8
	s32 nentries;                  // 0xC
};

// Fields used here (HYPOTHESIS: png_info layout).
struct PngInfo80190EA0 {
	u8 pad0[0x8];
	u32 valid; // 0x8
	u8 padC[0xB8 - 0xC];
	u32 freeMe; // 0xB8
	u8 padBC[0xD4 - 0xBC];
	PngSPLT80190EA0* spltPalettes; // 0xD4
	s32 spltPalettesNum;           // 0xD8
};

#define PNG_INFO_sPLT 0x2000
#define PNG_FREE_SPLT 0x20

extern "C" {
void* fn_8017CDA4(void* png, u32 size);
void fn_8017CE74(void* png, void* block);
char* strcpy(char* dst, const char* src);
u32 strlen(const char* string);

void fn_80190EA0(void* png, PngInfo80190EA0* info, PngSPLT80190EA0* entries, s32 nentries)
{
	PngSPLT80190EA0* np;
	s32 i;

	np = (PngSPLT80190EA0*)fn_8017CDA4(
	    png, (info->spltPalettesNum + nentries) * sizeof(PngSPLT80190EA0));
	memcpy(np, info->spltPalettes, info->spltPalettesNum * sizeof(PngSPLT80190EA0));
	fn_8017CE74(png, info->spltPalettes);
	info->spltPalettes = 0;

	for (i = 0; i < nentries; i++) {
		PngSPLT80190EA0* to   = np + info->spltPalettesNum + i;
		PngSPLT80190EA0* from = entries + i;
		to->name              = (char*)fn_8017CDA4(png, strlen(from->name) + 1);
		strcpy(to->name, from->name);
		to->entries = (PngSPLTEntry80190EA0*)fn_8017CDA4(
		    png, from->nentries * sizeof(PngSPLTEntry80190EA0));
		memcpy(to->entries, from->entries, from->nentries * sizeof(PngSPLTEntry80190EA0));
		to->nentries = from->nentries;
		to->depth    = from->depth;
	}

	info->spltPalettes = np;
	info->spltPalettesNum += nentries;
	info->valid |= PNG_INFO_sPLT;
	info->freeMe |= PNG_FREE_SPLT;
}
}
