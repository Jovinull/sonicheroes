#include "types.h"

// Releases the special-texture set (see fn_800BE56C and fn_800BDFC8): deletes the eight objects of
// lbl_80304268, frees lbl_8042C3EC, runs fn_801A4C84 and fn_801A4B8C on each texture of
// lbl_80304228 that has a raster (+0x4), destroys those textures (fn_801A491C) and frees the eight
// images of lbl_80304248, destroys the texture dictionary lbl_8042C3E8 (fn_801A46D0) and releases
// the three clumps of lbl_80253CC0 (fn_80147178, fn_80147288). HYPOTHESIS: RwTextureDestroy,
// RwTexDictionaryDestroy and RpClumpDestroy-like calls; the names are UNKNOWN.
// NonMatching (22 words, registers only): retail gives the first loop's counter r31 (its NULL a
// copy of it) and the later loops' counter r27, and sets up the array bases before the zero copies
// of the third loop; with one shared u8 counter MWCC uses r26 throughout, and separate counters
// lose the zero copies. Same family as fn_8004EF98.

class TObject800BF5D8
{
public:
	u8 pad0[0x18];
	virtual ~TObject800BF5D8();
};

struct Texture800BF5D8 {
	u8 pad0[0x4];
	void* raster; // 0x4
};

struct RwGlobals800BF5D8 {
	u8 pad0[0x138];
	void (*rwfree)(void* block); // 0x138
};

extern "C" {
extern TObject800BF5D8* lbl_80304268[8];
extern void* lbl_8042C3EC;
extern Texture800BF5D8* lbl_80304228[8];
extern void* lbl_80304248[8];
extern void* lbl_8042C3E8;
extern void* lbl_80253CC0[3];
extern RwGlobals800BF5D8* lbl_8042C9A4;
void fn_801A4C84(void* raster);
void fn_801A4B8C(Texture800BF5D8* texture);
void fn_801A491C(Texture800BF5D8* texture);
void fn_801A46D0(void* dictionary);
void fn_80147178(void* clump);
void fn_80147288(void* clump);
}

extern "C" void fn_800BF5D8(void)
{
	u8 i;

	for (i = 0; i < 8; i++) {
		if (lbl_80304268[i] != NULL) {
			delete lbl_80304268[i];
			lbl_80304268[i] = NULL;
		}
	}
	if (lbl_8042C3EC != NULL) {
		lbl_8042C9A4->rwfree(lbl_8042C3EC);
		lbl_8042C3EC = NULL;
	}
	for (i = 0; i < 8; i++) {
		if (lbl_80304228[i] != NULL && lbl_80304228[i]->raster != NULL) {
			fn_801A4C84(lbl_80304228[i]->raster);
			fn_801A4B8C(lbl_80304228[i]);
		}
	}
	for (i = 0; i < 8; i++) {
		if (lbl_80304228[i] != NULL) {
			fn_801A491C(lbl_80304228[i]);
			lbl_80304228[i] = NULL;
		}
		if (lbl_80304248[i] != NULL) {
			lbl_8042C9A4->rwfree(lbl_80304248[i]);
			lbl_80304248[i] = NULL;
		}
	}
	if (lbl_8042C3E8 != NULL) {
		fn_801A46D0(lbl_8042C3E8);
		lbl_8042C3E8 = NULL;
	}
	for (i = 0; i < 3; i++) {
		if (lbl_80253CC0[i] != NULL) {
			fn_80147178(lbl_80253CC0[i]);
			fn_80147288(lbl_80253CC0[i]);
			lbl_80253CC0[i] = NULL;
		}
	}
}
