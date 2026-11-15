// Draws a string with a 2D font (HYPOTHESIS: Rt2dFontShow-style rendering): pushes the current
// transform, moves to the anchor, scales by the height and drops by the font baseline, then for
// each character (one byte, or two for fonts with flag 0x2) looks up its glyph (directly below
// 0x80, through the extended table at +0x118 above), paints the glyph path with the brush
// (fn_801724B4) and advances by the glyph width plus the font's spacing. Pops the transform and
// returns the font. Names are inferred from this function only.
#include "game/rw_engine.h"

struct V2d8016BD6C {
	f32 x;
	f32 y;
};

struct Glyph8016BD6C {
	f32 width;  // 0x0
	u32 hidden; // 0x4: glyphs with nonzero +0x4 are skipped
	u8 pad8[0x18 - 0x8];
	void* path; // 0x18
	u8 pad1C[0x20 - 0x1C];
};

struct Font8016BD6C {
	u8 pad0[0x8];
	f32 baseline; // 0x8
	f32 spacing;  // 0xC
	u32 flags;    // 0x10: FONT_8016BD6C_WIDE_CHARS
	u8 pad14[0x18 - 0x14];
	s16 charMap[0x80]; // 0x18: glyph index of characters below 0x80, or -1
	s32 firstExtended; // 0x118
	s32 numExtended;   // 0x11C
	s16* extendedMap;  // 0x120
	u8 pad124[0x128 - 0x124];
	RwSList* glyphs; // 0x128
};

#define FONT_8016BD6C_WIDE_CHARS 0x2

extern "C" {
extern f32 lbl_8042F448; // 0.0f
void* fn_8019460C(RwSList* sList);
// HYPOTHESIS: CTM push/pop, translate and scale (Rt2dCTMPush, Rt2dCTMPop, Rt2dCTMTranslate,
// Rt2dCTMScale) and the glyph path fill (Rt2dPathFill).
void fn_8016F488(void);
void fn_8016F860(void);
void fn_8016F8FC(f32 x, f32 y);
void fn_8016F894(f32 x, f32 y);
void fn_801724B4(void* path, void* brush);

Font8016BD6C* fn_8016BD6C(
    Font8016BD6C* font, const u8* text, f32 height, V2d8016BD6C* anchor, void* brush)
{
	const u8* string;
	Glyph8016BD6C* glyphs;
	s32 step;
	u8 mask;
	s32 high;
	s32 c;

	string = text;
	if (font != 0) {
		glyphs = (Glyph8016BD6C*)fn_8019460C(font->glyphs);
		if (font->flags & FONT_8016BD6C_WIDE_CHARS) {
			step = 2;
			mask = 0xFF;
			high = 1;
		} else {
			step = 1;
			mask = 0;
			high = 0;
		}
		fn_8016F488();
		fn_8016F8FC(anchor->x, anchor->y);
		fn_8016F894(height, height);
		fn_8016F8FC(lbl_8042F448, -font->baseline);

		c = string[0] | ((string[high] & mask) << 8);
		while (c > 0) {
			s32 index;
			if (c >= 0x80) {
				s32 k = c - font->firstExtended;
				if (k >= 0 && k < font->numExtended) {
					index = font->extendedMap[k];
				} else {
					index = -1;
				}
			} else {
				index = font->charMap[c];
			}
			string += step;
			if (index >= 0) {
				Glyph8016BD6C* glyph = &glyphs[index];
				if (glyph->hidden == 0) {
					fn_801724B4(glyph->path, brush);
					fn_8016F8FC(glyph->width + font->spacing, lbl_8042F448);
				}
			}
			c = string[0] | ((string[high] & mask) << 8);
		}
		fn_8016F860();
	}
	return font;
}
}
