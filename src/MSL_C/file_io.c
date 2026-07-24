#include "types.h"

// Order follows the original binary, which for this compiler is source order.

// Registered so that exit() flushes and closes every open stream. The hook
// itself lives in the small data area, which is why the store is sda21.
extern void __close_all(void);
extern void (*__stdio_exit)(void);

void __stdio_atexit(void)
{
	__stdio_exit = __close_all;
}
