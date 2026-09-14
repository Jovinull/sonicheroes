#include "cri/sj.h"
#include "cri/svm.h"
#include "MSL_C/string.h"

// Shared SJ tag/chunk helpers and error dispatch, inferred GC source boundary
// 0x80221610..0x802218A8. The hexadecimal table belongs exclusively to these
// helpers; the preceding ring-buffer callback and SJUNI state are separate.

static s32 sj_hexstr_to_val_tbl[0x70] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	10,
	11,
	12,
	13,
	14,
	15,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	10,
	11,
	12,
	13,
	14,
	15,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};

static inline s32 sjrbf_DecodeLength(const s8* p)
{
	s32 value = sj_hexstr_to_val_tbl[p[8]];
	value     = value * 16 + sj_hexstr_to_val_tbl[p[9]];
	value     = value * 16 + sj_hexstr_to_val_tbl[p[10]];
	value     = value * 16 + sj_hexstr_to_val_tbl[p[11]];
	value     = value * 16 + sj_hexstr_to_val_tbl[p[12]];
	value     = value * 16 + sj_hexstr_to_val_tbl[p[13]];
	return value * 16 + sj_hexstr_to_val_tbl[p[14]];
}

s8* fn_80221610(const CriChunk* input, const char* name, const char* stop, CriChunk* output)
{
	s8* cursor;
	s8* end;

	output->addr = NULL;
	output->size = 0;
	end          = (s8*)input->addr + input->size;
	cursor       = (s8*)input->addr;

	while (cursor < end) {
		if (strncmp((char*)cursor, name, 7) == 0) {
			output->addr = cursor + 0x10;
			output->size = sjrbf_DecodeLength(cursor);
			break;
		}

		if (stop != NULL && strncmp((char*)cursor, stop, 7) == 0) {
			return NULL;
		}

		{
			u32 length = sj_hexstr_to_val_tbl[cursor[8]];
			length     = length * 16 + sj_hexstr_to_val_tbl[cursor[9]];
			length     = length * 16 + sj_hexstr_to_val_tbl[cursor[10]];
			length     = length * 16 + sj_hexstr_to_val_tbl[cursor[11]];
			length     = length * 16 + sj_hexstr_to_val_tbl[cursor[12]];
			length     = length * 16 + sj_hexstr_to_val_tbl[cursor[13]];
			length     = length * 16 + sj_hexstr_to_val_tbl[cursor[14]];
			cursor += length + 0x10;
		}
	}

	return cursor < end ? cursor : NULL;
}

void fn_80221824(CriChunk* input, s32 size, CriChunk* first, CriChunk* remainder)
{
	*first          = *input;
	remainder->size = first->size;
	if (first->size > size) {
		first->size = size;
	}
	remainder->size -= first->size;
	if (remainder->size == 0) {
		remainder->addr = NULL;
	} else {
		remainder->addr = (s8*)first->addr + first->size;
	}
}

void fn_80221888(const char* message)
{
	fn_8022240C(message);
}
