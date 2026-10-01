#include "cri/sfxset.h"

/*
 * Reviewed CRI SFXSET boundary: all 29 functions at 0x8B98--0x8EA8 and
 * the two format tags at rodata 0x408--0x418; no private mutable state.
 * The first three helpers operate on the same Y/Cb/Cr frames consumed by
 * SFXCNV. Correlated PS2 names include SFX_SetMaxRowToYccPln,
 * sfxset_ShiftBufInfByLine and SFX_ShiftYccPtrByLine. Together with the
 * adjacent SUD/version and SFXCNV/error-string families, this supports the
 * vendor-unit boundary; no original GameCube map or source filename survives.
 * C is the reviewed vendor ABI classification, not proof of historical language.
 */

const char lbl_17_rodata_408[5] = "SFXZ";
const char lbl_17_rodata_410[8] = "SFXINFE";

void fn_17_8B98(SfxPlanes* planes, s32 width)
{
	s32 half = width / 2;
	s32 even = half * 2;

	planes->y.remaining = even;
	half                = even / 2;
	planes->u.remaining = half;
	planes->v.remaining = half;
}

void fn_17_8BC4(SfxPlane* plane, s32 rows)
{
	s32 stride    = plane->stride;
	s32 remaining = plane->remaining;
	s32 offset    = rows * stride;
	u8* address   = plane->address;

	plane->address   = address + offset;
	plane->remaining = remaining - rows;
}

void fn_17_8BE8(SfxPlanes* planes, s32 rows)
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
	return handle->unk_0x64;
}

void fn_17_8C70(SfxHandle* handle, u32 value)
{
	handle->unk_0x64 = value;
}

u32 fn_17_8C78(SfxHandle* handle)
{
	return handle->unk_0x60;
}

void fn_17_8C80(SfxHandle* handle, u32 value)
{
	handle->unk_0x60 = value;
}

u32 fn_17_8C88(SfxHandle* handle)
{
	return handle->output_mode;
}

void fn_17_8C90(SfxHandle* handle, u32 value)
{
	handle->output_mode = value;
}

void fn_17_8C98(SfxHandle* handle, s32* first, s32* second, s32* mode)
{
	fn_17_E89C(handle->frame_handle, first, second, mode);
}

void fn_17_8CBC(SfxHandle* handle, s32 first, s32 second, s32 mode)
{
	fn_17_E8B8(handle->frame_handle, first, second, mode);
}

void fn_17_8CE0(SfxHandle* handle, SfxFrameInfo* frame, s32* first, s32* second)
{
	fn_17_10664(handle->convert_handle, frame->index, first, second);
}

void fn_17_8D08(SfxHandle* handle, float* near_z, float* far_z)
{
	fn_17_EB0C(handle->convert_handle, near_z, far_z);
}

void fn_17_8D2C(SfxHandle* handle, float near_z, float far_z)
{
	fn_17_EB50(handle->convert_handle, near_z, far_z);
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
	*a = handle->unk_0x08;
	*b = handle->unk_0x0C;
}

void fn_17_8E88(SfxHandle* handle, u32 a, u32 b)
{
	handle->unk_0x08 = a;
	handle->unk_0x0C = b;
}

u32 fn_17_8E94(SfxHandle* handle)
{
	return handle->unk_0x04;
}

void fn_17_8E9C(SfxHandle* handle, u32 value)
{
	handle->unk_0x04 = value;
}

void fn_17_8EA4(void) { }
