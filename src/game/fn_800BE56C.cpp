#include "types.h"

// Texture callback that replaces the eight special textures (returns the texture): the last two
// characters of the texture's name (+0x10) pick one of the eight suffixes of lbl_8023A4E0; for a
// match a new 4-flag raster with the texture's raster size and depth (+0x0: width +0xC, height
// +0x10, depth +0x14) is created (fn_801A19D4) and wrapped in a texture (fn_801A4874) stored in
// table[index]; the raster gets the 0x1000-byte image lbl_80304248[index] (locked with mode 9,
// fn_801A1AC8 / fn_801A16A0) and the texture the original name and filter mode 2 (+0x50).
// HYPOTHESIS: RwRasterCreate, RwTextureCreate, RwRasterLock/Unlock and RwTextureSetName.

struct Raster800BE56C {
	u8 pad0[0xC];
	s32 width;  // 0xC
	s32 height; // 0x10
	s32 depth;  // 0x14
};

struct Texture800BE56C {
	Raster800BE56C* raster; // 0x0
	u8 pad4[0x10 - 0x4];
	char name[0x40]; // 0x10
	u32 filter;      // 0x50
};

struct Names800BE56C {
	const char* names[8];
};

extern "C" {
extern const Names800BE56C lbl_8023A4E0;
extern void* lbl_80304248[8];
unsigned long strlen(const char* s);
char* strcpy(char* dst, const char* src);
int strcmp(const char* a, const char* b);
void* memcpy(void* dst, const void* src, unsigned long n);
Raster800BE56C* fn_801A19D4(s32 width, s32 height, s32 depth, s32 flags);
Texture800BE56C* fn_801A4874(Raster800BE56C* raster);
void* fn_801A1AC8(Raster800BE56C* raster, s32 level, s32 mode);
void fn_801A16A0(Raster800BE56C* raster);
void fn_801A49E4(Texture800BE56C* texture, const char* name);
}

// The index of the texture name's two-character suffix in lbl_8023A4E0, or -1.
static inline s8 SuffixIndex(Texture800BE56C* texture)
{
	Names800BE56C suffixes = lbl_8023A4E0;
	char suffix[4];

	if (strlen(texture->name) < 2) {
		return -1;
	}
	strcpy(suffix, &texture->name[strlen(texture->name) - 2]);
	for (s8 i = 0; i < 8; i++) {
		if (strcmp(suffix, suffixes.names[i]) == 0) {
			return i;
		}
	}
	return -1;
}

extern "C" Texture800BE56C* fn_800BE56C(Texture800BE56C* texture, Texture800BE56C** table)
{
	Raster800BE56C* raster = texture->raster;
	s8 index               = SuffixIndex(texture);

	if (index < 0) {
		return texture;
	}
	raster = fn_801A19D4(raster->width, raster->height, raster->depth, 4);
	if (raster != NULL) {
		table[index] = fn_801A4874(raster);
		if (table[index] != NULL) {
			void* image = lbl_80304248[index];
			memcpy(fn_801A1AC8(raster, 0, 9), image, 0x1000);
			fn_801A16A0(raster);
			fn_801A49E4(table[index], texture->name);
			table[index]->filter = (table[index]->filter & ~0xFF) | 2;
		}
	} else {
		table[index] = NULL;
	}
	return texture;
}
