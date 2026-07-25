#include "types.h"

typedef struct SfxHandle {
	u8 unk0[4];
	long format;
	long width;
	long height;
	long unk10;
	long unk14;
	long unk18;
	u8 unk1C[4];
	void* decoder;
	u8 unk24[8];
	void* alpha;
	u8 unk30[4];
	long conversion;
	void* output;
} SfxHandle;

typedef struct SfxFrame {
	u8 unk0[4];
	void* pixels;
	long source_width;
	long source_height;
	u8 unk10[0x34];
	long width;
	long rows;
	long format;
	u8 unk50[0x24];
	long split;
} SfxFrame;

typedef struct SfxBuffer {
	void* pixels;
	long width;
	long rows;
	u8 unkC[0xC];
} SfxBuffer;

typedef struct SfxBufferSmall {
	void* pixels;
	long width;
	long rows;
} SfxBufferSmall;

typedef struct SfxBufferPair {
	void* input_pixels;
	long input_width;
	long input_rows;
	void* result_pixels;
	long result_width;
	long result_rows;
	u8 unk18[0x10];
} SfxBufferPair;

typedef struct SfxBufferExtended {
	SfxBufferSmall buffer;
	u8 unkC[0x10];
} SfxBufferExtended;

typedef struct SfxBufferOut {
	void* pixels;
	long width;
	long rows;
	long stride;
} SfxBufferOut;

typedef struct SfxBufferOutPadded {
	void* pixels;
	long width;
	long rows;
	long stride;
	u8 unk10[8];
} SfxBufferOutPadded;

typedef struct SfxRgbInput {
	void* first;
	void* second;
	void* third;
	long first_stride;
	long second_stride;
	long third_stride;
} SfxRgbInput;

typedef struct SfxRgbInputPadded {
	void* first;
	void* second;
	void* third;
	long first_stride;
	long second_stride;
	long third_stride;
	u8 unk18[4];
} SfxRgbInputPadded;

typedef struct SfxRgbOutput {
	void* pixels;
	long width;
	long rows;
	long stride;
	u8 unk10[8];
} SfxRgbOutput;

typedef struct SfxRgbWork {
	void* pixels;
	long width;
	long rows;
	long source_width;
	long mode;
	u8 unk14[4];
	long source_height;
} SfxRgbWork;

typedef struct SfxConvertInput {
	void* pixels;
	long width;
	long height;
	long stride;
	u8 unk10[8];
} SfxConvertInput;

typedef struct SfxConvertOutput {
	long depth;
	void* pixels;
	long width;
	long height;
	long source_width;
	long source_height;
} SfxConvertOutput;

typedef struct SfxPlanarFrame {
	u8 unk0[4];
	void* luma;
	long width;
	long height;
	u8 unk10[4];
	void* chroma_u;
	long chroma_u_stride;
	u8 unk1C[8];
	void* chroma_v;
	long chroma_v_stride;
} SfxPlanarFrame;

typedef struct SfxPlanarInput {
	void* luma;
	void* chroma_u;
	void* chroma_v;
	long width;
	long luma_stride;
	long chroma_u_stride;
	long chroma_v_stride;
} SfxPlanarInput;

typedef struct SfxPlaneSet {
	void* luma;
	void* chroma_u;
	void* chroma_v;
	long width;
	long luma_stride;
	long chroma_u_stride;
	u8 unk18[0x10];
} SfxPlaneSet;

const char lbl_17_rodata_418[]      = "E201312: sfxcnv_IsCnvUpHalf : compo is invalid.";
static const f32 sfxcnv_scale_value = 1.164f;
#define lbl_17_rodata_448 "E301282: CnvToRgb888 : compo is not support."
#define lbl_17_rodata_478 "COMPO"
#define lbl_17_rodata_480 "E301281: SFX_CnvFrmRgb888 : frmfmt is not support."
#define lbl_17_rodata_4B4 "E202281: SFX_MakeTblZ32 : zclip is not set."
#define lbl_17_rodata_4E0 "E202282: SFX_MakeTblZ16 : zclip is not set."

extern void fn_17_E338(void*, void*, const char*);
extern long fn_17_E2F4(void*, const char*);
extern long fn_17_EAE0(void*);
extern long fn_17_E2FC(SfxHandle*);
extern void fn_17_F058(void*, long, void*);
extern void fn_17_F7F8(void*, long, void*);
extern void fn_17_5F274(void*);
extern void fn_17_5F04C(void*);
extern void fn_17_E8D8(void*, long, void*);
extern void fn_17_E8FC(void*, long, void*);
extern long fn_17_E8D0(void*);
extern void fn_17_C208(SfxHandle*, SfxFrame*, void*);
extern void fn_17_D2CC(SfxHandle*, SfxFrame*, void*);
extern void fn_17_E008(SfxHandle*, SfxFrame*, void*);

extern void fn_17_A38C(SfxHandle*, SfxFrame*, long, void*);
extern void fn_17_A010(SfxHandle*, SfxFrame*, long, void*);
extern void fn_17_A188(SfxHandle*, SfxFrame*, long, void*);
extern void fn_17_5F9AC(void*, void*, void*, void*);
extern void fn_17_5EE40(SfxBuffer*, SfxBuffer*);
extern void fn_17_5EE28(SfxBufferSmall*, SfxBufferOut*);
extern void fn_17_5EE3C(SfxBufferSmall*, SfxBufferOut*, void*);
extern void fn_17_5EE44(SfxBufferSmall*, SfxBufferOut*, void*);
extern void fn_17_5EE38(SfxBufferSmall*, SfxBufferSmall*);
extern void fn_17_5EE30(SfxBufferSmall*, SfxBufferSmall*, void*);
extern void fn_17_5EE34(SfxBufferSmall*, SfxBufferSmall*, void*);
extern void fn_17_5F4E8(SfxConvertInput*, SfxConvertOutput*, void*);
extern void fn_17_5F5F8(SfxPlanarInput*, SfxConvertOutput*, void*);
extern void fn_17_5F4EC(SfxPlanarInput*, SfxConvertOutput*, void*);
extern void fn_17_5D75C(SfxPlaneSet*, void*, void*, long, long);
extern void fn_17_5DA88(SfxRgbInput*, SfxRgbWork*, void*);
extern void fn_17_5DEAC(SfxRgbInput*, SfxRgbWork*);
extern long fn_17_E318(void);
extern void fn_17_5E728(void*, SfxRgbOutput*);
extern void fn_17_5F5FC(void*, SfxRgbOutput*, void*);
extern void fn_17_5F814(void*, SfxRgbOutput*);
extern void fn_17_8E74(SfxHandle*, long*, long*);
extern void fn_17_8E88(SfxHandle*, long, long);
extern void fn_17_8B98(SfxFrame*, long);
extern void fn_17_8BE8(SfxFrame*, long);
extern long fn_17_8E94(SfxHandle*);
extern void fn_17_8E9C(SfxHandle*, long);
extern void fn_17_AD7C(SfxHandle*, SfxFrame*, void*);
extern void fn_17_ABF8(SfxHandle*, SfxFrame*, void*);
extern void fn_17_B3B4(SfxHandle*, SfxFrame*, void*);
extern long fn_17_8C78(SfxHandle*);
extern long fn_17_8C68(SfxHandle*);
extern long fn_17_10B4C(SfxHandle*);
extern long fn_17_10B20(SfxHandle*);
extern long fn_17_8C88(SfxHandle*);

extern int fn_17_9A70(SfxHandle*, int);

void fn_17_8EA8(SfxHandle* handle)
{
	switch (handle->format) {
		case 0x11:
		case 0x21:
		case 0x31:
		case 0x41:
		case 0xF1:
		case 0x101:
		case 0x1001:
			break;
		default:
			fn_17_E338(NULL, NULL, lbl_17_rodata_418);
			break;
	}
}

static inline long sfxcnv_can_convert_to_21(SfxHandle* handle)
{
	long conversion = handle->conversion;
	long result     = 1;

	if (conversion == 100) {
		result = 0;
	} else if (conversion == 0x15) {
		result = 0;
	}
	return result;
}

static inline int sfxcnv_can_convert(SfxHandle* handle, int format)
{
	int result = 1;

	if (handle->conversion == 100) {
		return 0;
	}
	if (handle->conversion == format) {
		switch (format) {
			case 0:
				break;
			case 1:
				result = 0;
				break;
			case 2:
				if (fn_17_E8D0(handle->alpha) != 1) {
					result = 0;
				}
				break;
			case 3:
				result = 0;
				break;
			case 0xB:
				break;
			case 0x15:
			case 0x16:
				result = 0;
				break;
			case 0x17:
				break;
			case 100:
				break;
			default:
				break;
		}
	}
	return result;
}

static inline long sfxcnv_is_planar(SfxHandle* handle)
{
	switch (handle->format) {
		case 0x11:
		case 0x31:
		case 0x41:
		case 0xF1:
		case 0x1001:
			return 0;
		case 0x21:
		case 0x101:
			return 1;
		default:
			fn_17_E338(NULL, NULL, lbl_17_rodata_418);
			return 0;
	}
}

static inline long sfxcnv_is_planar_error(SfxHandle* handle, const char* error)
{
	switch (handle->format) {
		case 0x11:
		case 0x31:
		case 0x41:
		case 0xF1:
		case 0x1001:
			return 0;
		case 0x21:
		case 0x101:
			return 1;
		default:
			fn_17_E338(NULL, NULL, error);
			return 0;
	}
}

static inline long sfxcnv_zero(void)
{
	return 0;
}

static inline void sfxcnv_setup_pair(SfxHandle* handle, SfxFrame* frame, void* output,
    SfxBufferSmall* input, SfxBufferOutPadded* result)
{
	input->pixels  = frame->pixels;
	input->width   = frame->width;
	input->rows    = frame->rows;
	result->pixels = output;
	result->width  = frame->width;
	result->rows   = sfxcnv_is_planar(handle) == 1 ? frame->rows / 2 : frame->rows;
	result->stride = handle->width == 0 ? frame->source_width * 4 : handle->width;
}

static inline void sfxcnv_setup_pair_cached(SfxHandle* handle, SfxFrame* frame, void* output,
    SfxBufferSmall* input, SfxBufferOutPadded* result, const char* error)
{
	input->pixels  = frame->pixels;
	input->width   = frame->width;
	input->rows    = frame->rows;
	result->pixels = output;
	result->width  = frame->width;
	if (sfxcnv_is_planar_error(handle, error) == 1) {
		result->rows = frame->rows / 2;
	} else {
		result->rows = frame->rows;
	}
	if (handle->width == 0) {
		result->stride = frame->source_width * 4;
	} else {
		result->stride = handle->width;
	}
}

void fn_17_8F2C(SfxHandle* handle, SfxFrame* frame, void* output)
{
	long can_convert;

	switch (handle->format) {
		case 0x11:
			if (fn_17_8C88(handle) != 1) {
				fn_17_8EA8(handle);
			} else {
				can_convert = sfxcnv_can_convert_to_21(handle);
				if (can_convert == 1) {
					handle->conversion = 0x15;
					fn_17_5F04C(handle->output);
				}
				fn_17_8EA8(handle);
			}
			break;
		case 0x1001:
			can_convert = sfxcnv_can_convert_to_21(handle);
			if (can_convert == 1) {
				handle->conversion = 0x15;
				fn_17_5F04C(handle->output);
			}
			fn_17_8EA8(handle);
			break;
		case 0x21:
		case 0x31:
		case 0x41:
		case 0xF1:
		case 0x101:
		default:
			fn_17_E338(handle, frame, lbl_17_rodata_448);
			break;
	}
}

#pragma dont_inline on
void fn_17_9184(SfxHandle* handle, SfxFrame* frame, void* output)
{
	long mode = *(long*)frame;

	if (handle->format == 0) {
		handle->format = fn_17_E2F4(frame, lbl_17_rodata_478);
	}
	switch (mode) {
		case 3:
			fn_17_8F2C(handle, frame, output);
			break;
		case 0:
		case 1:
		case 2:
		default:
			fn_17_E338(handle, frame, lbl_17_rodata_480);
			break;
	}
}

void fn_17_9228(SfxHandle* handle, SfxFrame* frame, void* output)
{
	long width;
	long height;
	long half_rows;
	long rows = frame->rows;

	fn_17_8E74(handle, &width, &height);
	fn_17_8E88(handle, width * 2, rows);
	frame->rows /= 2;
	half_rows = rows / 2;
	fn_17_8B98(frame, half_rows);
	fn_17_9184(handle, frame, output);
	fn_17_8E88(handle, width * 2, rows);
	fn_17_8B98(frame, rows);
	fn_17_8BE8(frame, half_rows);
	fn_17_9184(handle, frame, (u8*)output + width);
}
#pragma dont_inline off

void fn_17_92F8(SfxHandle* handle, SfxFrame* frame, void* output)
{
	fn_17_9184(handle, frame, output);
}

void fn_17_9318(SfxHandle* handle, SfxFrame* frame)
{
	if (fn_17_EAE0(handle->decoder) != 1) {
		fn_17_E338(handle, frame, lbl_17_rodata_4B4);
	} else {
		fn_17_F058(handle->decoder, frame->format, handle->output);
	}
}

void fn_17_9384(SfxHandle* handle, SfxFrame* frame)
{
	if (fn_17_EAE0(handle->decoder) != 1) {
		fn_17_E338(handle, frame, lbl_17_rodata_4E0);
	} else {
		fn_17_F7F8(handle->decoder, frame->format, handle->output);
	}
}

void fn_17_93F0(SfxHandle* handle)
{
	fn_17_5F274(handle->output);
}

void fn_17_9414(SfxHandle* handle)
{
	fn_17_5F04C(handle->output);
}

void fn_17_9438(SfxHandle* handle, SfxFrame* frame)
{
	fn_17_E8D8(handle->alpha, frame->format, handle->output);
}

void fn_17_9468(SfxHandle* handle, SfxFrame* frame)
{
	fn_17_E8FC(handle->alpha, frame->format, handle->output);
}

void fn_17_9498(u8* table)
{
	long i;

	for (i = 0; i <= 15; i++) {
		table[i] = 0;
	}
	for (i = 16; i <= 235; i++) {
		table[i] = (u8)(1.164f * (f32)(i - 16));
	}
	for (i = 236; i <= 255; i++) {
		table[i] = 255;
	}
}

static inline void sfxcnv_make_table_cached(u8* table, const char* strings)
{
	f32 scale = 1.164f;
	long i;

	for (i = 0; i <= 15; i++) {
		table[i] = 0;
	}
	for (i = 16; i <= 235; i++) {
		table[i] = (u8)(scale * (f32)(i - 16));
	}
	for (i = 236; i <= 255; i++) {
		table[i] = 255;
	}
}

#pragma no_register_coloring on
static inline void sfxcnv_zero_table(void* table, long zero)
{
	long i;

	for (i = zero; i <= 15; i++) {
		((u8*)table)[i] = (u8)zero;
	}
}

void sfxcnv_MakeTable(SfxHandle* handle)
{
	long i          = 0;
	void* table     = handle->output;
	u8* final_table = table;

	sfxcnv_zero_table(table, i);
	for (i = 16; i <= 235; i++) {
		((u8*)table)[i] = (u8)(sfxcnv_scale_value * (f32)(i - 16));
	}
	for (i = 236; i <= 255; i++) {
		final_table[i] = 255;
	}
}
#pragma no_register_coloring off

#define lbl_17_rodata_518 "E201311: sfxcnv_MakeTable : compo is not support."
#define lbl_17_rodata_54C "E201313: sfxcnv_CnvZbitToCft : zbit is invalid."
#define lbl_17_rodata_5E0 "E201192: CnvToY84C44 : compo is not support."
#define lbl_17_rodata_644 "E201182: CnvToYuv422 : compo is not support."
#define lbl_17_rodata_674 "E201183: SFX_CnvFrmYUV422 : frmfmt is not support."
#define lbl_17_rodata_6A8 "E212182: CnvToArgb8888mb : compo is not support."
#define lbl_17_rodata_798 "E201182: CnvToArgb8888 : compo is not support."

void fn_17_9A10(SfxHandle* handle, SfxFrame* frame)
{
	fn_17_F058(handle->decoder, frame->format, handle->output);
}

void fn_17_9A40(SfxHandle* handle, SfxFrame* frame)
{
	fn_17_F7F8(handle->decoder, frame->format, handle->output);
}

int fn_17_9A70(SfxHandle* handle, int format)
{
	int conversion = handle->conversion;
	int result     = 1;

	if (conversion == 100) {
		return 0;
	}
	if (conversion == format) {
		switch (format) {
			case 0:
				break;
			case 1:
				goto zero;
			case 2:
				if (fn_17_E8D0(handle->alpha) != 1) {
					result = 0;
				}
				break;
			case 3:
				goto zero;
			case 0xB:
			case 0xC:
				break;
			case 0x15:
			case 0x16:
				goto zero;
			case 100:
				break;
			default:
				break;
			zero:
				result = 0;
				break;
		}
	}
	return result;
}
void fn_17_9B24(SfxHandle* handle, SfxFrame* frame, long format)
{
	if (fn_17_9A70(handle, format) == 1) {
		handle->conversion = format;
		switch (format) {
			case 0xB:
				fn_17_9A40(handle, frame);
				break;
			case 0xD:
				fn_17_9A10(handle, frame);
				break;
			case 2:
				fn_17_9468(handle, frame);
				break;
			case 3:
				fn_17_9438(handle, frame);
				break;
			case 0x15:
				fn_17_9414(handle);
				break;
			case 0x16:
				fn_17_93F0(handle);
				break;
			case 1:
				fn_17_9498(handle->output);
				break;
			case 0:
			case 0xC:
			case 100:
			default:
				fn_17_E338(handle, frame, lbl_17_rodata_518);
				break;
		}
	}
}

long fn_17_9F94(long format)
{
	switch (format) {
		case 0x10:
			return 1;
		case 0x18:
			return 2;
		case 0x20:
			return 3;
		case 0:
		default:
			fn_17_E338(NULL, NULL, lbl_17_rodata_54C);
			return 0;
	}
}

void fn_17_A010(SfxHandle* handle, SfxFrame* frame, long depth, void* output)
{
	SfxConvertInput input;
	SfxConvertOutput result;
	long width;
	long height;

	input.pixels = frame->pixels;
	input.width  = frame->source_width;
	input.height = frame->source_height;
	input.stride = 0x40;
	if (handle->width == 0) {
		width = input.width;
	} else {
		width = handle->width;
	}
	if (handle->height == 0) {
		height = frame->source_height / 2;
	} else {
		height = handle->height;
	}
	result.depth         = fn_17_9F94(depth);
	result.pixels        = output;
	result.width         = width;
	result.height        = height;
	result.source_width  = frame->source_width;
	result.source_height = frame->source_height / 2;

	switch (depth) {
		case 0x20:
			if (sfxcnv_can_convert(handle, 0xD) == 1) {
				handle->conversion = 0xD;
				fn_17_F058(handle->decoder, frame->format, handle->output);
			}
			fn_17_5F4E8(&input, &result, handle->output);
			break;
		case 0x10:
		default:
			break;
	}
}

void fn_17_A188(SfxHandle* handle, SfxFrame* frame, long depth, void* output)
{
	SfxPlanarInput input;
	SfxConvertOutput result;
	SfxPlanarFrame* planar = (SfxPlanarFrame*)frame;
	long width;
	long height;
	long offset;

	offset     = (planar->width * planar->height) / 2;
	input.luma = (u8*)planar->luma + offset;
	offset /= 2;
	input.chroma_u        = offset + (u8*)planar->chroma_u;
	input.chroma_v        = offset + (u8*)planar->chroma_v;
	input.width           = planar->width;
	input.luma_stride     = planar->chroma_u_stride;
	input.chroma_u_stride = planar->chroma_v_stride;
	input.chroma_v_stride = 0;

	if (handle->width == 0) {
		width = input.width;
	} else {
		width = handle->width;
	}
	if (handle->height == 0) {
		height = planar->height / 2;
	} else {
		height = handle->height;
	}
	result.depth         = fn_17_9F94(depth);
	result.pixels        = output;
	result.width         = width;
	result.height        = height;
	result.source_width  = planar->width;
	result.source_height = planar->height / 2;

	switch (depth) {
		case 0x10:
			if (sfxcnv_can_convert(handle, 0xB) == 1) {
				handle->conversion = 0xB;
				fn_17_F7F8(handle->decoder, frame->format, handle->output);
			}
			fn_17_5F5F8(&input, &result, handle->output);
			break;
		case 0x20:
			if (sfxcnv_can_convert(handle, 0xD) == 1) {
				handle->conversion = 0xD;
				fn_17_F058(handle->decoder, frame->format, handle->output);
			}
			fn_17_5F4EC(&input, &result, handle->output);
			break;
		default:
			break;
	}
}

#pragma dont_inline on
void fn_17_A38C(SfxHandle* handle, SfxFrame* frame, long depth, void* output)
{
	const char* strings = lbl_17_rodata_418;

	if (handle->format == 0) {
		handle->format = fn_17_E2F4(frame, "COMPO");
	}
	if (fn_17_EAE0(handle->decoder) != 1) {
		fn_17_E338(handle, frame, "E201315: sfxcnv_CnvFrmZcmn : zclip is not set.");
	} else {
		switch (*(long*)frame) {
			case 3:
				fn_17_A188(handle, frame, depth, output);
				break;
			case 2:
				fn_17_A010(handle, frame, depth, output);
				break;
			case 0:
			case 1:
			default:
				fn_17_E338(handle, frame, "E201191: SFX_CnvFrmZcmn : frmfmt is not support.");
				break;
		}
	}
}
#pragma dont_inline off

#pragma dont_inline on
void fn_17_A464(void* arg0, void* arg1, void* arg2)
{
	fn_17_A38C(arg0, arg1, 0x20, arg2);
}

void fn_17_A48C(void* arg0, void* arg1, void* arg2)
{
	fn_17_A38C(arg0, arg1, 0x18, arg2);
}

void fn_17_A4B4(void* arg0, void* arg1, void* arg2)
{
	fn_17_A38C(arg0, arg1, 0x10, arg2);
}
#pragma dont_inline off

void fn_17_A4DC(SfxHandle* handle, SfxFrame* frame, void* arg2, void* arg3)
{
	SfxPlanarFrame* planar = (SfxPlanarFrame*)frame;
	SfxPlaneSet planes;
	long width;
	long height;

	planes.luma            = planar->luma;
	planes.chroma_u        = planar->chroma_u;
	planes.chroma_v        = planar->chroma_v;
	planes.width           = planar->width;
	planes.luma_stride     = planar->chroma_u_stride;
	planes.chroma_u_stride = planar->chroma_v_stride;

	if (handle->width == 0) {
		width = planes.width;
	} else {
		width = handle->width;
	}
	if (handle->height == 0) {
		height = planar->height;
	} else {
		height = handle->height;
	}
	if (sfxcnv_is_planar(handle) == 1) {
		height /= 2;
	}
	fn_17_5D75C(&planes, arg2, arg3, width, height);
}

static inline void sfxcnv_convert_planar(
    SfxHandle* handle, SfxFrame* frame, void* arg2, void* arg3, const char* error)
{
	SfxPlanarFrame* planar = (SfxPlanarFrame*)frame;
	SfxPlaneSet planes;
	long width;
	long height;

	switch (handle->format) {
		case 0x11:
		case 0x101:
			planes.luma            = planar->luma;
			planes.chroma_u        = planar->chroma_u;
			planes.chroma_v        = planar->chroma_v;
			planes.width           = planar->width;
			planes.luma_stride     = planar->chroma_u_stride;
			planes.chroma_u_stride = planar->chroma_v_stride;

			if (handle->width == 0) {
				width = planes.width;
			} else {
				width = handle->width;
			}
			height = handle->height;
			if (height == 0) {
				height = planar->height;
			}
			if (sfxcnv_is_planar(handle) == 1) {
				height /= 2;
			}
			fn_17_5D75C(&planes, arg2, arg3, width, height);
			break;
		case 0x21:
		case 0x31:
		case 0x41:
		case 0xF1:
		case 0x1001:
		default:
			fn_17_E338(handle, frame, error);
			break;
	}
}

void fn_17_A62C(SfxHandle* handle, SfxFrame* frame, void* arg2, void* arg3)
{
	sfxcnv_convert_planar(handle, frame, arg2, arg3, lbl_17_rodata_5E0);
}

void fn_17_A7D8(SfxHandle* handle, SfxFrame* frame, void* arg2, void* arg3)
{
	const char* strings = lbl_17_rodata_418;
	long mode           = *(long*)frame;

	if (handle->format == 0) {
		handle->format = fn_17_E2F4(frame, "COMPO");
	}
	switch (mode) {
		case 3:
			sfxcnv_convert_planar(
			    handle, frame, arg2, arg3, "E201192: CnvToY84C44 : compo is not support.");
			break;
		case 0:
		case 1:
		case 2:
		default:
			fn_17_E338(handle, frame, "E201193: SFX_CnvFrmY84C44 : frmfmt is not support.");
			break;
	}
}

#pragma opt_propagation off
void fn_17_A9C0(SfxHandle* handle, SfxFrame* frame, void* output, long field)
{
	SfxPlanarFrame* planar = (SfxPlanarFrame*)frame;
	SfxRgbInput input;
	SfxRgbWork result;
	long mode = sfxcnv_zero();
	long use_alpha;
	void* alpha;

	input.first         = planar->luma;
	input.second        = planar->chroma_u;
	input.third         = planar->chroma_v;
	input.first_stride  = planar->width;
	input.second_stride = planar->chroma_u_stride;
	input.third_stride  = planar->chroma_v_stride;

	result.pixels = output;
	result.width  = frame->width;
	if (sfxcnv_is_planar(handle) == 1) {
		result.rows = frame->rows / 2;
	} else {
		result.rows = frame->rows;
	}
	if (handle->width == 0) {
		result.source_width = planar->width;
	} else {
		result.source_width = handle->width;
	}
	if (handle->height == 0) {
		result.source_height = planar->height;
	} else {
		result.source_height = handle->height;
	}

	switch (fn_17_8C78(handle)) {
		case -1:
			use_alpha = 0;
			if (fn_17_10B4C(handle) == 1 && fn_17_10B20(handle) == 1 && fn_17_8C68(handle) == 0) {
				use_alpha = 1;
			}
			break;
		case 0:
			use_alpha = 0;
			break;
		case 1:
			use_alpha = 1;
			break;
		default:
			use_alpha = 0;
			break;
	}
	if (use_alpha == 1) {
		result.mode = 2;
	} else {
		result.mode = 1;
	}

	if (field == 1) {
		alpha = handle->output;
		if (mode != 1) {
			fn_17_5DA88(&input, &result, alpha);
		}
	} else if (mode != 1) {
		fn_17_5DEAC(&input, &result);
	}
}
#pragma opt_propagation on

void fn_17_ABF8(SfxHandle* handle, SfxFrame* frame, void* output)
{
	int can_convert;

	switch (handle->format) {
		case 0x11:
			if (fn_17_8C88(handle) != 1) {
				fn_17_A9C0(handle, frame, output, 0);
			} else {
				can_convert = sfxcnv_can_convert(handle, 0x16);
				if (can_convert == 1) {
					handle->conversion = 0x16;
					fn_17_5F274(handle->output);
				}
				fn_17_A9C0(handle, frame, output, 1);
			}
			break;
		case 0x101:
			fn_17_A9C0(handle, frame, output, 0);
			break;
		case 0x1001:
			can_convert = sfxcnv_can_convert(handle, 0x15);
			if (can_convert == 1) {
				handle->conversion = 0x15;
				fn_17_5F04C(handle->output);
			}
			fn_17_A9C0(handle, frame, output, 1);
			break;
		case 0x21:
		case 0x31:
		case 0x41:
		case 0xF1:
		default:
			fn_17_E338(handle, frame, lbl_17_rodata_644);
			break;
	}
}

#pragma dont_inline on
void fn_17_AD7C(SfxHandle* handle, SfxFrame* frame, void* output)
{
	long mode = *(long*)frame;

	if (handle->format == 0) {
		handle->format = fn_17_E2F4(frame, lbl_17_rodata_478);
	}
	switch (mode) {
		case 3:
			fn_17_ABF8(handle, frame, output);
			break;
		case 0:
		case 1:
		case 2:
		default:
			fn_17_E338(handle, frame, lbl_17_rodata_674);
			break;
	}
}
#pragma dont_inline off

#pragma dont_inline on
void fn_17_AE20(SfxHandle* handle, SfxFrame* frame, void* output)
{
	long unit_width;
	long rows = frame->rows;

	frame->rows /= 2;
	fn_17_8BE8(frame, rows / 2);
	unit_width = fn_17_8E94(handle);
	fn_17_8E9C(handle, 0x11);
	fn_17_AD7C(handle, frame, output);
	fn_17_8E9C(handle, unit_width);
}

void fn_17_AEC0(SfxHandle* handle, SfxFrame* frame, void* output)
{
	long unit_width;

	frame->rows /= 2;
	unit_width = fn_17_8E94(handle);
	fn_17_8E9C(handle, 0x11);
	fn_17_AD7C(handle, frame, output);
	fn_17_8E9C(handle, unit_width);
}
#pragma dont_inline off

#pragma dont_inline on
void fn_17_AF50(SfxHandle* handle, SfxFrame* frame, void* output)
{
	long width;
	long height;
	long half_rows;
	long rows = frame->rows;

	fn_17_8E74(handle, &width, &height);
	frame->rows /= 2;
	half_rows = rows / 2;
	fn_17_8B98(frame, half_rows);
	fn_17_AD7C(handle, frame, output);
	fn_17_8B98(frame, rows);
	fn_17_8BE8(frame, half_rows);
	fn_17_AD7C(handle, frame, (u8*)output + width * 2);
}
#pragma dont_inline off

void fn_17_AFFC(SfxHandle* handle, SfxFrame* frame, void* output)
{
	long use_alpha;

	if (fn_17_E2FC(handle) == 0) {
		switch (fn_17_8C78(handle)) {
			case -1:
				use_alpha = 0;
				if (fn_17_10B4C(handle) == 1 && fn_17_10B20(handle) == 1
				    && fn_17_8C68(handle) == 0) {
					use_alpha = 1;
				}
				break;
			case 0:
				use_alpha = 0;
				break;
			case 1:
				use_alpha = 1;
				break;
			default:
				use_alpha = 0;
				break;
		}
		if (use_alpha == 1) {
			fn_17_AF50(handle, frame, output);
			return;
		}
	}
	fn_17_AD7C(handle, frame, output);
}

void fn_17_B0F8(SfxHandle* handle, SfxFrame* frame, void* output)
{
	SfxBufferSmall input;
	SfxBufferExtended result;

	input.pixels         = frame->pixels;
	input.width          = frame->width;
	input.rows           = frame->rows;
	result.buffer.pixels = output;
	result.buffer.width  = frame->width;
	result.buffer.rows   = frame->rows / 2;
	fn_17_5EE38(&input, &result.buffer);

	input.pixels         = frame->pixels;
	input.width          = frame->width;
	input.rows           = frame->rows;
	result.buffer.pixels = output;
	result.buffer.width  = frame->width;
	result.buffer.rows   = frame->rows;
	fn_17_5EE30(&input, (SfxBufferSmall*)(u8*)&result, handle->output);
}

void fn_17_B1A8(SfxHandle* handle, SfxFrame* frame, void* output, long mode)
{
	SfxBufferSmall input;
	SfxBufferExtended result;

	input.pixels         = frame->pixels;
	input.width          = frame->width;
	input.rows           = frame->rows;
	result.buffer.pixels = output;
	result.buffer.width  = frame->width;
	if (sfxcnv_is_planar(handle) == 1) {
		result.buffer.rows = frame->rows / 2;
	} else {
		result.buffer.rows = frame->rows;
	}
	if (handle->width == 0) {
		*(long*)result.unkC = frame->source_width * 4;
	} else {
		*(long*)result.unkC = handle->width;
	}
	if (mode == 1) {
		fn_17_5EE34(&input, &result.buffer, handle->output);
	} else {
		fn_17_5EE38(&input, &result.buffer);
	}
}

void fn_17_B2F8(SfxHandle* handle, SfxFrame* frame, void* output)
{
	SfxBuffer result;
	SfxBuffer input;

	switch (handle->format) {
		case 0x21:
			input.pixels  = frame->pixels;
			input.width   = frame->width;
			input.rows    = frame->rows;
			result.pixels = output;
			result.width  = frame->width;
			result.rows   = frame->rows;
			fn_17_5EE40(&input, &result);
			break;
		case 0x11:
			break;
		case 0x31:
		case 0x41:
		case 0xF1:
		case 0x101:
		case 0x1001:
		default:
			fn_17_E338(handle, frame, lbl_17_rodata_6A8);
			break;
	}
}

void fn_17_B3B4(SfxHandle* handle, SfxFrame* frame, void* output)
{
	SfxBufferSmall in0, in1, in2, in3, in4, in5;
	SfxBufferOutPadded out0, out1, out2, out3, out4, out5;

	switch (handle->format) {
		case 0x11:
			if (fn_17_8C88(handle) != 1) {
				sfxcnv_setup_pair_cached(handle, frame, output, &in0, &out0, lbl_17_rodata_418);
				fn_17_5EE38(&in0, (SfxBufferSmall*)&out0);
			} else {
				fn_17_9B24(handle, frame, 0x15);
				sfxcnv_setup_pair_cached(handle, frame, output, &in1, &out1, lbl_17_rodata_418);
				fn_17_5EE34(&in1, (SfxBufferSmall*)&out1, handle->output);
			}
			break;
		case 0x1001:
			fn_17_9B24(handle, frame, 0x15);
			sfxcnv_setup_pair_cached(handle, frame, output, &in2, &out2, lbl_17_rodata_418);
			fn_17_5EE34(&in2, (SfxBufferSmall*)&out2, handle->output);
			break;
		case 0x31:
			fn_17_9B24(handle, frame, 2);
			sfxcnv_setup_pair_cached(handle, frame, output, &in3, &out3, lbl_17_rodata_418);
			fn_17_5EE34(&in3, (SfxBufferSmall*)&out3, handle->output);
			break;
		case 0x41:
			fn_17_9B24(handle, frame, 3);
			sfxcnv_setup_pair_cached(handle, frame, output, &in4, &out4, lbl_17_rodata_418);
			fn_17_5EE34(&in4, (SfxBufferSmall*)&out4, handle->output);
			break;
		case 0x21:
			if (fn_17_9A70(handle, 1) == 1) {
				handle->conversion = 1;
				sfxcnv_make_table_cached(handle->output, lbl_17_rodata_418);
			}
			in5.pixels  = frame->pixels;
			in5.width   = frame->width;
			in5.rows    = frame->rows;
			out5.pixels = output;
			out5.width  = frame->width;
			out5.rows   = frame->rows / 2;
			fn_17_5EE38(&in5, (SfxBufferSmall*)&out5);
			in5.pixels  = frame->pixels;
			in5.width   = frame->width;
			in5.rows    = frame->rows;
			out5.pixels = output;
			out5.width  = frame->width;
			out5.rows   = frame->rows;
			fn_17_5EE30(&in5, (SfxBufferSmall*)&out5, handle->output);
			break;
		case 0xF1:
		case 0x101:
		default:
			fn_17_E338(handle, frame,
			    "E212173: sfxcnv_CnvFrmYcc420mbToArgb8888mb() : compo is not support.");
			break;
	}
}

void fn_17_BD80(SfxHandle* handle, SfxFrame* frame, void* output)
{
	const char* strings = lbl_17_rodata_418;
	SfxBuffer result;
	SfxBuffer input;
	long mode;

	fn_17_E338(handle, frame, "E212171: SFX_CnvFrmARGB8888Mb : function is not support.");
	mode = *(long*)frame;
	if (handle->format == 0) {
		handle->format = fn_17_E2F4(frame, "COMPO");
	}
	switch (mode) {
		case 1:
			fn_17_B3B4(handle, frame, output);
			break;
		case 2:
			switch (handle->format) {
				case 0x11:
					break;
				case 0x21:
					input.pixels  = frame->pixels;
					input.width   = frame->width;
					input.rows    = frame->rows;
					result.pixels = output;
					result.width  = frame->width;
					result.rows   = frame->rows;
					fn_17_5EE40(&input, &result);
					break;
				case 0x31:
				case 0x41:
				case 0xF1:
				case 0x101:
				case 0x1001:
				default:
					fn_17_E338(handle, frame, "E212182: CnvToArgb8888mb : compo is not support.");
					break;
			}
			break;
		case 3:
		default:
			fn_17_E338(handle, frame, "E212172: SFX_CnvFrmMbARGB8888 : frmfmt is not support.");
			break;
	}
}

void fn_17_BEC0(void* unused, SfxFrame* frame, void* output)
{
	SfxBuffer input;
	SfxBuffer result;

	input.pixels  = frame->pixels;
	input.width   = frame->width;
	input.rows    = frame->rows;
	result.pixels = output;
	result.width  = frame->width;
	result.rows   = frame->rows;
	fn_17_5EE40(&input, &result);
}

void fn_17_BF0C(SfxHandle* handle, SfxFrame* frame, void* output)
{
	SfxBuffer result;
	SfxBuffer input;

	switch (handle->format) {
		case 0x21:
			input.pixels  = frame->pixels;
			input.width   = frame->width;
			input.rows    = frame->rows;
			result.pixels = output;
			result.width  = frame->width;
			result.rows   = frame->rows;
			fn_17_5EE40(&input, &result);
			break;
		case 0x11:
			break;
		case 0x31:
		case 0x41:
		case 0xF1:
		case 0x101:
		case 0x1001:
		default:
			fn_17_E338(handle, frame, lbl_17_rodata_798);
			break;
	}
}

void fn_17_BFC8(SfxHandle* handle, SfxFrame* frame, void* pixels)
{
	SfxBufferOut output;
	SfxBufferSmall input;

	input.pixels  = frame->pixels;
	input.width   = frame->width;
	input.rows    = frame->rows;
	output.pixels = pixels;
	output.width  = frame->width;
	output.rows   = frame->rows / 2;
	if (handle->width == 0) {
		output.stride = frame->source_width * 4;
	} else {
		output.stride = handle->width;
	}
	fn_17_5EE28(&input, &output);

	input.pixels  = frame->pixels;
	input.width   = frame->width;
	input.rows    = frame->rows;
	output.pixels = pixels;
	output.width  = frame->width;
	output.rows   = frame->rows;
	if (handle->width == 0) {
		output.stride = frame->source_width * 4;
	} else {
		output.stride = handle->width;
	}
	fn_17_5EE3C(&input, &output, handle->output);
}

void fn_17_C0B8(SfxHandle* handle, SfxFrame* frame, void* pixels, long mode)
{
	SfxBufferOut output;
	SfxBufferSmall input;

	input.pixels  = frame->pixels;
	input.width   = frame->width;
	input.rows    = frame->rows;
	output.pixels = pixels;
	output.width  = frame->width;
	if (sfxcnv_is_planar(handle) == 1) {
		output.rows = frame->rows / 2;
	} else {
		output.rows = frame->rows;
	}
	if (handle->width == 0) {
		output.stride = frame->source_width * 4;
	} else {
		output.stride = handle->width;
	}
	if (mode == 1) {
		fn_17_5EE44(&input, &output, handle->output);
	} else {
		fn_17_5EE28(&input, &output);
	}
}

void fn_17_C208(SfxHandle* handle, SfxFrame* frame, void* pixels)
{
	switch (handle->format) {
		case 0x11:
			if (fn_17_8C88(handle) != 1) {
				SfxBufferSmall input;
				SfxBufferOutPadded result;
				input.pixels  = frame->pixels;
				input.width   = frame->width;
				input.rows    = frame->rows;
				result.pixels = pixels;
				result.width  = frame->width;
				if (sfxcnv_is_planar_error(handle, lbl_17_rodata_418) == 1)
					result.rows = frame->rows / 2;
				else
					result.rows = frame->rows;
				if (handle->width == 0) {
					result.stride = frame->source_width * 4;
				} else {
					result.stride = handle->width;
				}
				fn_17_5EE28(&input, (SfxBufferOut*)&result);
			} else {
				SfxBufferSmall input;
				SfxBufferOutPadded result;
				if (sfxcnv_can_convert_to_21(handle) == 1) {
					handle->conversion = 0x15;
					fn_17_5F04C(handle->output);
				}
				input.pixels  = frame->pixels;
				input.width   = frame->width;
				input.rows    = frame->rows;
				result.pixels = pixels;
				result.width  = frame->width;
				if (sfxcnv_is_planar_error(handle, lbl_17_rodata_418) == 1)
					result.rows = frame->rows / 2;
				else
					result.rows = frame->rows;
				if (handle->width == 0) {
					result.stride = frame->source_width * 4;
				} else {
					result.stride = handle->width;
				}
				fn_17_5EE44(&input, (SfxBufferOut*)&result, handle->output);
			}
			break;
		case 0x1001: {
			SfxBufferSmall input;
			SfxBufferOutPadded result;
			if (sfxcnv_can_convert_to_21(handle) == 1) {
				handle->conversion = 0x15;
				fn_17_5F04C(handle->output);
			}
			input.pixels  = frame->pixels;
			input.width   = frame->width;
			input.rows    = frame->rows;
			result.pixels = pixels;
			result.width  = frame->width;
			if (sfxcnv_is_planar_error(handle, lbl_17_rodata_418) == 1)
				result.rows = frame->rows / 2;
			else
				result.rows = frame->rows;
			if (handle->width == 0) {
				result.stride = frame->source_width * 4;
			} else {
				result.stride = handle->width;
			}
			fn_17_5EE44(&input, (SfxBufferOut*)&result, handle->output);
			break;
		}
		case 0x31: {
			SfxBufferSmall input;
			SfxBufferOutPadded result;
			if (sfxcnv_can_convert(handle, 2) == 1) {
				handle->conversion = 2;
				fn_17_E8FC(handle->alpha, frame->format, handle->output);
			}
			input.pixels  = frame->pixels;
			input.width   = frame->width;
			input.rows    = frame->rows;
			result.pixels = pixels;
			result.width  = frame->width;
			if (sfxcnv_is_planar_error(handle, lbl_17_rodata_418) == 1)
				result.rows = frame->rows / 2;
			else
				result.rows = frame->rows;
			if (handle->width == 0) {
				result.stride = frame->source_width * 4;
			} else {
				result.stride = handle->width;
			}
			fn_17_5EE44(&input, (SfxBufferOut*)&result, handle->output);
			break;
		}
		case 0x41: {
			SfxBufferSmall input;
			SfxBufferOutPadded result;
			if (sfxcnv_can_convert(handle, 3) == 1) {
				handle->conversion = 3;
				fn_17_E8D8(handle->alpha, frame->format, handle->output);
			}
			input.pixels  = frame->pixels;
			input.width   = frame->width;
			input.rows    = frame->rows;
			result.pixels = pixels;
			result.width  = frame->width;
			if (sfxcnv_is_planar_error(handle, lbl_17_rodata_418) == 1)
				result.rows = frame->rows / 2;
			else
				result.rows = frame->rows;
			if (handle->width == 0) {
				result.stride = frame->source_width * 4;
			} else {
				result.stride = handle->width;
			}
			fn_17_5EE44(&input, (SfxBufferOut*)&result, handle->output);
			break;
		}
		case 0x21: {
			SfxBufferSmall input;
			SfxBufferOutPadded result;
			if (fn_17_9A70(handle, 1) == 1) {
				handle->conversion = 1;
				sfxcnv_make_table_cached(handle->output, lbl_17_rodata_418);
			}
			input.pixels  = frame->pixels;
			input.width   = frame->width;
			input.rows    = frame->rows;
			result.pixels = pixels;
			result.width  = frame->width;
			result.rows   = frame->rows / 2;
			if (handle->width == 0) {
				result.stride = frame->source_width * 4;
			} else {
				result.stride = handle->width;
			}
			fn_17_5EE28(&input, (SfxBufferOut*)&result);
			input.pixels  = frame->pixels;
			input.width   = frame->width;
			input.rows    = frame->rows;
			result.pixels = pixels;
			result.width  = frame->width;
			result.rows   = frame->rows;
			if (handle->width == 0) {
				result.stride = frame->source_width * 4;
			} else {
				result.stride = handle->width;
			}
			fn_17_5EE3C(&input, (SfxBufferOut*)&result, handle->output);
			break;
		}
		case 0xF1:
		case 0x101:
		default:
			fn_17_E338(handle, frame, "E201182: CnvToArgb8888 : compo is not support.");
			break;
	}
}

void fn_17_CC14(SfxHandle* handle, SfxFrame* frame, void* output)
{
	long unit_width;
	long rows = frame->rows;

	frame->rows /= 2;
	fn_17_8BE8(frame, rows / 2);
	unit_width = fn_17_8E94(handle);
	fn_17_8E9C(handle, 0x11);
	fn_17_E008(handle, frame, output);
	fn_17_8E9C(handle, unit_width);
}

void fn_17_CCB4(SfxHandle* handle, SfxFrame* frame, void* output)
{
	long unit_width;

	frame->rows /= 2;
	unit_width = fn_17_8E94(handle);
	fn_17_8E9C(handle, 0x11);
	fn_17_E008(handle, frame, output);
	fn_17_8E9C(handle, unit_width);
}

#pragma opt_propagation off
void fn_17_CD44(SfxHandle* handle, SfxFrame* frame, void* pixels)
{
	SfxRgbInputPadded second_input;
	SfxRgbOutput second_output;
	SfxRgbOutput first_output;
	SfxRgbInputPadded first_input;
	long mode;
	long plane_size;

	first_input.first         = frame->pixels;
	first_input.second        = ((SfxPlanarFrame*)frame)->chroma_u;
	first_input.third         = ((SfxPlanarFrame*)frame)->chroma_v;
	first_input.first_stride  = frame->source_width;
	first_input.second_stride = ((SfxPlanarFrame*)frame)->chroma_u_stride;
	first_input.third_stride  = ((SfxPlanarFrame*)frame)->chroma_v_stride;

	first_output.pixels = pixels;
	first_output.width  = frame->width;
	switch (handle->format) {
		case 0x11:
		case 0x31:
		case 0x41:
		case 0xF1:
		case 0x1001:
			mode = 0;
			break;
		case 0x21:
		case 0x101:
			mode = 1;
			break;
		default:
			fn_17_E338(NULL, NULL, lbl_17_rodata_418);
			mode = 0;
			break;
	}
	if (mode == 1) {
		first_output.rows = frame->rows / 2;
	} else {
		first_output.rows = frame->rows;
	}
	if (handle->width == 0) {
		first_output.stride = frame->source_width * 4;
	} else {
		first_output.stride = handle->width;
	}

	mode = 0;
	if (frame->split == 1) {
		if (mode != 1) {
			fn_17_5E728(&first_input, &first_output);
		}
	} else if (mode != 1) {
		fn_17_5E728(&first_input, &first_output);
	}

	plane_size                 = frame->source_width * frame->source_height / 2;
	second_input.first         = (u8*)frame->pixels + plane_size;
	second_input.second        = (u8*)((SfxPlanarFrame*)frame)->chroma_u + plane_size / 2;
	second_input.third         = (u8*)((SfxPlanarFrame*)frame)->chroma_v + plane_size / 2;
	second_input.first_stride  = frame->source_width;
	second_input.second_stride = ((SfxPlanarFrame*)frame)->chroma_u_stride;
	second_input.third_stride  = ((SfxPlanarFrame*)frame)->chroma_v_stride;

	second_output.pixels = pixels;
	second_output.width  = frame->width;
	second_output.rows   = frame->rows / 2;
	if (handle->width == 0) {
		second_output.stride = frame->source_width * 4;
	} else {
		second_output.stride = handle->width;
	}

	if (fn_17_E318() == 1) {
		fn_17_5F5FC(&second_input, &second_output, handle->output);
	} else {
		fn_17_5F814(&second_input, &second_output);
	}
}
#pragma opt_propagation on

void fn_17_CF88(void* unused, void** values, void* output)
{
	fn_17_5F9AC(values[1], output, values[2], values[3]);
}

long fn_17_CFBC(SfxHandle* handle)
{
	switch (handle->format) {
		case 0x11:
		case 0x31:
		case 0x41:
		case 0xF1:
		case 0x1001:
			return 0;
		case 0x21:
		case 0x101:
			return 1;
		default:
			fn_17_E338(NULL, NULL, lbl_17_rodata_418);
			return 0;
	}
}

#pragma opt_propagation off

void fn_17_D058(
    void* unused, SfxFrame* frame, SfxRgbInput* input, SfxRgbOutput* output, void* alpha)
{
	long mode = 0;

	if (frame->split == 1) {
		if (alpha != NULL) {
			if (mode != 1) {
				fn_17_5E158(input, output, alpha);
			}
		} else if (mode != 1) {
			fn_17_5E728(input, output);
		}
	} else {
		if (alpha != NULL) {
			if (mode != 1) {
				fn_17_5E158(input, output, alpha);
			}
		} else if (mode != 1) {
			fn_17_5E728(input, output);
		}
	}
}

void fn_17_D0F8(SfxHandle* handle, SfxFrame* frame, void* pixels, long use_alpha)
{
	SfxRgbInput input;
	SfxRgbOutput output;
	void* alpha;

	input.first         = frame->pixels;
	input.second        = ((SfxPlanarFrame*)frame)->chroma_u;
	input.third         = ((SfxPlanarFrame*)frame)->chroma_v;
	input.first_stride  = frame->source_width;
	input.second_stride = ((SfxPlanarFrame*)frame)->chroma_u_stride;
	input.third_stride  = ((SfxPlanarFrame*)frame)->chroma_v_stride;
	output.pixels       = pixels;
	output.width        = frame->width;
	if (fn_17_CFBC(handle) == 1) {
		output.rows = frame->rows / 2;
	} else {
		output.rows = frame->rows;
	}
	if (handle->width == 0) {
		output.stride = frame->source_width * 4;
	} else {
		output.stride = handle->width;
	}
	if (use_alpha == 1) {
		alpha = handle->output;
	} else {
		alpha = NULL;
	}
	fn_17_D058(handle, frame, &input, &output, alpha);
}

static inline void sfxcnv_d0f8_cached(
    SfxHandle* handle, SfxFrame* frame, void* pixels, long use_alpha, const char* error)
{
	SfxRgbInputPadded input;
	SfxRgbOutput output;
	void* alpha;

	input.first         = frame->pixels;
	input.second        = ((SfxPlanarFrame*)frame)->chroma_u;
	input.third         = ((SfxPlanarFrame*)frame)->chroma_v;
	input.first_stride  = frame->source_width;
	input.second_stride = ((SfxPlanarFrame*)frame)->chroma_u_stride;
	input.third_stride  = ((SfxPlanarFrame*)frame)->chroma_v_stride;
	output.pixels       = pixels;
	output.width        = frame->width;
	if (sfxcnv_is_planar_error(handle, error) == 1) {
		output.rows = frame->rows / 2;
	} else {
		output.rows = frame->rows;
	}
	if (handle->width == 0) {
		output.stride = frame->source_width * 4;
	} else {
		output.stride = handle->width;
	}
	if (use_alpha == 1) {
		alpha = handle->output;
	} else {
		alpha = NULL;
	}
	fn_17_D058(handle, frame, (SfxRgbInput*)&input, &output, alpha);
}
#pragma opt_propagation on

void fn_17_D2CC(SfxHandle* handle, SfxFrame* frame, void* output)
{
	switch (handle->format) {
		case 0x11:
			if (fn_17_8C88(handle) != 1) {
				sfxcnv_d0f8_cached(handle, frame, output, 0, lbl_17_rodata_418);
			} else {
				fn_17_9B24(handle, frame, 0x15);
				sfxcnv_d0f8_cached(handle, frame, output, 1, lbl_17_rodata_418);
			}
			break;
		case 0x101:
			sfxcnv_d0f8_cached(handle, frame, output, 0, lbl_17_rodata_418);
			break;
		case 0xF1:
			fn_17_CF88(handle, (void**)frame, output);
			break;
		case 0x21:
			fn_17_9B24(handle, frame, 1);
			fn_17_CD44(handle, frame, output);
			break;
		case 0x31:
			fn_17_9B24(handle, frame, 2);
			sfxcnv_d0f8_cached(handle, frame, output, 1, lbl_17_rodata_418);
			break;
		case 0x41:
			fn_17_9B24(handle, frame, 3);
			sfxcnv_d0f8_cached(handle, frame, output, 1, lbl_17_rodata_418);
			break;
		case 0x1001:
			fn_17_9B24(handle, frame, 0x15);
			sfxcnv_d0f8_cached(handle, frame, output, 1, lbl_17_rodata_418);
			break;
		default:
			fn_17_E338(handle, frame, "E201182: CnvToArgb8888 : compo is not support.");
			break;
	}
}

void fn_17_E008(SfxHandle* handle, SfxFrame* frame, void* output)
{
	const char* strings = lbl_17_rodata_418;
	SfxBuffer output_buffer;
	SfxBuffer input_buffer;
	long mode = *(long*)frame;

	if (handle->format == 0) {
		handle->format = fn_17_E2F4(frame, "COMPO");
	}
	switch (mode) {
		case 3:
			fn_17_D2CC(handle, frame, output);
			break;
		case 1:
			fn_17_C208(handle, frame, output);
			break;
		case 2:
			switch (handle->format) {
				case 0x11:
					break;
				case 0x21:
					input_buffer.pixels  = frame->pixels;
					input_buffer.width   = frame->width;
					input_buffer.rows    = frame->rows;
					output_buffer.pixels = output;
					output_buffer.width  = frame->width;
					output_buffer.rows   = frame->rows;
					fn_17_5EE40(&input_buffer, &output_buffer);
					break;
				case 0x31:
				case 0x41:
				case 0xF1:
				case 0x101:
				case 0x1001:
				default:
					fn_17_E338(handle, frame, "E201182: CnvToArgb8888 : compo is not support.");
					break;
			}
			break;
		default:
			fn_17_E338(handle, frame, "E201181: SFX_CnvFrmArgb8888 : frmfmt is not support.\0\0\0");
			break;
	}
}

#pragma dont_inline on
void fn_17_E158(SfxHandle* handle, SfxFrame* frame, void* output)
{
	long width;
	long height;
	long half_rows;
	long rows = frame->rows;

	fn_17_8E74(handle, &width, &height);
	fn_17_8E88(handle, width * 2, rows);
	frame->rows /= 2;
	half_rows = rows / 2;
	fn_17_8B98(frame, half_rows);
	fn_17_E008(handle, frame, output);
	fn_17_8E88(handle, width * 2, rows);
	fn_17_8B98(frame, rows);
	fn_17_8BE8(frame, half_rows);
	fn_17_E008(handle, frame, (u8*)output + width);
}

long fn_17_E228(SfxHandle* handle)
{
	long result;

	switch (fn_17_8C78(handle)) {
		case -1:
			result = 0;
			if (fn_17_10B4C(handle) == 1 && fn_17_10B20(handle) == 1 && fn_17_8C68(handle) == 0) {
				result = 1;
			}
			break;
		case 0:
			result = 0;
			break;
		case 1:
			result = 1;
			break;
		default:
			result = 0;
			break;
	}
	return result;
}

void fn_17_E2D4(SfxHandle* handle, SfxFrame* frame, void* output)
{
	fn_17_E008(handle, frame, output);
}
#pragma dont_inline off
