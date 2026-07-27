#include "types.h"
#include <rwsdk/rsglobal.h>

/*
 * CRI Sofdec user-data helpers.
 *
 * The PS2 prototype identifies this library as SUD. The GameCube boundaries
 * are independently visible in the REL: 0x87CC starts the SUD implementation,
 * fn_17_8B5C returns the SUD/GC version string, and 0x8EA8 starts the next
 * SFX conversion unit and its separate error-string family.
 */

typedef struct SfxHandle {
	u32 unk0;
	u32 unk4;
	u32 unk8;
	u32 unkC;
	s32 tag_valid;
	s32 tag_x;
	s32 tag_y;
	u32 unk1C;
	void* convert_handle;
	u32 out_zoffset;
	u32 out_zscale;
	void* frame_handle;
	u32 output_mode;
	u32 max_alpha;
	void* tables[10];
	u32 unk60;
	u32 unk64;
} SfxHandle;

typedef struct SfxFrameInfo {
	u8 unk0[0x4C];
	void* stream_info;
} SfxFrameInfo;

typedef struct SudPicture {
	u32 unk0;
	u32 unk4;
	u32 unk8;
	u32 width;
	u32 unk10;
	float unk14;
	float unk18;
	float unk1C;
	float unk20;
	float unk24;
	u32 unk28;
	u32 unk2C;
	u32 unk30;
	u32 unk34;
	u32 unk38;
	u32 unk3C;
	u32 unk40;
} SudPicture;

typedef struct SudPlane {
	s32 address;
	s32 stride;
	s32 remaining;
} SudPlane;

typedef struct SudPlanes {
	u32 unk0;
	SudPlane y;
	u32 unk10;
	SudPlane u;
	u32 unk20;
	SudPlane v;
} SudPlanes;

typedef struct SudStringPair {
	const char* value[2];
} SudStringPair;

typedef struct SudTail {
	char header[12];
	char number_format[8];
	char zeros[4];
	char newline[4];
	char padding[4];
} SudTail;

extern void fn_17_E89C(void*);
extern void fn_17_E8B8(void*);
extern void fn_17_10664(void*, void*);
extern void fn_17_EB0C(void*);
extern void fn_17_EB50(void*);
extern void fn_17_108A8(void*, s32, s32);
extern void* fn_80221610(void*, const char*, const char*, void*);
extern s32 strncmp(const char*, const char*, u32);
extern char* strcat(char*, const char*);
extern char* strncpy(char*, const char*, u32);
extern s32 sprintf(char*, const char*, ...);
extern s32 memcmp(const void*, const void*, u32);

extern const float lbl_17_rodata_374[];
extern const char lbl_17_rodata_408[];
extern const char lbl_17_rodata_410[];
extern const char lbl_17_rodata_390[];
extern const char lbl_17_rodata_3C8[];
extern const char lbl_17_rodata_3D8[];
extern const char lbl_17_rodata_3E4[];
extern const SudTail lbl_17_rodata_3E8;
extern const u32 lbl_8029BB80[];

extern s32 lbl_17_bss_C8;
extern const char* lbl_17_bss_CC;

const char lbl_17_rodata_390[0x34] = "\nCRI SUD/GC Ver.0.02 Build:May  9 2003 15:19:52\n";

#pragma peephole off
#pragma scheduling off
void fn_17_87CC(SudPicture* picture)
{
	float value;

	picture->unk0  = 0;
	picture->unk4  = 0;
	picture->unk8  = 0;
	picture->width = 0;
	picture->unk10 = 0;
	value          = lbl_17_rodata_374[0];
	picture->unk14 = value;
	picture->unk18 = value;
	picture->unk1C = value;
	picture->unk20 = value;
	picture->unk24 = value;
	picture->unk28 = 0;
	picture->unk2C = 0;
	picture->unk30 = RsGlobal.windowWidth;
	picture->unk34 = RsGlobal.windowHeight;
	picture->unk38 = 0;
	picture->unk40 = 1;
	picture->unk3C = 1;
}
#pragma scheduling reset
#pragma peephole on

s32 fn_17_8838(const void* data)
{
	if (data == NULL) {
		return 0;
	}
	return 20;
}

void fn_17_8850(const u8* data, s32 size, const u8** found, s32* found_size)
{
	s32 i;
	const u8* cursor = data;

	*found      = NULL;
	*found_size = 0;
	if (data == NULL || size <= 0) {
		return;
	}
	for (i = 0; i < size; i++) {
		if (memcmp(cursor, lbl_17_rodata_3E4, 1) == 0
		    && memcmp(cursor, &lbl_17_rodata_3E8, 8) == 0) {
			*found      = cursor;
			*found_size = fn_17_8838(*found);
		}
		cursor++;
	}
}

s32 fn_17_8918(const char* data, s32 size)
{
	if (data == NULL || size < 0) {
		return 0;
	}
	return strncmp(data + 0x13, lbl_17_rodata_3D8, 1) == 0;
}

s32 fn_17_8968(const char* data, s32 size)
{
	if (data == NULL || size < 0) {
		return 0;
	}
	return strncmp(data + 0x12, lbl_17_rodata_3C8, 1) == 0;
}

void fn_17_89B8(char* data, const s32* indices)
{
	const char* first[2]  = { "A", "D" };
	const char* second[2] = { "N", "C" };

	strncpy(data + 2, first[indices[0]], 1);
	strncpy(data + 3, second[indices[1]], 1);
}

#pragma opt_propagation off
void fn_17_8A54(char* output, s32 unused, const s32* selectors)
{
	char* data          = output;
	const s32* indices  = selectors;
	const char* strings = lbl_17_rodata_390;
	const char* const* first_values;
	const char* const* second_values;
	const char* second[2];
	const char* first[2];
	char number[16];
	char* next;

	strncpy(data, strings + 0x58, 8);
	sprintf(number, strings + 0x64, 4);
	strcat(data, number);
	next = data + 0x10;
	data = next;
	strncpy(data, strings + 0x6C, 2);
	first_values  = (const char* const*)(strings + 0x3C);
	second_values = (const char* const*)(strings + 0x4C);
	first[0]      = first_values[0];
	first[1]      = first_values[1];
	second[0]     = second_values[0];
	second[1]     = second_values[1];
	strncpy(data + 2, first[indices[0]], 1);
	strncpy(data + 3, second[indices[1]], 1);
	strcat(data, strings + 0x70);
}
#pragma opt_propagation on

void fn_17_8B3C(void)
{
	if (lbl_17_bss_C8 <= 0) {
		return;
	}
	lbl_17_bss_C8--;
}

const char* fn_17_8B5C(void)
{
	return lbl_17_rodata_390;
}

void fn_17_8B68(void)
{
	if (lbl_17_bss_C8 >= 1) {
		return;
	}
	lbl_17_bss_CC = lbl_17_rodata_390;
	lbl_17_bss_C8++;
}

const char sud_marker[2] = "<";
const SudTail sud_tail   = {
	"<SUDPS_>",
	"<%06X>",
	"00",
	"\n",
	"",
};
