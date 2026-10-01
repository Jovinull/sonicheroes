#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/dispatch.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/msgbuf.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/msghndlr.h"

// MetroTRK dispatch.c: the message dispatch table, 0x801CA918 to 0x801CA9B4.
// Boundaries: every function matched by instruction shape against the
// reference compiled with the MetroTRK flags, in link order.
// Reference: mariopartyrd/marioparty4 src/TRK_MINNOW_DOLPHIN/dispatch.c (public
// decompilation of the same MetroTRK build). Built with GC/1.3; see the
// TRK_MINNOW_DOLPHIN entry in configure.py.

u32 gTRKDispatchTableSize;

struct DispatchEntry {
	int (*fn)(TRKBuffer*);
};

struct DispatchEntry gTRKDispatchTable[33] = {
	{ &TRKDoUnsupported },
	{ &TRKDoConnect },
	{ &TRKDoDisconnect },
	{ &TRKDoReset },
	{ &TRKDoVersions },
	{ &TRKDoSupportMask },
	{ &TRKDoCPUType },
	{ &TRKDoUnsupported },
	{ &TRKDoUnsupported },
	{ &TRKDoUnsupported },
	{ &TRKDoUnsupported },
	{ &TRKDoUnsupported },
	{ &TRKDoUnsupported },
	{ &TRKDoUnsupported },
	{ &TRKDoUnsupported },
	{ &TRKDoUnsupported },
	{ &TRKDoReadMemory },
	{ &TRKDoWriteMemory },
	{ &TRKDoReadRegisters },
	{ &TRKDoWriteRegisters },
	{ &TRKDoUnsupported },
	{ &TRKDoUnsupported },
	{ &TRKDoFlushCache },
	{ &TRKDoSetOption },
	{ &TRKDoContinue },
	{ &TRKDoStep },
	{ &TRKDoStop },
	{ &TRKDoUnsupported },
	{ &TRKDoUnsupported },
	{ &TRKDoUnsupported },
	{ &TRKDoUnsupported },
	{ &TRKDoUnsupported },
};

DSError TRKInitializeDispatcher()
{
	gTRKDispatchTableSize = 32;
	return DS_NoError;
}

DSError TRKDispatchMessage(TRKBuffer* buffer)
{
	DSError error;
	u8 command;

	error = DS_DispatchError;
	TRKSetBufferPosition(buffer, 0);
	TRKReadBuffer1_ui8(buffer, &command);
	command &= 0xFF;
	if (command < gTRKDispatchTableSize) {
		error = gTRKDispatchTable[command].fn(buffer);
	}
	return error;
}
