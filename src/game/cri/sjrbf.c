#include "types.h"

// CRI SJRBF: parses named records from an in-memory SJ buffer. The complete
// unit is the six-function run at 0x8022154C..0x802218A8 together with its
// exclusive rodata, hexadecimal lookup table, and BSS workspace.
// MATCHING: every function and owned section is byte-exact.

typedef struct SjRange {
	s8* data;
	s32 size;
} SjRange;

void* memset(void* dst, s32 value, u32 size);
s32 strncmp(const char* lhs, const char* rhs, u32 count);
void fn_8022240C(const char* message);
void fn_80221888(const char* message);

static s32 lbl_804270A8;
static u8 lbl_804270AC[0xC04];

static const char lbl_8023FFB0[] = "SJRBF Error";
const u32 gap_06_8023FFBC_rodata = 0;

static s32 lbl_8029B888[0x70] = {
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
	s32 value = lbl_8029B888[p[8]];
	value     = value * 16 + lbl_8029B888[p[9]];
	value     = value * 16 + lbl_8029B888[p[10]];
	value     = value * 16 + lbl_8029B888[p[11]];
	value     = value * 16 + lbl_8029B888[p[12]];
	value     = value * 16 + lbl_8029B888[p[13]];
	return value * 16 + lbl_8029B888[p[14]];
}

void fn_8022154C(void)
{
	fn_80221888(lbl_8023FFB0);
}

void fn_80221574(void)
{
	lbl_804270A8--;
	if (lbl_804270A8 == 0) {
		memset(lbl_804270AC, 0, 0xC00);
	}
}

void fn_802215BC(void)
{
	if (lbl_804270A8 == 0) {
		memset(lbl_804270AC, 0, 0xC00);
	}
	lbl_804270A8++;
}

s8* fn_80221610(const SjRange* input, const char* name, const char* stop, SjRange* output)
{
	s8* cursor;
	s8* end;

	output->data = NULL;
	output->size = 0;
	end          = input->data + input->size;
	cursor       = input->data;

	while (cursor < end) {
		if (strncmp((char*)cursor, name, 7) == 0) {
			output->data = cursor + 0x10;
			output->size = sjrbf_DecodeLength(cursor);
			break;
		}

		if (stop != NULL && strncmp((char*)cursor, stop, 7) == 0) {
			return NULL;
		}

		{
			u32 length = lbl_8029B888[cursor[8]];
			length     = length * 16 + lbl_8029B888[cursor[9]];
			length     = length * 16 + lbl_8029B888[cursor[10]];
			length     = length * 16 + lbl_8029B888[cursor[11]];
			length     = length * 16 + lbl_8029B888[cursor[12]];
			length     = length * 16 + lbl_8029B888[cursor[13]];
			length     = length * 16 + lbl_8029B888[cursor[14]];
			cursor     = length + cursor;
			cursor += 0x10;
		}
	}

	return cursor < end ? cursor : NULL;
}

void fn_80221824(const SjRange* input, s32 size, SjRange* first, SjRange* remainder)
{
	*first          = *input;
	remainder->size = first->size;
	if (first->size > size) {
		first->size = size;
	}
	remainder->size -= first->size;
	if (remainder->size == 0) {
		remainder->data = NULL;
	} else {
		remainder->data = first->data + first->size;
	}
}

void fn_80221888(const char* message)
{
	fn_8022240C(message);
}
