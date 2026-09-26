#include "types.h"

// MSL arith.c, 0x801BE7D0 to 0x801BE838: div and labs (abs is smart-stripped).
// Boundaries: both functions match the reference by instruction shape and sit
// between ansi_fp.c and buffer_io.c in the library's link order.
// Reference: zeldaret/tww src/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/
// arith.c. Built with GC/1.3 like the rest of MSL_C.

typedef struct {
	int quot;
	int rem;
} div_t;

int abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

long labs(long x)
{
	if (x < 0)
		return -x;
	else
		return x;
}

div_t div(int numerator, int denominator)
{
	div_t ret;
	int i = 1;
	int j = 1;

	if (numerator < 0) {
		numerator = -numerator;
		i         = -1;
	}

	if (denominator < 0) {
		denominator = -denominator;
		j           = -1;
	}

	ret.quot = (numerator / denominator) * (i * j);
	ret.rem  = numerator * i - j * (ret.quot * denominator);
	return ret;
}
