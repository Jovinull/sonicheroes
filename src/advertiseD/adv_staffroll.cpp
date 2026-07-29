#include "types.h"

// ADV_STAFFROLL (staff-roll / credits scroll) translation unit.
//
// Reference-guided from the Sonic Heroes PS2 Sep-28-2003 debug prototype:
// class ADV_STAFFROLL, source file D:\Tsonic\Tsonic\src\advertise\adv_staffroll.cpp.
// The GameCube retail REL bytes are ground truth; the PS2 build only supplies
// names/types/signatures (its overlay code is not present in the ELF, so no
// logic could be disassembled from it).

// One decoded credits line. Field names from the PS2 .mdebug (Color, Type,
// Height, String); byte offsets are ground truth from the GC REL.
struct sSTAFFROLLLINES {
	/* 0x00 */ u32 Color;
	/* 0x04 */ s32 Type;
	/* 0x08 */ f32 unk_0x08;
	/* 0x0c */ f32 unk_0x0c; // running scroll position
	/* 0x10 */ f32 unk_0x10;
	/* 0x14 */ u16* String;
}; // 0x18

// The staff-roll object (ctor at 0x131B0, vtable at 0x8460, size 0xa4).
struct Line {
	/* 0x00 */ u8 base[0x18];
	/* 0x18 */ void* vtable;
	/* 0x1c */ u8 unk_0x1c[0x2];
	/* 0x1e */ u16 unk_0x1e;
	/* 0x20 */ u8 unk_0x20[0x8];
	/* 0x28 */ s32 unk_0x28;
	/* 0x2c */ s32 mode;
	/* 0x30 */ u8 unk_0x30[0x10];
	/* 0x40 */ s32 unk_0x40;
	/* 0x44 */ s32 unk_0x44;
	/* 0x48 */ u8 unk_0x48[0x38];
	/* 0x80 */ f32 Speed;
	/* 0x84 */ sSTAFFROLLLINES* Lines;
	/* 0x88 */ s32 LineNum;
	/* 0x8c */ f32 x;
	/* 0x90 */ f32 y;
	/* 0x94 */ f32 z;
	/* 0x98 */ s32 timer;
	/* 0x9c */ s32 unk_0x9c;
	/* 0xa0 */ u8 r;
	/* 0xa1 */ u8 g;
	/* 0xa2 */ u8 b;
	/* 0xa3 */ u8 a;
};

// Heap/font manager singleton (lbl_8042C9A4 points to it). It stores its
// allocator/free entry points as function pointers at fixed offsets.
struct HeapMgr {
	/* 0x000 */ u8 pad_0[0x138];
	/* 0x138 */ void (*Free)(void* p);
	/* 0x13c */ void* unk_0x13c;
	/* 0x140 */ void* (*Alloc)(s32 size, s32 count);
};

extern "C" {

// File-scope statics (dtk-named; addresses are ground truth).
extern void* lbl_1_bss_7E8; // decoded staff-roll CSV text
extern void* lbl_1_bss_7EC; // CSV line index
extern s32 lbl_1_bss_7F0;
extern void* lbl_1_bss_7F4;
extern void* lbl_1_bss_7F8[9]; // per-logo textures
extern void* lbl_1_bss_81C;
extern void* lbl_1_bss_820[4];

// External helpers (DOL / other REL objects).
extern void fn_800426B4(void* p);
extern void fn_801A46D0(void* p);
extern void fn_8012ECE0(void);
extern void fn_8012FF6C(void* tag);
extern u8 lbl_803E8150;
extern u8 lbl_1_data_8450;
extern void fn_800A8264(Line* self);
extern void* advE3Rom_resume(s32 size);
extern void fn_8012F3D0(void* tag, void* str);
extern void fn_800A8828(Line* self, void* parent);
extern s32 fn_1_12A0(void* obj, s32 x);
extern void* lbl_8042C180;
extern void* lbl_1_data_844C;
extern u8 lbl_1_data_8460;
extern void fn_1_12A40(Line* self, char* csv, s32 n);
extern HeapMgr* lbl_8042C9A4;
extern void fn_1_12690(Line* self, sSTAFFROLLLINES* line, char* src);
s32 ADV_STAFFROLL_GetLineNum(Line* self, const char* str, s32 n);
s32 fn_1_12474(Line* self, char* dst, const char* src, char delim);
void ADV_STAFFROLL_StrCpy(Line* self, u16* dst, const char* src);
extern s32 fn_801C3C04(const char* a, const char* b);
extern s32 strlen(const char* s);
extern u8 lbl_1_data_8494; // "SEGA"
extern u8 lbl_1_data_849C; // "SONICTEAM"
extern u8 lbl_1_data_84A8; // "DOLBY"
extern u8 lbl_1_data_84B0; // "RW"
extern u8 lbl_1_data_84B4; // "VSI"
extern u8 lbl_1_data_84B8; // "ADX"
extern u8 lbl_1_data_84BC; // "SOFDEC"
extern void fn_800A8620(Line* self, s32 flag);
extern void advE3Rom_pause(Line* self);
extern void fn_80194294(s32 id, u32* out);
extern void fn_80194234(s32 id, u32 val);
extern void fn_800D5488(f32 a, f32 b, f32 w, f32 h, void* tex, void* rgba);
extern void fn_8012F728(void* tag);
extern void fn_8012F14C(void* tag);
extern void fn_8012F1F8(void* tag, u16* str, f32 x, f32 y, f32 sx, f32 sy, sSTAFFROLLLINES* line);
extern s32 RsGlobal[];
extern void fn_1_122CC(Line* self, sSTAFFROLLLINES* line, f32 w, f32 h);
extern void fn_801942C0(s32 mode, void* verts, s32 count);
extern void fn_1_12450(u8* dst, const u8* src);
extern const s32 lbl_1_rodata_19F8[9];
// Float constants live in the module's shared .rodata. Referenced by their dtk
// names so MWCC emits the target's individual per-constant lis/addi/lfs loads
// (a REL can't reach these via r2/SDA2, and inline literals would pool behind a
// pinned base register); named relocs also pair cleanly in objdiff.
extern const f32 lbl_1_rodata_1A1C;
extern const f32 lbl_1_rodata_1A20;
struct FloatValue {
	f32 value;
};
extern const FloatValue lbl_1_rodata_1A24;
extern const f32 lbl_1_rodata_1A28; // 24.0
extern const f32 lbl_1_rodata_1A2C; // 128.0
extern const f32 lbl_1_rodata_1A30; // 256.0
extern const f32 lbl_1_rodata_1A34; // 1024.0
extern const f32 lbl_1_rodata_1A38; // 512.0
extern const f64 lbl_1_rodata_1A40;
extern const f32 lbl_1_rodata_1A48; // 50.0
extern const f32 lbl_1_rodata_1A4C; // 60.0
extern void fn_801301C8(void* tag);
extern void fn_8012ED38(void);
extern void* fn_80057644(s32 size);
extern void* fn_800BCC84(void* obj, void* name, s32 flag);
extern void* fn_80012994(s32 size);
extern void* fn_800BC580(void* obj, s32 mode, void* buf);
extern void** fn_801A4BBC(void* archive, void* name);
extern void fn_800126C8(void* p);
extern void fn_800BCBD4(void* obj, s32 flag);
extern s32 fn_1_12138(void);
extern s32 sprintf(char* buf, const char* fmt, ...);
extern void* fn_800426E0(void* name, void* countOut);
extern u8 lbl_1_data_84C4;
extern u8 lbl_1_data_84E4;
extern void* lbl_1_data_82A8[9];
extern void* lbl_1_data_838C[];
extern void* lbl_1_data_8420[];
extern void* lbl_1_data_83EC[];

// Forward references within this TU.
void fn_1_12B50(Line* o);
void fn_1_12B90(Line* o);
void fn_1_12BD0(Line* o);
void fn_1_12F88(Line* o);
void fn_1_12BF0(Line* o);
void fn_1_12DF4(Line* o);
void fn_1_12518(Line* o);
void fn_1_125A0(Line* o, f32 div);
Line* fn_1_131B0(Line* self, void* parent, void* csv, void* csvIdx, const f32* pos);

// One textured-quad vertex (pos, packed RGBA, uv).
struct Vtx {
	/* 0x00 */ f32 x;
	/* 0x04 */ f32 y;
	/* 0x08 */ f32 z;
	/* 0x0c */ u8 col[4];
	/* 0x10 */ f32 u;
	/* 0x14 */ f32 v;
};

// Draw a logo as a textured quad: bind the logo texture, build a 4-vertex
// strip at the line's position sized w*h, then restore the texture register.
void fn_1_122CC(Line* self, sSTAFFROLLLINES* line, f32 w, f32 h)
{
	u8 col[4];
	u32 saved;
	Vtx q[4];
	f32 one;
	f32 yh;
	f32 zero;
	f32 half;
	f32 y;

	fn_80194294(1, &saved);
	fn_80194234(1, (u32)lbl_1_bss_7F8[lbl_1_rodata_19F8[line->Type]]);
	fn_1_12450(col, (const u8*)line);

	q[0].x      = line->unk_0x08;
	y           = line->unk_0x0c;
	q[0].y      = y;
	half        = lbl_1_rodata_1A1C;
	q[0].z      = half;
	q[0].col[0] = col[0];
	q[0].col[1] = col[1];
	q[0].col[2] = col[2];
	q[0].col[3] = col[3];
	zero        = lbl_1_rodata_1A20;
	q[0].u      = zero;
	q[0].v      = zero;

	q[1].x      = line->unk_0x08;
	yh          = y + h;
	q[1].y      = yh;
	q[1].z      = half;
	q[1].col[0] = col[0];
	q[1].col[1] = col[1];
	q[1].col[2] = col[2];
	q[1].col[3] = col[3];
	q[1].u      = zero;
	one         = lbl_1_rodata_1A24.value;
	q[1].v      = one;

	q[2].x      = line->unk_0x08 + w;
	q[2].y      = y;
	q[2].z      = half;
	q[2].col[0] = col[0];
	q[2].col[1] = col[1];
	q[2].col[2] = col[2];
	q[2].col[3] = col[3];
	q[2].u      = one;
	q[2].v      = zero;

	q[3].x      = line->unk_0x08 + w;
	q[3].y      = yh;
	q[3].z      = half;
	q[3].col[0] = col[0];
	q[3].col[1] = col[1];
	q[3].col[2] = col[2];
	q[3].col[3] = col[3];
	q[3].u      = one;
	q[3].v      = one;

	fn_801942C0(4, &q[0], 4);
	fn_80194234(1, saved);
}

// Copy a 4-byte colour (byte-wise).
void fn_1_12450(u8* dst, const u8* src)
{
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	dst[3] = src[3];
}

// Copy one CSV field out of src into dst until a delimiter, newline or NUL,
// honouring double-quote spans, dropping carriage returns, and returning the
// number of source characters consumed.
s32 fn_1_12474(Line* self, char* dst, const char* src, char delim)
{
	s32 count   = 0;
	s32 inQuote = 0;

	if (dst == 0) {
		goto done;
	}
	if (src == 0) {
		goto done;
	}

	while (1) {
		count++;

		if (*src == 0) {
			break;
		}
		if (*src == '\n') {
			break;
		}
		if (inQuote == 0 && *src == delim) {
			break;
		}

		if (*src == '\r') {
			src++;
			continue;
		}
		if (*src == '"') {
			inQuote = inQuote ? 0 : 1;
			src++;
			continue;
		}

		*dst++ = *src++;
	}

	*dst = 0;
done:
	return count;
}

// Cache: register every non-special line's decoded string with the font/heap.
void fn_1_12518(Line* o)
{
	s32 i;

	for (i = 0; i != o->LineNum; i++) {
		if (o->Lines[i].Type == 0) {
			fn_8012F3D0(&lbl_803E8150, o->Lines[i].String);
		}
	}
}

inline f32 adv_staffroll_div(f32 value, f32 divisor)
{
	return value / divisor;
}

inline s32 adv_staffroll_line_count(Line* line)
{
	return line->LineNum;
}

inline sSTAFFROLLLINES* adv_staffroll_lines(Line* line)
{
	return line->Lines;
}

// SpeedAdjust: total line height / divisor -> scroll speed.
void fn_1_125A0(Line* o, f32 div)
{
	s32 index;
	f32 divisor;
	f32 sum            = lbl_1_rodata_1A20;
	sSTAFFROLLLINES* p = adv_staffroll_lines(o);
	s32 count          = adv_staffroll_line_count(o);
	s32 i;
	divisor = div;

	if (((!sum) && (!sum)) && (!sum)) {
	}

	for (i = 0; i != count; i++) {
		index = i;
		sum += p[index].unk_0x10;
	}

	o->Speed = adv_staffroll_div(sum, divisor);
}

// StrCpy: widen an ASCII string into u16 glyphs, translating '?' to the
// copyright glyph 0xa9 and terminating at NUL or newline. const method; this
// in r3 is unused. dst in r4, src in r5.
void ADV_STAFFROLL_StrCpy(Line* self, u16* dst, const char* src)
{
	while (1) {
		s8 c = *src;

		if (c == 0 || c == '\n') {
			break;
		}

		if (c == '?') {
			*dst = 0xa9;
			dst++;
			src++;
		} else {
			src++;
			*dst = (u8)c;
			dst++;
		}
	}

	*dst = 0;
}

// Decode one CSV record (up to 3 comma fields) into a line: field 0 = credit
// name, field 1 = alternate, field 2 = a logo keyword (SEGA/SONICTEAM/...).
#pragma dont_inline on
void fn_1_12690(Line* self, sSTAFFROLLLINES* line, char* src)
{
	char buf[0x108];
	s32 count;
	s8 c;

	c = *src;
	if (c == 0 || c == '\n') {
		count = 0;
	} else {
		count = fn_1_12474(self, buf, src, ',');
	}
	if (count > 1) {
		s32 len        = strlen(buf);
		line->unk_0x08 = self->x;
		line->Type     = 0;
		line->String   = (u16*)lbl_8042C9A4->Alloc(len + 1, 2);
		line->unk_0x10 = 24.0f;
		((u8*)line)[0] = 0xff;
		((u8*)line)[1] = 0x80;
		((u8*)line)[2] = 0;
		((u8*)line)[3] = 0xff;
		ADV_STAFFROLL_StrCpy(self, line->String, buf);
		return;
	}

	src += count;
	c = *src;
	if (c == 0 || c == '\n') {
		count = 0;
	} else {
		count = fn_1_12474(self, buf, src, ',');
	}
	if (count > 1) {
		s32 len        = strlen(buf);
		line->unk_0x08 = self->x + self->z;
		line->Type     = 0;
		line->String   = (u16*)lbl_8042C9A4->Alloc(len + 1, 2);
		line->unk_0x10 = 24.0f;
		((u8*)line)[0] = 0xff;
		((u8*)line)[1] = 0xff;
		((u8*)line)[2] = 0xff;
		((u8*)line)[3] = 0xff;
		ADV_STAFFROLL_StrCpy(self, line->String, buf);
		return;
	}

	src += count;
	c = *src;
	if (c == 0 || c == '\n') {
		count = 0;
	} else {
		count = fn_1_12474(self, buf, src, ',');
	}
	if (count > 1) {
		line->unk_0x10 = 128.0f;
		if (fn_801C3C04(buf, (const char*)&lbl_1_data_8494) == 0) {
			line->Type = 2;
		} else if (fn_801C3C04(buf, (const char*)&lbl_1_data_849C) == 0) {
			line->Type = 3;
		} else if (fn_801C3C04(buf, (const char*)&lbl_1_data_84A8) == 0) {
			line->Type = 5;
		} else if (fn_801C3C04(buf, (const char*)&lbl_1_data_84B0) == 0) {
			line->Type = 4;
		} else if (fn_801C3C04(buf, (const char*)&lbl_1_data_84B4) == 0) {
			line->Type = 6;
		} else if (fn_801C3C04(buf, (const char*)&lbl_1_data_84B8) == 0) {
			line->Type     = 7;
			line->unk_0x10 = 256.0f;
		} else if (fn_801C3C04(buf, (const char*)&lbl_1_data_84BC) == 0) {
			line->Type     = 8;
			line->unk_0x10 = 256.0f;
		} else {
			line->Type = 2;
		}
		f32 pos = self->y;
		pos -= 128.0f;
		line->unk_0x08 = pos + self->x;
		line->String   = 0;
		((u8*)line)[0] = 0xff;
		((u8*)line)[1] = 0xff;
		((u8*)line)[2] = 0xff;
		((u8*)line)[3] = 0xff;
	} else {
		line->Type     = 1;
		line->String   = 0;
		line->unk_0x10 = 24.0f;
	}
}
#pragma dont_inline reset

// GetLineNum: count newline characters over n bytes. const method (this in r3,
// ignored); str in r4, n in r5.
s32 ADV_STAFFROLL_GetLineNum(Line* self, const char* str, s32 n)
{
	s32 count = 0;
	s32 i;

	for (i = 0; i != n; i++) {
		if ((s8)str[i] == '\n') {
			count++;
		}
	}

	return count;
}

// Decode: split the CSV text into decoded lines, stacking each line's scroll
// height so unk_0x0c holds the cumulative Y offset.
#pragma dont_inline on
void fn_1_12A40(Line* self, char* csv, s32 n)
{
	char buf[0x100];
	struct FloatValue {
		f32 value;
	};
	FloatValue zero;
	f32 y;
	s32 lineCount = ADV_STAFFROLL_GetLineNum(self, csv, n);
	s32 offset;
	s32 i;

	self->Lines = (sSTAFFROLLLINES*)lbl_8042C9A4->Alloc(0x18, lineCount);
	y           = lbl_1_rodata_1A20;
	i           = 0;
	offset      = 0;
	if ((i && i) && i) {
	}
	zero.value = y;

	for (; i != lineCount; i++) {
		s32 consumed                                              = fn_1_12474(self, buf, csv, 0);
		((sSTAFFROLLLINES*)((u8*)self->Lines + offset))->unk_0x08 = zero.value;
		((sSTAFFROLLLINES*)((u8*)self->Lines + offset))->unk_0x0c = y;
		fn_1_12690(self, (sSTAFFROLLLINES*)((u8*)self->Lines + offset), csv);
		y += ((sSTAFFROLLLINES*)((u8*)self->Lines + offset))->unk_0x10;
		csv += consumed;
		self->LineNum++;
		offset += 0x18;
	}
}
#pragma dont_inline reset

// Line fade step: darken the RGB by 0x10 each call; when it would cross zero,
// clamp to black and advance the line's mode.
void fn_1_12B50(Line* o)
{
	s32 d = o->r - 0x10;

	if (d <= 0) {
		o->r    = 0;
		o->g    = 0;
		o->b    = 0;
		o->mode = 2;
	} else {
		o->r = d;
		o->g = d;
		o->b = d;
	}
}

// Line fade-in step: brighten the RGB by 0x10 each call; when it would cross
// full white, clamp to 0xff and advance the line's mode.
void fn_1_12B90(Line* o)
{
	u32 d = (u8)o->r + 0x10;

	if (d >= 0xff) {
		o->r    = 0xff;
		o->g    = 0xff;
		o->b    = 0xff;
		o->mode = 7;
	} else {
		o->r = d;
		o->g = d;
		o->b = d;
	}
}

// Line dwell timer: advance and, after 0x258 frames, advance the mode.
void fn_1_12BD0(Line* o)
{
	if (o->timer++ > 0x258) {
		o->mode = 8;
	}
}

// Draw the highlight box behind a logo line: save the GX blend/compare state,
// force the box render mode, draw, then restore every saved register.
void fn_1_12BF0(Line* o)
{
	u32 s8, s6, s7, s9, sc, s14, s3, s4, se, sa, sb;

	if (lbl_1_bss_820[0] == 0) {
		return;
	}

	fn_80194294(8, &s8);
	fn_80194294(6, &s6);
	fn_80194294(7, &s7);
	fn_80194294(9, &s9);
	fn_80194294(0xc, &sc);
	fn_80194294(0x14, &s14);
	fn_80194294(3, &s3);
	fn_80194294(4, &s4);
	fn_80194294(0xe, &se);
	fn_80194294(0xa, &sa);
	fn_80194294(0xb, &sb);

	fn_80194234(8, 0);
	fn_80194234(6, 0);
	fn_80194234(7, 2);
	fn_80194234(9, 2);
	fn_80194234(0xc, 1);
	fn_80194234(0x14, 1);
	fn_80194234(3, 3);
	fn_80194234(4, 3);
	fn_80194234(0xe, 0);
	fn_80194234(0xa, 5);
	fn_80194234(0xb, 6);

	fn_800D5488(lbl_1_rodata_1A20, lbl_1_rodata_1A20, 1024.0f, 512.0f, lbl_1_bss_820[0], &o->r);

	fn_80194234(8, s8);
	fn_80194234(6, s6);
	fn_80194234(7, s7);
	fn_80194234(9, s9);
	fn_80194234(0xc, sc);
	fn_80194234(0x14, s14);
	fn_80194234(3, s3);
	fn_80194234(4, s4);
	fn_80194234(0xe, se);
	fn_80194234(0xa, sa);
	fn_80194234(0xb, sb);
}

// Draw all on-screen lines: text lines via the font printer, logo lines via
// fn_1_122CC, culling lines above the top or below the current scroll window.
#pragma opt_propagation off
void fn_1_12DF4(Line* self)
{
	sSTAFFROLLLINES* p;
	s32* dimensions;
	s32 i;
	f32 zero;

	fn_8012F728(&lbl_803E8150);
	p          = self->Lines;
	i          = 0;
	dimensions = RsGlobal;
	zero       = lbl_1_rodata_1A20;
	for (; i != self->LineNum; i++, p++) {
		if (p->unk_0x0c + p->unk_0x10 < zero) {
			continue;
		}
		if ((f32)(s32)dimensions[2] < p->unk_0x0c) {
			continue;
		}
		switch (p->Type) {
			case 0:
				void* tag;
				volatile sSTAFFROLLLINES* volatileLine;
				u16* str;
				f32 x;
				f32 y;
				f32 one;

				fn_8012F3D0(&lbl_803E8150, p->String);
				tag          = &lbl_803E8150;
				volatileLine = p;
				str          = volatileLine->String;
				x            = volatileLine->unk_0x08;
				y            = volatileLine->unk_0x0c;
				one          = *(volatile const f32*)&lbl_1_rodata_1A24.value;
				fn_8012F1F8(tag, str, x, y, one, one, p);
				break;
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				fn_1_122CC(self, p, 256.0f, 128.0f);
				break;
			case 7:
			case 8:
				fn_1_122CC(self, p, 256.0f, 256.0f);
				break;
		}
	}

	fn_8012F14C(&lbl_803E8150);
}
#pragma opt_propagation reset

// Scroll every decoded line up by Speed; when the last line has scrolled past
// the top, advance the mode.
void fn_1_12F88(Line* o)
{
	sSTAFFROLLLINES* last;
	s32 i;

	for (i = 0; i != o->LineNum; i++) {
		o->Lines[i].unk_0x0c -= o->Speed;
	}

	last = &o->Lines[o->LineNum - 1];
	if (last->unk_0x0c + last->unk_0x10 < lbl_1_rodata_1A20) {
		o->mode = 6;
	}
}

// Per-line update: run the base update, then dispatch on the line's mode.
#pragma dont_inline on
void fn_1_12FFC(Line* o)
{
	fn_800A8264(o);

	switch (o->unk_0x28) {
		case 5:
			fn_1_12DF4(o);
			break;
		case 6:
		case 7:
		case 8:
			fn_1_12BF0(o);
			break;
	}
}
#pragma dont_inline reset

// Empty virtual (vtable slot).
void fn_1_13058(void) { }

// Line mode-step dispatcher: run the handler for the line's current mode.
// Defined before the handlers so MWCC keeps them as out-of-line calls.
#pragma dont_inline on
void fn_1_1305C(Line* o)
{
	switch (o->unk_0x28) {
		case 5:
			fn_1_12F88(o);
			break;
		case 6:
			fn_1_12B90(o);
			break;
		case 7:
			fn_1_12BD0(o);
			break;
		case 8:
			fn_1_12B50(o);
			break;
	}
}
#pragma dont_inline reset

// Destructor: free every line's decoded string and the line array, run the
// base dtor, and (when the deleting-dtor flag is set) release the object.
void* fn_1_130C0(Line* o, s16 flag)
{
	if (o != 0) {
		o->vtable = &lbl_1_data_8460;
		if (o->Lines != 0) {
			s32 i;
			for (i = 0; i != o->LineNum; i++) {
				if (o->Lines[i].String != 0) {
					lbl_8042C9A4->Free(o->Lines[i].String);
				}
			}
			lbl_8042C9A4->Free(o->Lines);
		}
		lbl_1_bss_7F0 = 0;
		fn_800A8620(o, 0);
		if (flag > 0) {
			advE3Rom_pause(o);
		}
	}
	return o;
}

// Construct one staff-roll line object: base ctor, set vtable + defaults,
// decode the CSV line, then set scroll speed (framerate-adjusted on 60Hz).
#pragma dont_inline on
Line* fn_1_131B0(Line* self, void* parent, void* csv, void* csvIdx, const f32* pos)
{
	fn_800A8828(self, parent);
	self->vtable   = &lbl_1_data_8460;
	*(void**)self  = lbl_1_data_844C;
	self->unk_0x1e = 0xa4;
	self->unk_0x40 = 1;
	self->unk_0x44 = 1;
	self->unk_0x28 = 0;
	self->mode     = 5;
	self->Speed    = lbl_1_rodata_1A24.value;
	self->x        = pos[0];
	self->y        = pos[1];
	self->z        = pos[2];
	self->Lines    = 0;
	self->LineNum  = 0;
	self->timer    = 0;
	self->unk_0x9c = 0;
	self->r        = 0;
	self->g        = 0;
	self->b        = 0;
	self->a        = 0xff;

	fn_1_12A40(self, (char*)csv, (s32)csvIdx);

	if (fn_1_12A0(lbl_8042C180, 0x11) == 2) {
		fn_1_125A0(self, 50.0f * pos[3] / 60.0f);
	} else {
		fn_1_125A0(self, pos[3]);
	}

	fn_1_12518(self);
	lbl_1_bss_7F0 = 1;
	return self;
}
#pragma dont_inline reset

// Spawn one staff-roll line object at the supplied position.
#pragma force_active on
void fn_1_13310(void* parent, const f32* pos)
{
	Line* line;

	if (lbl_1_bss_7E8 != 0) {
		line = (Line*)advE3Rom_resume(0xa4);
		if (line != 0) {
			fn_1_131B0(line, parent, lbl_1_bss_7E8, lbl_1_bss_7EC, pos);
		}
	}
}
#pragma force_active reset

// Spawn one staff-roll line object at a fixed position.
void fn_1_1338C(void* parent)
{
	Line* line;

	if (lbl_1_bss_7E8 != 0) {
		line = (Line*)advE3Rom_resume(0xa4);
		if (line != 0) {
			fn_1_131B0(line, parent, lbl_1_bss_7E8, lbl_1_bss_7EC, (const f32*)&lbl_1_data_8450);
		}
	}
}

// Finalize: free the decoded CSV and per-logo textures, then tear down the
// font/heap the staff roll allocated.
void fn_1_13400(void)
{
	s32 i;
	void** p;

	if (lbl_1_bss_7E8 != 0) {
		fn_800426B4(lbl_1_bss_7E8);
		lbl_1_bss_7E8 = 0;
		lbl_1_bss_7EC = 0;
	}

	p = lbl_1_bss_7F8;
	for (i = 0; i < 9; i++) {
		*p++ = 0;
	}

	if (lbl_1_bss_7F4 != 0) {
		fn_801A46D0(lbl_1_bss_7F4);
		lbl_1_bss_7F4 = 0;
	}

	lbl_1_bss_820[0] = 0;

	if (lbl_1_bss_81C != 0) {
		fn_801A46D0(lbl_1_bss_81C);
		lbl_1_bss_81C = 0;
	}

	fn_8012ECE0();
	fn_8012FF6C(&lbl_803E8150);
}

// Initialize: load the logo-texture archive (caching the 9 logos), load the
// language-specific font archive, then load the credits CSV text.
void fn_1_13510(void)
{
	char buf[0x200];
	struct Handle {
		void* value;
	};
	Handle loader;
	void* scratch;
	void** found;
	s32 i;
	s32 region;

	fn_801301C8(&lbl_803E8150);
	fn_8012ED38();

	loader.value = fn_80057644(0x58);
	if (loader.value != 0) {
		loader.value = fn_800BCC84(loader.value, &lbl_1_data_84C4, 0);
	}
	if (loader.value != 0) {
		scratch = fn_80012994(0x96000);
		if (scratch != 0) {
			lbl_1_bss_7F4 = fn_800BC580(loader.value, 2, scratch);
			if (lbl_1_bss_7F4 != 0) {
				for (i = 0; i != 9; i++) {
					found = fn_801A4BBC(lbl_1_bss_7F4, lbl_1_data_82A8[i]);
					if (found != 0) {
						lbl_1_bss_7F8[i] = *found;
					}
				}
			}
			fn_800126C8(scratch);
		}
		fn_800BCBD4(loader.value, 1);
	}

	region = fn_1_12A0(lbl_8042C180, 0x13);
	if (region < 0 || region >= 7) {
		region = 1;
	}
	sprintf(buf, (const char*)lbl_1_data_838C[fn_1_12138()], lbl_1_data_8420[region]);

	Handle loader2;
	void* scratch2;
	loader2.value = fn_80057644(0x58);
	if (loader2.value != 0) {
		loader2.value = fn_800BCC84(loader2.value, buf, 0);
	}
	if (loader2.value != 0) {
		scratch2 = fn_80012994(0x96000);
		if (scratch2 != 0) {
			lbl_1_bss_81C = fn_800BC580(loader2.value, 2, scratch2);
			if (lbl_1_bss_81C != 0) {
				found = fn_801A4BBC(lbl_1_bss_81C, lbl_1_data_83EC[fn_1_12138()]);
				if (found != 0) {
					lbl_1_bss_820[0] = *found;
				}
			}
			fn_800126C8(scratch2);
		}
		fn_800BCBD4(loader2.value, 1);
	}

	lbl_1_bss_7E8 = fn_800426E0(&lbl_1_data_84E4, &lbl_1_bss_7EC);
}
}
