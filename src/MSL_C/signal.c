#include "types.h"

// MSL signal.c, 0x801C3940 to 0x801C39F0: raise, over the six-entry handler
// table that is the unit's .bss at 0x803EE0B0 (signal itself is smart-stripped).
// Reference: mariopartyrd/marioparty4 src/MSL_C.PPCEABI.bare.H/signal.c.
// Built with GC/1.3 like the rest of MSL_C.

typedef void (*__signal_func_ptr)(int);

void exit(int status);

__signal_func_ptr signal_funcs[6];

int raise(int sig)
{
	__signal_func_ptr temp_r31;

	if (sig < 1 || sig > 6) {
		return -1;
	}
	temp_r31 = signal_funcs[sig - 1];
	if ((unsigned long)temp_r31 != 1) {
		signal_funcs[sig - 1] = NULL;
	}
	if ((unsigned long)temp_r31 == 1 || (temp_r31 == NULL && sig == 1)) {
		return 0;
	}
	if (temp_r31 == NULL) {
		exit(0);
	}
	temp_r31(sig);
	return 0;
}
