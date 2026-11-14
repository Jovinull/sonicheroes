// Records the palette histogram (HYPOTHESIS: libpng png_set_hIST): frees any previous one through
// fn_8017C024 (png_free_data, PNG_FREE_HIST), copies num_palette entries into memory allocated with
// fn_8017CDA4 (png_malloc), shares it with the info structure, marks hIST valid and owned. Without
// a palette it only warns through fn_8017C5FC (png_warning) with lbl_8028FF20.
#include "types.h"

#define PNG_INFO_hIST 0x40
#define PNG_FREE_HIST 0x8

struct Png80190128 {
	unsigned char pad0[0x168];
	unsigned short* hist; // 0x168
};

// Fields used here (HYPOTHESIS: png_info layout).
struct PngInfo80190128 {
	unsigned char pad0[0x8];
	unsigned int valid; // 0x8
	unsigned char padC[0x14 - 0xC];
	unsigned short numPalette; // 0x14
	unsigned char pad16[0x7C - 0x16];
	unsigned short* hist; // 0x7C
	unsigned char pad80[0xB8 - 0x80];
	unsigned int freeMe; // 0xB8
};

extern "C" {
extern char lbl_8028FF20[];
void fn_8017C5FC(void* png, const char* message);
void fn_8017C024(Png80190128* png, PngInfo80190128* info, unsigned int mask, int num);
void* fn_8017CDA4(Png80190128* png, unsigned int size);

void fn_80190128(Png80190128* png, PngInfo80190128* info, const unsigned short* hist)
{
	int i;
	if (png == 0 || info == 0) {
		return;
	}
	if (info->numPalette == 0) {
		fn_8017C5FC(png, lbl_8028FF20);
		return;
	}
	fn_8017C024(png, info, PNG_FREE_HIST, 0);
	png->hist = (unsigned short*)fn_8017CDA4(png, info->numPalette * sizeof(unsigned short));
	for (i = 0; i < info->numPalette; i++) {
		png->hist[i] = hist[i];
	}
	info->hist = png->hist;
	info->valid |= PNG_INFO_hIST;
	info->freeMe |= PNG_FREE_HIST;
}
}
