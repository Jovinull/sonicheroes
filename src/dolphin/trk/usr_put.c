#include "TRK_MINNOW_DOLPHIN/Os/dolphin/usr_put.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/msghndlr.h"
#include "PowerPC_EABI_Support/MetroTRK/trk.h"

// MetroTRK usr_put.c: the user console output hook, 0x801CA88C to 0x801CA918.
// Boundaries: every function matched by instruction shape against the
// reference compiled with the MetroTRK flags, in link order.
// Reference: mariopartyrd/marioparty4 src/TRK_MINNOW_DOLPHIN/usr_put.c (public
// decompilation of the same MetroTRK build). Built with GC/1.3.2; see the
// TRK_MINNOW_DOLPHIN entry in configure.py.

BOOL usr_puts_serial(const char* msg)
{
	BOOL connect_ = FALSE;
	char c;
	char buf[2];

	while (!connect_ && (c = *msg++) != '\0') {
		BOOL connect = GetTRKConnected();

		buf[0] = c;
		buf[1] = '\0';

		SetTRKConnected(FALSE);
		OSReport(buf);

		SetTRKConnected(connect);
		connect_ = FALSE;
	}
	return connect_;
}

void usr_put_initialize(void) { }
