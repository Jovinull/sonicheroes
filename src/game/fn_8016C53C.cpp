// Builds the extended character map of a 2D font (HYPOTHESIS: part of the Rt2d font reader):
// scans the character codes of the font's glyphs (the code table at +0xA0C of lbl_803EC968) for
// the smallest and largest positive code, allocates a s16 map spanning that range, fills it with
// -1 and stores each glyph's index at its code. The map, its first code and its size go to the
// font (+0x120, +0x118, +0x11C). Returns the font, or null when the map cannot be allocated; a
// font without positive codes is left unchanged. Names follow fn_8016BD6C.
// NonMatching: retail keeps the code range (highest - lowest) in a fifth saved register and runs
// the scan with highest in a volatile register, four instructions fewer than this source
// (102 words). Declaration permutations do not change it.
#include "game/rw_engine.h"

struct Font8016C53C {
	u8 pad0[0x118];
	s32 firstExtended; // 0x118
	s32 numExtended;   // 0x11C
	s16* extendedMap;  // 0x120
	s32 numGlyphs;     // 0x124
};

struct Rt2dGlobals8016C53C {
	u8 pad0[0xA0C];
	s32* glyphCodes; // 0xA0C
};

extern "C" {
extern Rt2dGlobals8016C53C lbl_803EC968;

Font8016C53C* fn_8016C53C(Font8016C53C* font)
{
	s32 lowest;
	s32 highest;
	s32 found;
	s32* code;
	s32 i;
	s32 size;
	s16* map;

	lowest  = 0xFFFF;
	highest = 0;
	found   = 0;
	code    = lbl_803EC968.glyphCodes;

	for (i = 0; i < font->numGlyphs; i++) {
		if (*code > 0) {
			if (*code < lowest) {
				lowest = *code;
			}
			if (*code > highest) {
				highest = *code;
			}
			found = 1;
		}
		code++;
	}

	if (found > 0) {
		size = highest - lowest + 1;
		map  = (s16*)lbl_8042C9A4->rwmalloc(size * sizeof(s16));
		if (map == 0) {
			return 0;
		}
		for (i = 0; i < size; i++) {
			map[i] = -1;
		}
		for (i = 0; i < font->numGlyphs; i++) {
			if (lbl_803EC968.glyphCodes[i] > 0) {
				map[lbl_803EC968.glyphCodes[i] - lowest] = i;
			}
		}
		font->numExtended   = size;
		font->firstExtended = lowest;
		font->extendedMap   = map;
	}
	return font;
}
}
