#include "types.h"

static void (*FatalFunc)(void);

void __DVDPrintFatalMessage(void)
{
	if (FatalFunc != NULL) {
		FatalFunc();
	}
}
