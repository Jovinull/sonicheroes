#include "types.h"

// message.cpp and MESSAGE's member names/layout are corroborated by PS2 DWARF.
// GameCube text boundary: 0x800CE010-0x800CF070. GameCube DisplayMessage also
// accepts two offset arguments absent from the PS2 signature.
// Deferred emission permits the language-change paths to inline destruction
// and reverses the definitions into the retail order; see language-audit.md.
// All nine retail functions and their owned data match natively. setupBBox
// retains its ordinary out-of-line definition: its body is linker-stripped,
// but its constants precede the constructor's height constant. No instruction
// post-processor is used.
struct Rt2dBrush;
struct Rt2dFont {
	u8 unk_0x00[0x10];
	s32 unk_0x10;
};
struct MessageRGBA {
	u8 red, green, blue, alpha;
};
struct MessageV2 {
	f32 x, y;
};
struct MessageBox {
	f32 x, y, w, h;
};
struct MessagePlacement {
	f32 x, y, height;
};
enum Rt2dJustificationType { };
struct MessageMode {
	s8 flags[0x2c];
	s32 values[6];
};
struct MessageGlobals {
	char* title;
	s32 width, height;
};
struct MessageRwGlobals {
	u8 unk_0x00[0x138];
	void (*free)(void*);
};
extern "C" {
extern MessageMode* lbl_8042C180;
extern MessageGlobals RsGlobal;
extern MessageRwGlobals* lbl_8042C9A4;
void fn_80169EF4(Rt2dBrush*);
void fn_8016E230(Rt2dFont*);
Rt2dFont* fn_8016E810(char*);
Rt2dBrush* fn_80169E28();
void fn_8016A4C4(Rt2dBrush*, MessageRGBA*, MessageRGBA*, MessageRGBA*, MessageRGBA*);
char* RsPathnameCreate(const char*);
void RsPathnameDestroy(char*);
void fn_8016E054(char*);
void fn_8016F488();
void fn_8016EAB4();
void fn_8016F860();
f32 fn_8016E108(Rt2dFont*, char*, f32);
void fn_8016E840(Rt2dFont*, char*, f32, MessageV2*, Rt2dBrush*);
char* fn_800426E0(char*, s32*);
u32 strlen(const char*);
s32 strcmp(const char*, const char*);
char* strcpy(char*, const char*);
s32 sprintf(char*, const char*, ...);
void OSReport(const char*, ...);
void* memset(void*, s32, u32);
}

class MESSAGE
{
public:
	char fname[64];
	Rt2dBrush* brush;
	MessageRGBA col[4];
	MessageBox bbox;
	f32 height;
	char* dttbl;
	s32 dttbllen;
	char recout[256];
	s32 lenout;
	Rt2dFont* jfFonts[16];
	MESSAGE(char*);
	~MESSAGE();
	s32 convLine(char*);
	s16 searchTbl(char*, u16*, u16*);
	s32 DisplayMessage(char*, f32, f32, Rt2dJustificationType, f32, f32);
	s32 ReleaseFontFile();
	s32 LoadFontFile(char*);
	s32 jfConvJFont(char*, s32, s32*, s32*);
	void setupBBox();
	void setupBrush();
};

void RemoveLangMessage();
MESSAGE* MessageEuc;
MessageRGBA ColorWhite = { 255, 255, 255, 255 };
static f32 fontHight   = 0.1f;
static f32 fontBlank   = 0.3f;
// GameCube placement data; descriptive names inferred from the access pattern.
static MessagePlacement fontPlacement[6]
    = { { 0, 0, 23 }, { -0.11680000275373459f, 0, 20.610000610351562f }, { 0, 0, 23 }, { 0, 0, 23 },
	      { -0.11680000275373459f, 0, 20.610000610351562f }, { 0, 0, 23 } };
static s32 fontPlacementIndex[2][3] = { { 0, 1, 2 }, { 3, 4, 5 } };

inline s32 MESSAGE::jfConvJFont(char* text, s32 index, s32* font, s32* code)
{
	switch (lbl_8042C180->flags[19]) {
		case 0:
		case 6: {
			u32 c1 = text[index] & 0xff, c2 = text[index + 1] & 0xff;
			if (!(c1 & 0x80)) {
				*font = c1;
				*code = c2;
			} else {
				*font = -1;
				*code = c1;
			}
			break;
		}
		case 1:
		default: {
			u32 c = text[index] & 0xff;
			if (c == 0x81 || c == 0x83) {
				*font = -1;
				*code = c;
			} else if (c < 0x7b) {
				*font = 0;
				*code = c - 0x20;
			} else if (c < 0xcf) {
				*font = 1;
				*code = c - 0x7b;
			} else {
				*font = 2;
				*code = c - 0xcf;
			}
			break;
		}
	}
	return 0;
}

inline void MESSAGE::setupBrush()
{
	brush  = fn_80169E28();
	col[0] = ColorWhite;
	col[1] = ColorWhite;
	col[2] = ColorWhite;
	col[3] = ColorWhite;
	fn_8016A4C4(brush, &col[0], &col[1], &col[2], &col[3]);
}

MESSAGE::MESSAGE(char* name)
{
	char* path = RsPathnameCreate("./font/");
	fn_8016E054(path);
	RsPathnameDestroy(path);
	fname[0] = 0;
	height   = 32.0f;
	memset(jfFonts, 0, sizeof(jfFonts));
	setupBrush();
	setupBBox();
	if (name)
		LoadFontFile(name);
}

void MESSAGE::setupBBox()
{
	bbox.x = 100.0f;
	bbox.y = 300.0f;
	bbox.w = 320.0f;
	bbox.h = 100.0f;
}

MESSAGE::~MESSAGE()
{
	fn_80169EF4(brush);
	ReleaseFontFile();
}

s32 MESSAGE::LoadFontFile(char* name)
{
	char path[128];
	if (!strcmp(fname, name))
		return 1;
	ReleaseFontFile();
	for (s32 i = 0; i < 16; ++i) {
		sprintf(path, "%s%02d", name, i);
		jfFonts[i] = fn_8016E810(path);
		if (jfFonts[i])
			jfFonts[i]->unk_0x10 = 0;
	}
	sprintf(path, "font/%s.txt", name);
	dttbl = fn_800426E0(path, &dttbllen);
	if (!dttbl) {
		char error[256];
		sprintf(error, "[%s]が読めない\n", path);
		OSReport(error);
	}
	strcpy(fname, name);
	return 0;
}

s32 MESSAGE::ReleaseFontFile()
{
	if (jfFonts[0]) {
		for (s32 i = 0; i < 16; ++i)
			if (jfFonts[i]) {
				fn_8016E230(jfFonts[i]);
				jfFonts[i] = 0;
			}
		lbl_8042C9A4->free(dttbl);
		fname[0] = 0;
		return 1;
	}
	return 0;
}

s32 MESSAGE::DisplayMessage(
    char* text, f32 x, f32 y, Rt2dJustificationType justify, f32 offsetX, f32 offsetY)
{
	f32 posX = offsetX;
	s32 font, code;
	s32 i;
	f32 width, maxWidth;
	f32 scale;
	s32 step;
	s32 mode;
	s32 tv = lbl_8042C180->flags[17] == 2;
	switch (lbl_8042C180->values[3]) {
		case 0:
		case 1:
			mode = 1;
			break;
		case 5:
			mode = 2;
			break;
		default:
			mode = 0;
			break;
	}
	s32 placement = fontPlacementIndex[tv][mode];
	MessageV2 pos = { 0, 0 };
	pos.x         = x;
	pos.y         = y;
	if (!jfFonts[0] || !brush)
		return 0;
	fn_8016F488();
	fn_8016EAB4();
	switch (lbl_8042C180->flags[19]) {
		case 0:
		case 6:
			step = 2;
			break;
		default:
			step = 1;
			break;
	}
	convLine(text);
	scale                = fontPlacement[placement].height / RsGlobal.height;
	static char glyph[2] = "";
	if (justify == 1) {
		width    = 0;
		maxWidth = 0;
		for (i = 0; i < lenout; i += step) {
			jfConvJFont(recout, i, &font, &code);
			if (font < 0) {
				if (step == 2)
					--i;
				switch (code & ~0x80) {
					case 3:
						if (width > maxWidth)
							maxWidth = width;
						width = 0;
						continue;
				}
			}
			glyph[0] = (char)((char)code + 32);
			width += fn_8016E108(jfFonts[font], glyph, scale);
		}
		if (width > maxWidth)
			maxWidth = width;
		if (lbl_8042C180->flags[19] == 6)
			maxWidth *= 1.0f - fontHight;
		posX = posX
		    + (0.5f * ((f32)RsGlobal.width / RsGlobal.height / 1.083f - maxWidth)
		        + fontPlacement[placement].x);
		pos.x = posX;
		pos.y = y + fontPlacement[placement].y + offsetY;
	} else {
		posX  = x + fontPlacement[placement].x;
		pos.x = posX;
		pos.y = y + fontPlacement[placement].y;
	}
	for (i = 0; i < lenout; i += step) {
		jfConvJFont(recout, i, &font, &code);
		if (font < 0) {
			if (step == 2)
				--i;
			switch (code & ~0x80) {
				case 3:
					pos.x = posX;
					pos.y -= scale * (1.0f + fontBlank);
					continue;
				default:
					goto done;
			}
		}
		glyph[0]      = (char)((char)code + 32);
		f32 previousX = pos.x;
		fn_8016E840(jfFonts[font], glyph, scale, &pos, brush);
		if (lbl_8042C180->flags[19] == 6)
			pos.x -= fontHight * (pos.x - previousX);
	}
done:
	fn_8016F860();
	return 1;
}

s16 MESSAGE::searchTbl(char* text, u16* font, u16* code)
{
	s32 offset = 0;
	s16 index  = 0;
	u8* table  = (u8*)dttbl;
	s32 column = 0, row = 0;
	*font = 0;
	*code = 0;
	do {
		if (table[offset] < 0x80) {
			if ((u8)text[0] < 0x80 && text[0] == table[offset])
				return index;
			++offset;
			++index;
			++column;
			++*code;
		} else {
			if ((u8)text[0] >= 0x80 && text[0] == dttbl[offset] && text[1] == dttbl[offset + 1])
				return index;
			offset += 2;
			++index;
			column += 2;
			++*code;
		}
		if (column >= 19) {
			column = 0;
			if (++row >= 10) {
				++*font;
				*code = 0;
				row   = 0;
			}
		}
	} while (offset < dttbllen);
	return index;
}

s32 MESSAGE::convLine(char* line)
{
	lenout     = 0;
	s32 length = strlen(line);
	switch (lbl_8042C180->flags[19]) {
		case 0:
		case 6:
			for (s16 i = 0; i < length; i += 2) {
				char* current = &line[i];
				u16 c1 = current[0] & 0xff, c2 = current[1] & 0xff;
				u16 font, code;
				if (c1 == '\\' && c2 == 'n')
					recout[lenout++] = (char)0x83;
				else if (c1 == 0x0au) {
					recout[lenout++] = (char)0x83;
					--i;
				} else if ((c1 >= '0' && c1 <= '9') || (c1 >= 'a' && c1 <= 'z')
				    || (c1 >= 'A' && c1 <= 'Z') || c1 == ' ') {
					if (searchTbl(&line[i], &font, &code) >= 0) {
						recout[lenout++] = (char)font;
						recout[lenout++] = (char)code;
						--i;
					}
				} else if (searchTbl(&line[i], &font, &code) >= 0) {
					recout[lenout++] = (char)font;
					recout[lenout++] = (char)code;
				}
			}
			break;
		case 1:
		default:
			for (s16 i = 0; i < length; ++i) {
				char* current = &line[i];
				u8 c1 = current[0], c2 = current[1];
				if (c1 == '\\' && c2 == ',') {
					++i;
					c1 = c2;
				}
				if (c1 == '\\' && c2 == '"') {
					++i;
					c1 = c2;
				}
				if (c1 == '\\' && c2 == 'n') {
					recout[lenout++] = (char)0x83;
					++i;
				} else if (c1 == 0x0au)
					recout[lenout++] = (char)0x83;
				else
					recout[lenout++] = (char)c1;
			}
			break;
	}
	return lenout;
}

void OnLangChange()
{
	switch (lbl_8042C180->flags[19]) {
		case 0:
		case 6:
			RemoveLangMessage();
			break;
		default:
			if (!MessageEuc)
				MessageEuc = new MESSAGE("a_euascii");
			break;
	}
}

void RemoveLangMessage()
{
	if (MessageEuc) {
		delete MessageEuc;
		MessageEuc = 0;
	}
}
