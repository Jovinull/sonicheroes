#include "types.h"

// Order follows the original binary, which for this compiler is source order.

typedef void (*__ExitProc)(void);

extern void __destroy_global_chain(void);
extern __ExitProc _dtors[];
extern __ExitProc __stdio_exit;
extern __ExitProc __console_exit;
extern void _ExitProcess(void);
extern void fn_801C3940(s32 signal);

static __ExitProc __atexit_funcs[64];
static s32 __atexit_curr_func;
s32 __aborting;

void exit(int status)
{
	__ExitProc* p;
	__ExitProc f;

	if (!__aborting) {
		__destroy_global_chain();
		for (p = _dtors; (f = *p) != 0; p++)
			f();
		if (__stdio_exit != 0) {
			__stdio_exit();
			__stdio_exit = 0;
		}
	}

	while (__atexit_curr_func > 0) {
		__atexit_curr_func--;
		__atexit_funcs[__atexit_curr_func]();
	}

	if (__console_exit != 0) {
		__console_exit();
		__console_exit = 0;
	}

	_ExitProcess();
}

void abort(void)
{
	fn_801C3940(1);
	__aborting = 1;

	while (__atexit_curr_func > 0) {
		__atexit_curr_func--;
		__atexit_funcs[__atexit_curr_func]();
	}

	if (__console_exit != 0) {
		__console_exit();
		__console_exit = 0;
	}

	_ExitProcess();
}
