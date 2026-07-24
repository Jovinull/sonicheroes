#include "types.h"

// Deferred code generation emits these definitions in reverse order.

typedef struct {
	s8 sign;
	s8 unk1;
	s16 exp;
	struct {
		u8 length;
		u8 text[36];
		u8 unk41;
	} sig;
} decimal;

typedef struct {
	char* decimal_point;
	char* thousands_sep;
	char* grouping;
	char* mon_decimal_point;
	char* mon_thousands_sep;
	char* mon_grouping;
	char* positive_sign;
	char* negative_sign;
	char* currency_symbol;
	char frac_digits;
	char p_cs_precedes;
	char n_cs_precedes;
	char p_sep_by_space;
	char n_sep_by_space;
	char p_sign_posn;
	char n_sign_posn;
	char* int_curr_symbol;
	char int_frac_digits;
	char int_p_cs_precedes;
	char int_n_cs_precedes;
	char int_p_sep_by_space;
	char int_n_sep_by_space;
	char int_p_sign_posn;
	char int_n_sign_posn;
} lconv;

enum scan_states {
	start              = 0x0001,
	sig_start          = 0x0002,
	leading_sig_zeroes = 0x0004,
	int_digit_loop     = 0x0008,
	frac_start         = 0x0010,
	frac_digit_loop    = 0x0020,
	sig_end            = 0x0040,
	exp_start          = 0x0080,
	leading_exp_digit  = 0x0100,
	leading_exp_zeroes = 0x0200,
	exp_digit_loop     = 0x0400,
	finished           = 0x0800,
	failure            = 0x1000,
	nan_state          = 0x2000,
	infin_state        = 0x4000,
	hex_state          = 0x8000
};

enum hex_scan_states {
	not_hex                = 0x0000,
	hex_start              = 0x0001,
	hex_leading_sig_zeroes = 0x0002,
	hex_int_digit_loop     = 0x0004,
	hex_frac_digit_loop    = 0x0008,
	hex_sig_end            = 0x0010,
	hex_exp_start          = 0x0020,
	hex_leading_exp_digit  = 0x0040,
	hex_leading_exp_zeroes = 0x0080,
	hex_exp_digit_loop     = 0x0100
};

#define FINAL_STATE(scan_state) ((scan_state) & (finished | failure))
#define SUCCESS(scan_state)                                                                        \
	((scan_state)                                                                                  \
	    & (leading_sig_zeroes | int_digit_loop | frac_digit_loop | leading_exp_zeroes              \
	        | exp_digit_loop | finished))

extern u8 lbl_80291680[256];
extern u8 lbl_80291880[256];
extern lconv lbl_80291980;

#define isalpha(c)  (lbl_80291680[(u8)(c)] & 0xC0)
#define isdigit(c)  (lbl_80291680[(u8)(c)] & 0x10)
#define isspace(c)  (lbl_80291680[(u8)(c)] & 0x06)
#define isxdigit(c) (lbl_80291680[(u8)(c)] & 0x20)
#define toupper(c)  ((c) == -1 ? -1 : lbl_80291880[(u8)(c)])

extern s32 lbl_8042BEE8[];
extern s32 lbl_8042BEEC[];
extern s32 lbl_8042BF00[];
extern s32 lbl_8042BF08[];
extern s32 lbl_8042BF10[];
extern double fn_801BCB64(const decimal* value);

#define FLOAT_NAN       (*(float*)lbl_8042BEE8)
#define FLOAT_INFINITY  (*(float*)lbl_8042BEEC)
#define DOUBLE_INFINITY (*(double*)lbl_8042BF00)
#define LONG_DOUBLE_MIN (*(long double*)lbl_8042BF08)
#define LONG_DOUBLE_MAX (*(long double*)lbl_8042BF10)
#define SHRT_MIN_VALUE  (-32768)
#define SHRT_MAX_VALUE  32767

// This unit is built with -sdata 4. The two eight-byte range bounds therefore
// use absolute addressing, while compiler-generated literals stay in .sdata2.
extern double __double_min;
extern double __double_max;
extern s32 errno;

// The callback that feeds the scanner still belongs to an earlier uncarved TU.
typedef struct {
	const char* str;
	s32 pos;
} __StringRead;

typedef s32 (*ReadProc)(void* arg, s32 c, s32 action);

long double fn_801C4004(
    s32 max_width, ReadProc read_proc, void* read_arg, s32* consumed, s32* error);
extern s32 fn_801C29BC(void* arg, s32 c, s32 action);

#define FETCH()    (count++, read_proc(read_arg, 0, 0))
#define UNFETCH(c) read_proc(read_arg, (c), 1)

long double fn_801C4004(
    s32 max_width, ReadProc read_proc, void* read_arg, s32* consumed, s32* error)
{
	s32 scan_state     = start;
	s32 hex_scan_state = not_hex;
	s32 count          = 0;
	s32 spaces         = 0;
	s32 c;
	decimal d        = { 0, 0, 0, { 0, "" } };
	s32 sig_negative = 0;
	s32 exp_negative = 0;
	long exp_value   = 0;
	s32 exp_adjust   = 0;
	long double result;
	s32 sign_detected = 0;

	u8* chptr = (u8*)&result;
	u8 uch, uch1;
	s32 ui;
	s32 chindex;
	s32 NibbleIndex;
	s32 expsign         = 0;
	s32 exp_digits      = 0;
	s32 intdigits       = 0;
	s32 RadixPointFound = 0;
	s16 exponent        = 0;
	s32 dot;

	dot = *(u8*)lbl_80291980.decimal_point;

	*error = 0;
	c      = FETCH();

	while (count <= max_width && c != -1 && !FINAL_STATE(scan_state)) {
		switch (scan_state) {
			case start:
				if (isspace(c)) {
					c = FETCH();
					count--;
					spaces++;
					break;
				}

				switch (toupper(c)) {
					case '-':
						sig_negative = 1;

					case '+':
						c             = FETCH();
						sign_detected = 1;
						break;
					case 'I':
						c          = FETCH();
						scan_state = infin_state;
						break;

					case 'N':
						c          = FETCH();
						scan_state = nan_state;
						break;

					default:
						scan_state = sig_start;
						break;
				}
				break;

			case infin_state: {
				s32 i        = 1;
				char model[] = "INFINITY";

				while (i < 8 && toupper(c) == model[i]) {
					i++;
					c = FETCH();
				}

				if (i == 3 || i == 8) {
					if (sig_negative)
						result = -FLOAT_INFINITY;
					else
						result = FLOAT_INFINITY;

					*consumed = spaces + i + sign_detected;
					return result;
				} else {
					scan_state = failure;
				}
				break;
			}

			case nan_state: {
				s32 i = 1, j = 0;
				char model[] = "NAN(";

				while (i < 4 && toupper(c) == model[i]) {
					i++;
					c = FETCH();
				}

				if (i == 3 || i == 4) {
					if (i == 4) {
						while (j < 32 && (isdigit(c) || isalpha(c))) {
							j++;
							c = FETCH();
						}

						if (c != ')') {
							scan_state = failure;
							break;
						} else {
							j++;
						}
					}
					if (sig_negative)
						result = -FLOAT_NAN;
					else
						result = FLOAT_NAN;

					*consumed = spaces + i + j + sign_detected;
					return result;
				} else {
					scan_state = failure;
				}
				break;
			}

			case sig_start:
				if (c == dot) {
					scan_state = frac_start;
					c          = FETCH();
					break;
				}
				if (!isdigit(c)) {
					scan_state = failure;
					break;
				}

				if (c == '0') {
					c = FETCH();
					if (toupper(c) == 'X') {
						scan_state     = hex_state;
						hex_scan_state = hex_start;
					} else {
						scan_state = leading_sig_zeroes;
					}
					break;
				}

				scan_state = int_digit_loop;
				break;

			case leading_sig_zeroes:
				if (c == '0') {
					c = FETCH();
					break;
				}
				scan_state = int_digit_loop;
				break;

			case int_digit_loop:
				if (!isdigit(c)) {
					if (c == dot) {
						scan_state = frac_digit_loop;
						c          = FETCH();
					} else {
						scan_state = sig_end;
					}
					break;
				}
				if (d.sig.length < 20)
					d.sig.text[d.sig.length++] = c;
				else
					exp_adjust++;

				c = FETCH();
				break;

			case frac_start:
				if (!isdigit(c)) {
					scan_state = failure;
					break;
				}

				scan_state = frac_digit_loop;
				break;

			case frac_digit_loop:
				if (!isdigit(c)) {
					scan_state = sig_end;
					break;
				}

				if (d.sig.length < 20) {
					if (c != '0' || d.sig.length)
						d.sig.text[d.sig.length++] = c;

					exp_adjust--;
				}
				c = FETCH();
				break;

			case sig_end:
				if (toupper(c) == 'E') {
					scan_state = exp_start;
					c          = FETCH();
					break;
				}
				scan_state = finished;
				break;

			case exp_start:
				if (c == '+')
					c = FETCH();
				else if (c == '-') {
					c            = FETCH();
					exp_negative = 1;
				}

				scan_state = leading_exp_digit;
				break;

			case leading_exp_digit:
				if (!isdigit(c)) {
					scan_state = failure;
					break;
				}

				if (c == '0') {
					scan_state = leading_exp_zeroes;
					c          = FETCH();
					break;
				}

				scan_state = exp_digit_loop;
				break;

			case leading_exp_zeroes:
				if (c == '0') {
					c = FETCH();
					break;
				}

				scan_state = exp_digit_loop;
				break;

			case exp_digit_loop:
				if (!isdigit(c)) {
					scan_state = finished;
					break;
				}

				exp_value = exp_value * 10 + (c - '0');
				if (exp_value > SHRT_MAX_VALUE)
					*error = 1;

				c = FETCH();
				break;

			case hex_state: {
				switch (hex_scan_state) {
					case hex_start:
						for (chindex = 0; chindex < 8; chindex++)
							*(chptr + chindex) = '\0';
						NibbleIndex    = 2;
						hex_scan_state = hex_leading_sig_zeroes;
						c              = FETCH();
						break;

					case hex_leading_sig_zeroes:
						if (c == '0') {
							c = FETCH();
							break;
						}

						hex_scan_state = hex_int_digit_loop;
						break;

					case hex_int_digit_loop:
						if (!isxdigit(c)) {
							if (c == dot) {
								hex_scan_state = hex_frac_digit_loop;
								c              = FETCH();
							} else {
								hex_scan_state = hex_sig_end;
							}
							break;
						}

						if (NibbleIndex < 17) {
							intdigits++;
							uch = *(chptr + NibbleIndex / 2);
							ui  = toupper(c);

							if (ui >= 'A')
								ui = ui - 'A' + 10;
							else
								ui -= '0';

							uch1 = ui;

							if (NibbleIndex % 2 != 0)
								uch |= uch1;
							else
								uch |= uch1 << 4;

							*(chptr + NibbleIndex++ / 2) = uch;
							c                            = FETCH();
						} else {
							c = FETCH();
						}

						break;

					case hex_frac_digit_loop:
						if (!isxdigit(c)) {
							hex_scan_state = hex_sig_end;
							break;
						}

						if (NibbleIndex < 17) {
							uch = *(chptr + NibbleIndex / 2);
							ui  = toupper(c);

							if (ui >= 'A')
								ui = ui - 'A' + 10;
							else
								ui -= '0';

							uch1 = ui;

							if (NibbleIndex % 2 != 0)
								uch |= uch1;
							else
								uch |= uch1 << 4;

							*(chptr + NibbleIndex++ / 2) = uch;
							c                            = FETCH();
						} else {
							c = FETCH();
						}
						break;

					case hex_sig_end:
						if (toupper(c) == 'P') {
							hex_scan_state = hex_exp_start;
							exp_digits++;
							c = FETCH();
						} else {
							scan_state = finished;
						}

						break;

					case hex_exp_start:
						exp_digits++;
						if (c == '-')
							expsign = 1;
						else if (c != '+') {
							c = UNFETCH(c);
							exp_digits--;
						}

						hex_scan_state = hex_leading_exp_digit;
						c              = FETCH();
						break;

					case hex_leading_exp_digit:
						if (!isdigit(c)) {
							scan_state = failure;
							break;
						}

						if (c == '0') {
							exp_digits++;
							hex_scan_state = hex_leading_exp_zeroes;
							c              = FETCH();
							break;
						}

						hex_scan_state = hex_exp_digit_loop;
						break;

					case hex_exp_digit_loop:
						if (!isdigit(c)) {
							scan_state = finished;
							break;
						}

						exponent = exponent * 10 + (c - '0');

						if (exp_value > SHRT_MAX_VALUE)
							*error = 1;

						exp_digits++;
						c = FETCH();
						break;
				}
			} break;
		}
	}

	if (!SUCCESS(scan_state)) {
		count     = 0;
		*consumed = 0;
	} else {
		count--;
		*consumed = count + spaces;
	}

	UNFETCH(c);

	if (hex_scan_state == not_hex) {
		if (exp_negative)
			exp_value = -exp_value;

		{
			s32 n = d.sig.length;
			u8* p = &d.sig.text[n];

			while (n-- && *--p == '0')
				exp_adjust++;

			d.sig.length = n + 1;

			if (d.sig.length == 0)
				d.sig.text[d.sig.length++] = '0';
		}

		exp_value += exp_adjust;

		if (exp_value < SHRT_MIN_VALUE || exp_value > SHRT_MAX_VALUE)
			*error = 1;

		if (*error) {
			if (exp_negative)
				return 0.0;
			return sig_negative ? -DOUBLE_INFINITY : DOUBLE_INFINITY;
		}

		d.exp = exp_value;

		result = fn_801BCB64(&d);

		if (result != 0.0 && result < LONG_DOUBLE_MIN) {
			*error = 1;
		} else if (result > LONG_DOUBLE_MAX) {
			*error = 1;
			result = DOUBLE_INFINITY;
		}

		if (sig_negative && SUCCESS(scan_state))
			result = -result;

		return result;
	} else {
		u64* uptr = (u64*)&result;

		if (result) {
			if (expsign)
				exponent = -exponent;

			while ((*(s16*)&result & 0x00F0) != 0x0010) {
				*uptr >>= 1;
				exponent++;
			}

			exponent += 4 * (intdigits - 1);
			*(s16*)&result &= 0x000F;
			*(s16*)&result |= (exponent + 1023) << 4;

			*consumed = spaces + sign_detected + NibbleIndex + 1 + exp_digits;
			if (result != 0.0 && result < LONG_DOUBLE_MIN) {
				*error = 1;
				result = 0.0;
			} else if (result > LONG_DOUBLE_MAX) {
				*error = 1;
				result = DOUBLE_INFINITY;
			}
			if (sig_negative)
				*(s16*)&result |= 0x8000;
		} else {
			result = 0.0;
		}
		return result;
	}
}

double strtod(const char* s, char** end)
{
	__StringRead state;
	s32 consumed;
	s32 error;
	long double value;
	long double magnitude;

	state.str = s;
	state.pos = 0;

	value = fn_801C4004(0x7FFFFFFF, fn_801C29BC, &state, &consumed, &error);

	if (end)
		*end = (char*)s + consumed;

	magnitude = __fabs(value);

	if (error != 0 || (0.0 != value && (magnitude < __double_min || magnitude > __double_max)))
		errno = 0x22;

	return value;
}

double atof(const char* s)
{
	__StringRead state;
	s32 error;
	s32 consumed;
	long double value;
	long double magnitude;

	state.str = s;
	state.pos = 0;

	value     = fn_801C4004(0x7FFFFFFF, fn_801C29BC, &state, &consumed, &error);
	magnitude = __fabs(value);

	if (error != 0 || (value != 0.0 && (magnitude < __double_min || magnitude > __double_max)))
		errno = 0x22;

	return value;
}
