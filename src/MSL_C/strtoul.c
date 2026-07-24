#include "types.h"

typedef struct {
	const char* str;
	s32 pos;
} StringReadState;

typedef s32 (*ReadProc)(void* arg, s32 c, s32 action);

enum ScanState {
	SCAN_START          = 0x01,
	SCAN_CHECK_FOR_ZERO = 0x02,
	SCAN_LEADING_ZERO   = 0x04,
	SCAN_NEED_DIGIT     = 0x08,
	SCAN_DIGIT_LOOP     = 0x10,
	SCAN_FINISHED       = 0x20,
	SCAN_FAILURE        = 0x40,
};

#define FINAL_STATE(state) ((state) & (SCAN_FINISHED | SCAN_FAILURE))
#define SUCCESS(state)     ((state) & (SCAN_LEADING_ZERO | SCAN_DIGIT_LOOP | SCAN_FINISHED))
#define FETCH()            (count++, read_proc(read_arg, 0, 0))
#define UNFETCH(c)         read_proc(read_arg, (c), 1)

extern u8 lbl_80291680[256];
extern u8 lbl_80291880[256];

#define isalpha(c) (lbl_80291680[(u8)(c)] & 0xC0)
#define isdigit(c) (lbl_80291680[(u8)(c)] & 0x10)
#define isspace(c) (lbl_80291680[(u8)(c)] & 0x06)
#define toupper(c) ((c) == -1 ? -1 : lbl_80291880[(u8)(c)])

extern s32 errno;
extern s32 fn_801C29BC(void* arg, s32 c, s32 action);

u64 __strtoull(s32 base, s32 max_width, ReadProc read_proc, void* read_arg, s32* consumed,
    s32* negative, s32* overflow);
u32 __strtoul(s32 base, s32 max_width, ReadProc read_proc, void* read_arg, s32* consumed,
    s32* negative, s32* overflow);

s32 atoi(const char* str)
{
	u32 value;
	s32 overflow;
	s32 negative;
	s32 count;
	StringReadState state;

	state.str = str;
	state.pos = 0;

	value = __strtoul(10, 0x7FFFFFFF, fn_801C29BC, &state, &count, &negative, &overflow);

	if (overflow || (!negative && value > 0x7FFFFFFF) || (negative && value > 0x80000000U)) {
		value = negative ? 0x80000000U : 0x7FFFFFFF;
		errno = 0x22;
	} else if (negative) {
		value = -value;
	}

	return value;
}

u32 strtoul(const char* str, char** end, s32 base)
{
	u32 value;
	s32 count;
	s32 negative;
	s32 overflow;
	StringReadState state;

	state.str = str;
	state.pos = 0;

	value = __strtoul(base, 0x7FFFFFFF, fn_801C29BC, &state, &count, &negative, &overflow);

	if (end)
		*end = (char*)str + count;

	if (overflow) {
		value = 0xFFFFFFFFU;
		errno = 0x22;
	} else if (negative) {
		value = -value;
	}

	return value;
}

u64 __strtoull(s32 base, s32 max_width, ReadProc read_proc, void* read_arg, s32* consumed,
    s32* negative, s32* overflow)
{
	s32 scan_state = SCAN_START;
	s32 count      = 0;
	s32 spaces     = 0;
	u64 value      = 0;
	u64 value_max  = 0;
	u64 ullmax     = 0xFFFFFFFFFFFFFFFFULL;
	s32 c;

	*negative = *overflow = 0;

	if (base < 0 || base == 1 || base > 36 || max_width < 1) {
		scan_state = SCAN_FAILURE;
	} else {
		c = FETCH();
	}

	if (base != 0)
		value_max = ullmax / base;

	while (count <= max_width && c != -1 && !FINAL_STATE(scan_state)) {
		switch (scan_state) {
			case SCAN_START:
				if (isspace(c)) {
					c = FETCH();
					count--;
					spaces++;
					break;
				}

				if (c == '+') {
					c = FETCH();
				} else if (c == '-') {
					c         = FETCH();
					*negative = 1;
				}

				scan_state = SCAN_CHECK_FOR_ZERO;
				break;

			case SCAN_CHECK_FOR_ZERO:
				if ((base == 0 || base == 16) && c == '0') {
					scan_state = SCAN_LEADING_ZERO;
					c          = FETCH();
					break;
				}

				scan_state = SCAN_NEED_DIGIT;
				break;

			case SCAN_LEADING_ZERO:
				if (c == 'X' || c == 'x') {
					base       = 16;
					scan_state = SCAN_NEED_DIGIT;
					c          = FETCH();
					break;
				}

				if (base == 0)
					base = 8;

				scan_state = SCAN_DIGIT_LOOP;
				break;

			case SCAN_NEED_DIGIT:
			case SCAN_DIGIT_LOOP:
				if (base == 0)
					base = 10;

				if (!value_max)
					value_max = ullmax / base;

				if (isdigit(c)) {
					if ((c -= '0') >= base) {
						if (scan_state == SCAN_DIGIT_LOOP)
							scan_state = SCAN_FINISHED;
						else
							scan_state = SCAN_FAILURE;
						c += '0';
						break;
					}
				} else if (!isalpha(c) || toupper(c) - 'A' + 10 >= base) {
					if (scan_state == SCAN_DIGIT_LOOP)
						scan_state = SCAN_FINISHED;
					else
						scan_state = SCAN_FAILURE;
					break;
				} else {
					c = toupper(c) - 'A' + 10;
				}

				if (value > value_max)
					*overflow = 1;

				value *= base;

				if ((u64)c > ullmax - value)
					*overflow = 1;

				value += c;
				scan_state = SCAN_DIGIT_LOOP;
				c          = FETCH();
				break;
		}
	}

	if (!SUCCESS(scan_state)) {
		count = value = *consumed = 0;
	} else {
		count--;
		*consumed = count + spaces;
	}

	UNFETCH(c);
	return value;
}

u32 __strtoul(s32 base, s32 max_width, ReadProc read_proc, void* read_arg, s32* consumed,
    s32* negative, s32* overflow)
{
	s32 scan_state = SCAN_START;
	s32 count      = 0;
	s32 spaces     = 0;
	u32 value      = 0;
	u32 value_max  = 0;
	s32 c;

	*negative = *overflow = 0;

	if (base < 0 || base == 1 || base > 36 || max_width < 1) {
		scan_state = SCAN_FAILURE;
	} else {
		c = FETCH();
	}

	if (base != 0)
		value_max = 0xFFFFFFFFU / base;

	while (count <= max_width && c != -1 && !FINAL_STATE(scan_state)) {
		switch (scan_state) {
			case SCAN_START:
				if (isspace(c)) {
					c = FETCH();
					count--;
					spaces++;
					break;
				}

				if (c == '+') {
					c = FETCH();
				} else if (c == '-') {
					c         = FETCH();
					*negative = 1;
				}

				scan_state = SCAN_CHECK_FOR_ZERO;
				break;

			case SCAN_CHECK_FOR_ZERO:
				if ((base == 0 || base == 16) && c == '0') {
					scan_state = SCAN_LEADING_ZERO;
					c          = FETCH();
					break;
				}

				scan_state = SCAN_NEED_DIGIT;
				break;

			case SCAN_LEADING_ZERO:
				if (c == 'X' || c == 'x') {
					base       = 16;
					scan_state = SCAN_NEED_DIGIT;
					c          = FETCH();
					break;
				}

				if (base == 0)
					base = 8;

				scan_state = SCAN_DIGIT_LOOP;
				break;

			case SCAN_NEED_DIGIT:
			case SCAN_DIGIT_LOOP:
				if (base == 0)
					base = 10;

				if (!value_max)
					value_max = 0xFFFFFFFFU / base;

				if (isdigit(c)) {
					if ((c -= '0') >= base) {
						if (scan_state == SCAN_DIGIT_LOOP)
							scan_state = SCAN_FINISHED;
						else
							scan_state = SCAN_FAILURE;
						c += '0';
						break;
					}
				} else if (!isalpha(c) || toupper(c) - 'A' + 10 >= base) {
					if (scan_state == SCAN_DIGIT_LOOP)
						scan_state = SCAN_FINISHED;
					else
						scan_state = SCAN_FAILURE;
					break;
				} else {
					c = toupper(c) - 'A' + 10;
				}

				if (value > value_max)
					*overflow = 1;

				value *= base;

				if ((u32)c > 0xFFFFFFFFU - value)
					*overflow = 1;

				value += c;
				scan_state = SCAN_DIGIT_LOOP;
				c          = FETCH();
				break;
		}
	}

	if (!SUCCESS(scan_state)) {
		count     = 0;
		value     = 0;
		*consumed = 0;
	} else {
		count--;
		*consumed = count + spaces;
	}

	UNFETCH(c);
	return value;
}

s32 fn_801C5900(void)
{
	return 0;
}
