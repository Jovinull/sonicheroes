#include "types.h"

// MSL locale.c. No code of it survives in the DOL: localeconv and setlocale
// were smart-stripped. What remains is its data, the "C" locale conventions
// in .data at 0x80291980 and the unit's string pool (".", "" and "C") in
// .rodata at 0x8023CC08, between ansi_fp.c and printf.c.
// Reference: the Metrowerks MSL locale.c layout (struct lconv with the C99
// int_* members). Built with GC/1.3 like the rest of MSL_C.

#define CHAR_MAX 127

struct lconv {
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
};

struct lconv __lconv = {
	".",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	"",
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
	CHAR_MAX,
};

int strcmp(const char* str1, const char* str2);

char* setlocale(int category, const char* locale)
{
	if (locale == 0 || !strcmp(locale, "C") || !strcmp(locale, ""))
		return "C";

	return 0;
}

struct lconv* localeconv(void)
{
	return &__lconv;
}
