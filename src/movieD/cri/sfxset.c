#include "types.h"

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

extern void fn_17_E89C(void*);
extern void fn_17_E8B8(void*);
extern void fn_17_10664(void*, void*);
extern void fn_17_EB0C(void*);
extern void fn_17_EB50(void*);
extern void fn_17_108A8(void*, s32, s32);
extern void* fn_80221610(void*, const char*, const char*, void*);

const char lbl_17_rodata_408[5] = "SFXZ";
const char lbl_17_rodata_410[8] = "SFXINFE";

void fn_17_8B98(SudPlanes* planes, s32 width)
{
	s32 half = width / 2;
	s32 even = half * 2;

	planes->y.remaining = even;
	half                = even / 2;
	planes->u.remaining = half;
	planes->v.remaining = half;
}

void fn_17_8BC4(SudPlane* plane, s32 rows)
{
	s32 stride    = plane->stride;
	s32 remaining = plane->remaining;
	s32 offset    = rows * stride;
	s32 address   = plane->address;

	plane->address   = address + offset;
	plane->remaining = remaining - rows;
}

void fn_17_8BE8(SudPlanes* planes, s32 rows)
{
	s32 y_rows;
	s32 chroma_rows;

	rows /= 2;
	y_rows = rows * 2;
	fn_17_8BC4(&planes->y, y_rows);
	chroma_rows = y_rows / 2;
	fn_17_8BC4(&planes->u, chroma_rows);
	fn_17_8BC4(&planes->v, chroma_rows);
}

u32 fn_17_8C68(SfxHandle* handle)
{
	return handle->unk64;
}

void fn_17_8C70(SfxHandle* handle, u32 value)
{
	handle->unk64 = value;
}

u32 fn_17_8C78(SfxHandle* handle)
{
	return handle->unk60;
}

void fn_17_8C80(SfxHandle* handle, u32 value)
{
	handle->unk60 = value;
}

u32 fn_17_8C88(SfxHandle* handle)
{
	return handle->output_mode;
}

void fn_17_8C90(SfxHandle* handle, u32 value)
{
	handle->output_mode = value;
}

void fn_17_8C98(SfxHandle* handle)
{
	fn_17_E89C(handle->frame_handle);
}

void fn_17_8CBC(SfxHandle* handle)
{
	fn_17_E8B8(handle->frame_handle);
}

void fn_17_8CE0(SfxHandle* handle, SfxFrameInfo* frame)
{
	fn_17_10664(handle->convert_handle, frame->stream_info);
}

void fn_17_8D08(SfxHandle* handle)
{
	fn_17_EB0C(handle->convert_handle);
}

void fn_17_8D2C(SfxHandle* handle)
{
	fn_17_EB50(handle->convert_handle);
}

u32 fn_17_8D50(SfxHandle* handle)
{
	return handle->out_zscale;
}

void fn_17_8D58(SfxHandle* handle, u32 value)
{
	handle->out_zscale = value;
}

u32 fn_17_8D60(SfxHandle* handle)
{
	return handle->out_zoffset;
}

void fn_17_8D68(SfxHandle* handle, u32 value)
{
	handle->out_zoffset = value;
}

void fn_17_8D70(SfxHandle* handle, s32* x, s32* y)
{
	if (handle->tag_valid != 1) {
		*x = 0;
		*y = 0;
		return;
	}
	*x = handle->tag_x;
	*y = handle->tag_y;
}

void fn_17_8DA0(SfxHandle* handle, s32 x, s32 y)
{
	s32 input[2];
	s32 output[2];
	void* convert_handle;

	convert_handle = handle->convert_handle;
	handle->tag_x  = x;
	handle->tag_y  = y;
	input[0]       = x;
	input[1]       = y;
	if (fn_80221610(input, lbl_17_rodata_408, lbl_17_rodata_410, output) == NULL) {
		fn_17_108A8(convert_handle, 0, 0);
	} else {
		fn_17_108A8(convert_handle, output[0], output[1]);
	}
	handle->tag_valid = 1;
}

u32 fn_17_8E3C(SfxHandle* handle)
{
	return handle->max_alpha;
}

void fn_17_8E44(SfxHandle* handle, u32 value)
{
	handle->max_alpha = value;
}

void* fn_17_8E4C(SfxHandle* handle, s32 index)
{
	return handle->tables[index];
}

void fn_17_8E5C(SfxHandle* handle, s32 index, void* table)
{
	handle->max_alpha     = 100;
	handle->tables[index] = table;
}

void fn_17_8E74(SfxHandle* handle, u32* a, u32* b)
{
	*a = handle->unk8;
	*b = handle->unkC;
}

void fn_17_8E88(SfxHandle* handle, u32 a, u32 b)
{
	handle->unk8 = a;
	handle->unkC = b;
}

u32 fn_17_8E94(SfxHandle* handle)
{
	return handle->unk4;
}

void fn_17_8E9C(SfxHandle* handle, u32 value)
{
	handle->unk4 = value;
}

void fn_17_8EA4(void) { }
